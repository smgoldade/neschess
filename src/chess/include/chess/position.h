// Author: Steven Goldade
#pragma once
#include "board.h"
#include "evaluation.h"
#include <nespp/dropout_stack.h>

namespace chess {
    struct PositionFlags {
        u8 white_to_move : 1;
        u8 white_king_side_castle : 1;
        u8 white_queen_side_castle : 1;
        u8 black_king_side_castle : 1;
        u8 black_queen_side_castle : 1;

        constexpr PositionFlags() : white_to_move(true), white_king_side_castle(true), white_queen_side_castle(true), black_king_side_castle(true), black_queen_side_castle(true) {}

        auto constexpr operator==(const PositionFlags& other) const noexcept -> bool {
            if(white_to_move != other.white_to_move) return false;
            if(white_king_side_castle != other.white_king_side_castle) return false;
            if(white_queen_side_castle != other.white_queen_side_castle) return false;
            if(black_king_side_castle != other.black_king_side_castle) return false;
            return black_queen_side_castle == other.black_queen_side_castle;
        }
    };

    struct PositionState {
        PositionFlags flags;
        Square en_passant_square;
        u8 reversible_ply_count;
        s16 evaluation;
        Move last_move;

        constexpr PositionState() noexcept : reversible_ply_count(0), evaluation(0) {}
        constexpr PositionState(PositionState& other) noexcept = default;
        constexpr PositionState(PositionState&& other) noexcept = default;
        auto constexpr operator=(const PositionState& other) noexcept -> PositionState& = default;
        auto constexpr operator=(PositionState&& other) noexcept -> PositionState& = default;

        auto constexpr operator==(const PositionState& other) const noexcept -> bool {
            if(flags != other.flags) return false;
            if(en_passant_square != other.en_passant_square) return false;
            if(reversible_ply_count != other.reversible_ply_count) return false;
            if(evaluation != other.evaluation) return false;
            return last_move == other.last_move;
        }
    };

    struct Position {
        constexpr Position() : board(), state() {}

        explicit constexpr Position(const char* fen) : board(), state() {
            enum class FenState {
                BOARD,
                SIDE,
                CASTLING,
                EN_PASSANT,
                HALF_MOVE,
                FULL_MOVE,
                DONE
            };

            FenState fen_state = FenState::BOARD;
            PieceType new_board[64];
            size_t i = 0;
            u8 board_index = 0;
            u16 half_move_count = 0;

            while(fen_state != FenState::DONE) {
                u8 next_char = fen[i++];
                switch(fen_state) {
                    case FenState::BOARD:
                        switch(next_char) {
                            case 'p':
                                new_board[board_index++ ^ 56] = PieceType::BLACK_PAWN;
                                break;
                            case 'n':
                                new_board[board_index++ ^ 56] = PieceType::BLACK_KNIGHT;
                                break;
                            case 'b':
                                new_board[board_index++ ^ 56] = PieceType::BLACK_BISHOP;
                                break;
                            case 'r':
                                new_board[board_index++ ^ 56] = PieceType::BLACK_ROOK;
                                break;
                            case 'q':
                                new_board[board_index++ ^ 56] = PieceType::BLACK_QUEEN;
                                break;
                            case 'k':
                                new_board[board_index++ ^ 56] = PieceType::BLACK_KING;
                                break;
                            case 'P':
                                new_board[board_index++ ^ 56] = PieceType::WHITE_PAWN;
                                break;
                            case 'N':
                                new_board[board_index++ ^ 56] = PieceType::WHITE_KNIGHT;
                                break;
                            case 'B':
                                new_board[board_index++ ^ 56] = PieceType::WHITE_BISHOP;
                                break;
                            case 'R':
                                new_board[board_index++ ^ 56] = PieceType::WHITE_ROOK;
                                break;
                            case 'Q':
                                new_board[board_index++ ^ 56] = PieceType::WHITE_QUEEN;
                                break;
                            case 'K':
                                new_board[board_index++ ^ 56] = PieceType::WHITE_KING;
                                break;
                            case '8': // NOLINT(*-branch-clone) -- Intentional to save lines
                                new_board[board_index++ ^ 56] = PieceType::NONE;
                            case '7':
                                new_board[board_index++ ^ 56] = PieceType::NONE;
                            case '6':
                                new_board[board_index++ ^ 56] = PieceType::NONE;
                            case '5':
                                new_board[board_index++ ^ 56] = PieceType::NONE;
                            case '4':
                                new_board[board_index++ ^ 56] = PieceType::NONE;
                            case '3':
                                new_board[board_index++ ^ 56] = PieceType::NONE;
                            case '2':
                                new_board[board_index++ ^ 56] = PieceType::NONE;
                            case '1':
                                new_board[board_index++ ^ 56] = PieceType::NONE;
                                break;
                            case ' ':
                                board = Board(new_board);
                                fen_state = FenState::SIDE;
                                break;
                            default:
                                break;
                        }
                        break;
                    case FenState::SIDE:
                        if(next_char == 'w') state.flags.white_to_move = true;
                        if(next_char == 'b') state.flags.white_to_move = false;
                        if(next_char == ' ') fen_state = FenState::CASTLING;
                        break;
                    case FenState::CASTLING:
                        if(next_char == 'k') state.flags.black_king_side_castle = true;
                        if(next_char == 'q') state.flags.black_queen_side_castle = true;
                        if(next_char == 'K') state.flags.white_king_side_castle = true;
                        if(next_char == 'Q') state.flags.white_queen_side_castle = true;
                        if(next_char == '-') {
                            state.flags.black_king_side_castle = false;
                            state.flags.black_queen_side_castle = false;
                            state.flags.white_king_side_castle = false;
                            state.flags.white_queen_side_castle = false;
                        }
                        if(next_char == ' ') fen_state = FenState::EN_PASSANT;
                        break;
                    case FenState::EN_PASSANT:
                        if(next_char == '-') {
                            i+=2;
                            state.en_passant_square = Square::INVALID;
                            fen_state = FenState::HALF_MOVE;
                        } else {
                            auto rank = fen[i++];
                            i++;
                            state.en_passant_square = Square(static_cast<File>(next_char-96), static_cast<Rank>(rank));
                            fen_state = FenState::HALF_MOVE;
                        }
                        break;
                    case FenState::HALF_MOVE:
                        if(next_char == ' ') {
                            state.reversible_ply_count = (half_move_count > 255) ? 255 : half_move_count;
                            fen_state = FenState::FULL_MOVE;
                        } else {
                            half_move_count *= 10;
                            half_move_count += next_char - '0';
                        }
                        break;
                    case FenState::FULL_MOVE:
                        if(next_char == '\0') fen_state = FenState::DONE;
                        break;
                    case FenState::DONE:
                        return;
                }
            }
            state.evaluation = Evaluator::evaluate(board, side_to_move());
        }

