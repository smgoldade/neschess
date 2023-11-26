/**
 * @author Steven Goldade
 * @date 11/7/2023
 */
#include "game_screen.h"
#include <chess/move_generator.h>
#include <nespp/compression.h>
#include <nespp/error.h>
#include <nespp/joypad.h>
#include <nespp/ppu.h>

auto GameScreen::init() noexcept -> void {
    Ppu::wait();
    if(NESChess::settings.player_side == chess::Side::NONE) {
        switch(Ppu::get_frame_count() % 2) { // Random enough, but frame perfect start game would select a side
            case 0:
            default:
                NESChess::settings.player_side = chess::Side::WHITE;
                break;
            case 1:
                NESChess::settings.player_side = chess::Side::BLACK;
                break;
        }
    }
    player_is_white = NESChess::settings.player_side == chess::Side::WHITE;
    
    cursor_square = player_is_white ? Square::E2 : Square::E7;
    selected_square = Square::INVALID;
    
    board_renderer.set_black_on_bottom(!player_is_white);

    BufferedPpu::off();
    Ppu::wait();

    Ppu::wait();
    BufferedPpu::control.nametable = 0;
    BufferedPpu::control.background_pattern_table = 0;
    BufferedPpu::control.sprite_pattern_table = 1;
    BufferedPpu::mask.render_left8_background = true;
    BufferedPpu::mask.render_left8_sprites = true;

    auto constexpr init_sprite = [&](PpuSprite& sprite, const u8 tile_number, const u8 x=0) noexcept {
        sprite.tile_number = tile_number;
        sprite.x = x;
        sprite.palette = 3;
        sprite.horizontal_flip = false;
        sprite.vertical_flip = false;
        sprite.behind_background = false;
        sprite.hide();
    };

    init_sprite(hourglass_sprite, Tileset1::HOURGLASS, HOURGLASS_X);
    init_sprite(thinking_t_sprite, Tileset1::UPPERCASE_T, HOURGLASS_X - 28);
    init_sprite(thinking_h_sprite, Tileset1::LOWERCASE_H, thinking_t_sprite.x + 8);
    init_sprite(thinking_i_sprite, Tileset1::LOWERCASE_I, thinking_h_sprite.x + 8);
    init_sprite(thinking_n_sprite, Tileset1::LOWERCASE_N, thinking_i_sprite.x + 8);
    init_sprite(thinking_k_sprite, Tileset1::LOWERCASE_K, thinking_n_sprite.x + 8);
    init_sprite(thinking_i2_sprite, Tileset1::LOWERCASE_I, thinking_k_sprite.x + 8);
    init_sprite(thinking_n2_sprite, Tileset1::LOWERCASE_N, thinking_i2_sprite.x + 8);
    init_sprite(thinking_g_sprite, Tileset1::LOWERCASE_G, thinking_n2_sprite.x + 8);

    select_sprite.set_reflected_tile(Tileset1::OUTER_BORDER);
    select_sprite.set_palette(3);
    select_sprite.hide();
    select_sprite.set_behind_background(false);

    piece_sprite.set_palette(0);
    piece_sprite.hide();
    piece_sprite.set_behind_background(false);

    move_from_sprite.set_reflected_tile(Tileset1::OUTER_BORDER);
    move_from_sprite.set_palette(2);
    move_from_sprite.hide();
    move_from_sprite.set_behind_background(false);

    move_to_sprite.set_reflected_tile(Tileset1::OUTER_BORDER);
    move_to_sprite.set_palette(2);
    move_to_sprite.hide();
    move_to_sprite.set_behind_background(false);

    Ppu::wait();
    RunLengthEncoding::decompress_to(Ppu::nametable_0, BLANK_SCREEN);
    board_renderer.render_full(position.get_board());
    
    state = State::FADE_IN;
    BufferedPpu::on();
    
    screen_fader.reset_frame(Ppu::get_frame_count());
    BufferedPpu::background_palette.write(PAL0);
    BufferedPpu::sprite_palette.write(SPRITE_PALETTE);
}

auto GameScreen::fade_in() noexcept -> void {
    Ppu::wait();
    const u8 frame = Ppu::get_frame_count();
    if(screen_fader.fade_in(frame)) {
        last_update_frame = frame;
        state = player_is_white ? State::MY_TURN : State::OPPONENT_TURN;
    }
}

