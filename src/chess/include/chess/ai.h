/**
 * @author Steven Goldade
 * @date 11/21/2023
 */
#pragma once
#include "move_generator.h"
#include <nespp/types.h>

namespace chess {

    struct AI {
        Move best_move;

        auto constexpr search(Position& position, const u8 depth, const u8 ply, s16 alpha, s16 beta) noexcept -> s16 {
            if(depth == 0) {
                return position.get_evaluation();
            }

            s16 best_eval = -32767;
            auto const& pieces = position.get_board().get_pieces(position.side_to_move());
            for(auto const& piece : pieces) {
                if(!piece.square().is_valid()) continue;

                for(auto const& move : MoveGenerator::moves_for_piece(position, piece)) {
                    if(!MoveGenerator::is_move_legal(position, move)) continue;
                    if(best_move.is_null_move()) best_move = move;// TODO: Maybe find an actually good move?

                    auto const basic_search = [&](s16 alpha, s16 beta) -> s16 {
                        return static_cast<s16>(-search(position, depth - 1, ply + 1, alpha, beta));
                    };

                    position.make_move(move);
                    auto eval = basic_search(static_cast<s16>(-alpha - 1), static_cast<s16>(-alpha));
                    if(alpha < eval && eval < beta) {
                        eval = basic_search(static_cast<s16>(-beta), static_cast<s16>(-alpha));
                    }
                    position.unmake_move(move);

                    if(eval < best_eval) continue;
                    best_eval = eval;
                    if(eval > alpha) {
                        alpha = best_eval;
                        if(ply == 0) {
                            best_move = move;
                        }
                    }
                    if(beta <= alpha) break;
                }
                if(beta <= alpha) break;
            }
            return best_eval;
        }
    };
}