        struct ScopedMove {
            Position& position;
            const Move& move;

            constexpr ScopedMove(Position& position, const Move& move) noexcept : position(position), move(move) {
                this->position.make_move(this->move);
            }

            constexpr ~ScopedMove() {
                position.unmake_move(move);
            }
        };

        auto constexpr make_scoped_move(const Move& move) -> ScopedMove {
            return {*this, move};
        }

        auto constexpr make_move(const Move& move) -> void {
            auto const & from_square = move.from_square();
            auto const & to_square = move.to_square();
            if(!from_square.is_valid() || !to_square.is_valid()) return;
            auto const move_piece = board.piece_at(from_square);
            auto const capture_piece = board.piece_at(to_square);// we don't care about en passant for this

            state_stack.push(state);
            auto const castle_check = [&](const bool castle_flag, const PieceType& king_piece, const PieceType& rook_piece, const Square& rook_square) -> bool {
                if(!castle_flag) return false;

                auto const is_king = move_piece.piece_type() == king_piece;
                auto const rook = Piece(rook_piece, rook_square);
                auto const rook_move = move_piece == rook;
                auto const rook_capture = capture_piece == rook;

                return !(is_king || rook_move || rook_capture);
            };
            state.flags.white_king_side_castle = castle_check(state.flags.white_king_side_castle, PieceType::WHITE_KING, PieceType::WHITE_ROOK, Square::H1);
            state.flags.white_queen_side_castle = castle_check(state.flags.white_queen_side_castle, PieceType::WHITE_KING, PieceType::WHITE_ROOK, Square::A1);
            state.flags.black_king_side_castle = castle_check(state.flags.black_king_side_castle, PieceType::BLACK_KING, PieceType::BLACK_ROOK, Square::H8);
            state.flags.black_queen_side_castle = castle_check(state.flags.black_queen_side_castle, PieceType::BLACK_KING, PieceType::BLACK_ROOK, Square::A8);

            auto const pawn_move = move_piece.piece_type().is_pawn();
            if(pawn_move || move.is_capture()) {
                state.reversible_ply_count = 0;
            } else {
                if(state.reversible_ply_count < 255) state.reversible_ply_count++;
            }
            state.en_passant_square = move.double_pawn_single_square();

            state.evaluation = static_cast<s16>(state.evaluation + Evaluator::evaluate_move(board, move));
            state.evaluation = static_cast<s16>(-state.evaluation);
            board.make_move(move);
            state.flags.white_to_move = !state.flags.white_to_move;
        }

        auto constexpr unmake_move(const Move& move) -> void {
            board.unmake_move(move);
            state = state_stack.pop();
        }

        [[nodiscard]] auto constexpr get_board() const noexcept -> const Board& {
            return board;
        }

        [[nodiscard]] auto constexpr is_white_to_move() const noexcept -> bool {
            return state.flags.white_to_move;
        }

        [[nodiscard]] auto constexpr side_to_move() const noexcept -> Side {
            return state.flags.white_to_move ? Side::WHITE : Side::BLACK;
        }

        [[nodiscard]] auto constexpr can_white_king_side_castle() const noexcept -> bool {
            return state.flags.white_king_side_castle;
        }

        [[nodiscard]] auto constexpr can_white_queen_side_castle() const noexcept -> bool {
            return state.flags.white_queen_side_castle;
        }

        [[nodiscard]] auto constexpr can_black_king_side_castle() const noexcept -> bool {
            return state.flags.black_king_side_castle;
        }

        [[nodiscard]] auto constexpr can_black_queen_side_castle() const noexcept -> bool {
            return state.flags.black_queen_side_castle;
        }

        [[nodiscard]] auto constexpr get_reversible_ply_count() const noexcept -> u8 {
            return state.reversible_ply_count;
        }

        [[nodiscard]] auto constexpr get_en_passant_square() const noexcept -> const Square& {
            return state.en_passant_square;
        }

        [[nodiscard]] auto constexpr get_evaluation() const noexcept -> s16 {
            return state.evaluation;
        }

        auto constexpr operator==(const Position& other) const noexcept -> bool {
            if(board != other.board) return false;
            if(state != other.state) return false;
            return state_stack == other.state_stack;
        }
    private:
        Board board;
        PositionState state;
        nespp::DropoutStack<PositionState, 20> state_stack;
    };
}