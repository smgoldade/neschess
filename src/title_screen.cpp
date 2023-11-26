/**
 * @author Steven Goldade
 * @date 11/7/2023
 */
#include "title_screen.h"
#include "nespp/include/nespp/nesmath.h"
#include "tileset.h"
#include <nespp/compression.h>
#include <nespp/joypad.h>

using namespace nespp;
using namespace nespp;

auto TitleScreen::init() noexcept -> void {
    BufferedPpu::off();
    Ppu::wait();

    Ppu::wait();
    BufferedPpu::control.nametable = 0;
    BufferedPpu::control.background_pattern_table = 1;
    BufferedPpu::control.sprite_pattern_table = 0;
    BufferedPpu::mask.render_left8_background = true;
    BufferedPpu::mask.render_left8_sprites = true;

    Ppu::wait();
    RunLengthEncoding::decompress_to(Ppu::nametable_0, TITLE_SCREEN);
    
    side_sprite.x = 124;
    side_sprite.y = 172;
    side_sprite.horizontal_flip = false;
    side_sprite.vertical_flip = false;
    side_sprite.behind_background = false;
    
    difficulty_sprite.x = 124;
    difficulty_sprite.y = 196;
    difficulty_sprite.horizontal_flip = false;
    difficulty_sprite.vertical_flip = false;
    difficulty_sprite.behind_background = false;
    
    left_cursor_sprite.tile_number = Tileset0::ARROW_LEFT;
    left_cursor_sprite.palette = 3;
    left_cursor_sprite.horizontal_flip = false;
    left_cursor_sprite.vertical_flip = false;
    left_cursor_sprite.behind_background = false;
    
    right_cursor_sprite.tile_number = Tileset0::ARROW_LEFT;
    right_cursor_sprite.palette = 3;
    right_cursor_sprite.horizontal_flip = true;
    right_cursor_sprite.vertical_flip = false;
    right_cursor_sprite.behind_background = false;
    
    state = State::FADE_IN;
    BufferedPpu::on();

    BufferedPpu::background_palette.write(PAL0);
    BufferedPpu::sprite_palette.write(SPRITE_PALETTE);
    screen_fader.reset_frame(Ppu::get_frame_count());
}

auto TitleScreen::fade_in() noexcept -> void {
    Ppu::wait();
    const u8 frame = Ppu::get_frame_count();
    if(screen_fader.fade_in(frame)) {
        state = State::RUNNING;
    }
}

auto TitleScreen::running() noexcept -> void {
    Ppu::wait();

    
    switch(NESChess::settings.player_side) {
        case chess::Side::WHITE:
            side_sprite.tile_number = Tileset0::SMALL_KNIGHT;
            side_sprite.palette = 1;
            break;
        case chess::Side::BLACK:
            side_sprite.tile_number = Tileset0::SMALL_KNIGHT;
            side_sprite.palette = 0;
            break;
        default:
        case chess::Side::NONE: // none will be used for random
            side_sprite.tile_number = '?';
            side_sprite.palette = 3;
            break;
    }
    
    difficulty_sprite.tile_number = NESChess::settings.difficulty + '0';
    difficulty_sprite.palette = 3;
    
    switch(cursor_position) {
        case CursorPosition::SIDE:
            left_cursor_sprite.x = 112;
            left_cursor_sprite.y = NESChess::settings.player_side == chess::Side::WHITE ? 255 : 172;
            right_cursor_sprite.x = 136;
            right_cursor_sprite.y = NESChess::settings.player_side == chess::Side::NONE ? 255 : 172;
            if(Joypad1::released.down) cursor_position = CursorPosition::DIFFICULTY;
            if(Joypad1::released.left) NESChess::settings.player_side = NESChess::settings.player_side == chess::Side::NONE ? chess::Side::BLACK : chess::Side::WHITE;
            if(Joypad1::released.right) NESChess::settings.player_side = NESChess::settings.player_side == chess::Side::WHITE ? chess::Side::BLACK : chess::Side::NONE;
            break;
        case CursorPosition::DIFFICULTY:
            left_cursor_sprite.x = 112;
            left_cursor_sprite.y = NESChess::settings.difficulty == 1 ? 255 : 196;
            right_cursor_sprite.x = 136;
            right_cursor_sprite.y = NESChess::settings.difficulty == 5 ? 255 : 196;
            if(Joypad1::released.up) cursor_position = CursorPosition::SIDE;
            if(Joypad1::released.down) cursor_position = CursorPosition::PLAY;
            if(Joypad1::released.left) NESChess::settings.difficulty = max(1, NESChess::settings.difficulty - 1);
            if(Joypad1::released.right) NESChess::settings.difficulty = min(5, NESChess::settings.difficulty + 1);
            break;
        default:
        case CursorPosition::PLAY:
            left_cursor_sprite.x = 144;
            left_cursor_sprite.y = 208;
            left_cursor_sprite.palette = 3;
            right_cursor_sprite.x = 104;
            right_cursor_sprite.y = 208;
            right_cursor_sprite.palette = 3;
            if(Joypad1::released.up) cursor_position = CursorPosition::DIFFICULTY;
            if(Joypad1::released.a || Joypad1::released.start)  {
                screen_fader.reset_frame(Ppu::get_frame_count());
                state = State::FADE_OUT;
                Ppu::wait();
            }
            break;
    }
}
auto TitleScreen::fade_out() noexcept -> void {
    Ppu::wait();
    const u8 frame = Ppu::get_frame_count();
    if(screen_fader.fade_out(frame)) {
        state = State::OFF_SCREEN;
    }
}