auto GameScreen::my_turn() noexcept -> void {
    hourglass_sprite.hide();
    thinking_t_sprite.hide();
    thinking_h_sprite.hide();
    thinking_i_sprite.hide();
    thinking_n_sprite.hide();
    thinking_k_sprite.hide();
    thinking_i2_sprite.hide();
    thinking_n2_sprite.hide();
    thinking_g_sprite.hide();

    while(true) {
        Ppu::wait();

        auto const cursor_move = [&](const bool joypad_released, const Direction direction) {
            if(!joypad_released) return;
            auto ray_direction = player_is_white ? direction : opposite_direction(direction);
            auto target_square = cursor_square.ray(ray_direction);
            if(target_square.is_valid()) cursor_square = target_square;
        };
        cursor_move(Joypad1::released.left, Direction::WEST);
        cursor_move(Joypad1::released.right, Direction::EAST);
        cursor_move(Joypad1::released.up, Direction::NORTH);
        cursor_move(Joypad1::released.down, Direction::SOUTH);


        if(Joypad1::released.a) {
            if(!selected_square.is_valid()) {
                auto const piece = position.get_board().piece_at(cursor_square);
                if(!piece.is_none() && piece.side() == NESChess::settings.player_side) {
                    selected_square = cursor_square;
                    board_renderer.hide_square(selected_square);
                    piece_sprite.set_tile(PIECES[piece.piece_type()]);
                }
            } else {
                auto const moves = chess::MoveGenerator::moves_for_piece(position, position.get_board().piece_at(selected_square));
                for(auto const & move : moves) {
                    if(!chess::MoveGenerator::is_move_legal(position, move)) continue;
                    if(move.from_square() != selected_square || move.to_square() != cursor_square) continue;

                    // TODO: Promotion selection

                    last_move = move;
                    position.make_move(last_move);
                    board_renderer.render_move(position.get_board(), last_move);
                    selected_square = Square::INVALID;
                    state = State::OPPONENT_TURN;
                    return;
                }
            }
        }
        if(Joypad1::released.b) {
            if(selected_square.is_valid()) {
                board_renderer.show_square(position.get_board(), selected_square);
                selected_square = Square::INVALID;
            }
        }

        select_sprite.set_coordinates(board_renderer.square_left_x(cursor_square)-2,board_renderer.square_top_y(cursor_square) - 2);
        if(!last_move.is_null_move()) {
            auto const from_square = last_move.from_square();
            auto const to_square = last_move.to_square();

            move_from_sprite.set_coordinates(board_renderer.square_left_x(from_square)-2, board_renderer.square_top_y(from_square)-2);
            move_to_sprite.set_coordinates(board_renderer.square_left_x(to_square)-2, board_renderer.square_top_y(to_square)-2);
        }

        if(selected_square.is_valid()) {
            piece_sprite.set_coordinates(board_renderer.square_left_x(cursor_square), board_renderer.square_top_y(cursor_square) - 2);
        } else {
            piece_sprite.hide();
        }
    }

}

auto GameScreen::opponent_turn() noexcept -> void {
    select_sprite.hide();
    piece_sprite.hide();
    move_from_sprite.hide();
    move_to_sprite.hide();
    
    hourglass_sprite.y = HOURGLASS_Y;
    thinking_t_sprite.y = hourglass_sprite.y + 8;
    thinking_h_sprite.y = hourglass_sprite.y + 8;
    thinking_i_sprite.y = hourglass_sprite.y + 8;
    thinking_n_sprite.y = hourglass_sprite.y + 8;
    thinking_k_sprite.y = hourglass_sprite.y + 8;
    thinking_i2_sprite.y = hourglass_sprite.y + 8;
    thinking_n2_sprite.y = hourglass_sprite.y + 8;
    thinking_g_sprite.y = hourglass_sprite.y + 8;

    Ppu::wait();
    u8 frame_count = Ppu::get_frame_count();
    if(HOURGLASS_DELAY < (s8)(frame_count - last_update_frame)) {
        last_update_frame = frame_count;
        hourglass_state = !hourglass_state;
        hourglass_sprite.tile_number = hourglass_state ? Tileset1::HOURGLASS : Tileset1::HOURGLASS_90;
    }

    if(chess::MoveGenerator::in_checkmate(position)) {
        const u8 lose[] = "You WIN!";
        BufferedPpu::nametable_0.write_partial(lose, 8, 12, 4);
        state = State::GAME_OVER;
        return;
    }

    ai.best_move = Move();
    ai.search(position, NESChess::settings.difficulty, 0, -30000, 30000);
    last_move = ai.best_move;
    if(last_move.is_null_move()) {
        nespp::Error::fatal_error("Error: Null Move", 16);
    }
    position.make_move(last_move);
    if(chess::MoveGenerator::in_checkmate(position)) {
       const u8 lose[] = "You LOSE!";
       BufferedPpu::nametable_0.write_partial(lose, 9, 11, 4);
       state = State::GAME_OVER;
       return;
    }

    if(chess::MoveGenerator::in_check(position)) {
        const u8 check[] = "Check!";
        BufferedPpu::nametable_0.write_partial(check, 6, 13, 4);
    } else {
        const u8 empty[] = "      ";
        BufferedPpu::nametable_0.write_partial(empty, 6, 13, 4);
    }

    board_renderer.render_move(position.get_board(), last_move);
    state = State::MY_TURN;
}

auto GameScreen::game_over() noexcept -> void {
    // TODO: Allow menu press
    Ppu::wait();
    Ppu::clear_sprites();
}

auto GameScreen::to_menu() noexcept -> void {

}

auto GameScreen::menu() noexcept -> void {

}

auto GameScreen::to_game() noexcept -> void {

}

auto GameScreen::to_title() noexcept -> void {

}
