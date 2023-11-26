/**
 * @author Steven Goldade
 * @date 11/7/2023
 */
#pragma once
#include "board_renderer.h"
#include "chess/ai.h"
#include "neschess.h"
#include "nespp/include/nespp/types.h"
#include "screen_fader.h"
#include <chess/move_generator.h>
#include <chess/position.h>
#include <nespp/metasprite.h>
#include <nespp/palette.h>

class GameScreen {
public:
    constexpr GameScreen() : state(State::INIT), position(), board_renderer(false, 4, 3), screen_fader(FADE_DELAY, PAL0, PAL1, PAL2, FINAL_PALETTE), player_is_white(false), last_update_frame(0), hourglass_state(true){};

    auto constexpr run() noexcept -> void {
        switch(state) {
            case State::INIT:
                init();
                break;
            case State::FADE_IN:
                fade_in();
                break;
            case State::MY_TURN:
                my_turn();
                break;
            case State::OPPONENT_TURN:
                opponent_turn();
                break;
            case State::GAME_OVER:
                game_over();
                break;
            case State::TO_MENU:
                to_menu();
                break;
            case State::MENU:
                menu();
                break;
            case State::TO_GAME:
                to_game();
                break;
            case State::TO_TITLE:
                to_title();
                break;
        }
    }

    auto init() noexcept -> void;
    auto fade_in() noexcept -> void;
    auto my_turn() noexcept -> void;
    auto opponent_turn() noexcept -> void;
    auto game_over() noexcept -> void;
    auto to_menu() noexcept -> void;
    auto menu() noexcept -> void;
    auto to_game() noexcept -> void;
    auto to_title() noexcept -> void;

private:
    static constexpr u8 BLANK_SCREEN[] = {
        0x69, 0x00, 0x69, 0xFF, 0x00, 0x69, 0xFF, 0x00, 0x69, 0xFF, 0x00, 0x69, 0xFF, 0x69, 0x00
    };
    static constexpr Palette FINAL_PALETTE = {
        Color::BLACK,
        {Color::WHITE, Color::BLACK, Color::LIGHT_ORANGE},
        Color::BLACK,
        {Color::WHITE, Color::BLACK, Color::MEDIUM_ORANGE},
        Color::BLACK,
        {Color::WHITE, Color::MEDIUM_GRAY, Color::WHITE},
        Color::BLACK,
        {Color::DARK_RED, Color::MEDIUM_GRAY, Color::WHITE}
    };
    static constexpr Palette PAL2 = FINAL_PALETTE.darken();
    static constexpr Palette PAL1 = PAL2.darken();
    static constexpr Palette PAL0 = PAL1.darken();
    static constexpr Palette SPRITE_PALETTE = {
        Color::BLACK,
        {Color::WHITE, Color::BLACK, Color::LIGHT_ORANGE},
        Color::BLACK,
        {Color::WHITE, Color::BLACK, Color::MEDIUM_ORANGE},
        Color::BLACK,
        {Color::LIGHT_BLUE, Color::MEDIUM_BLUE, Color::WHITE},
        Color::BLACK,
        {Color::DARK_RED, Color::MEDIUM_GRAY, Color::WHITE}
    };

    static constexpr u8 FADE_DELAY = 5;
    static constexpr u8 HOURGLASS_DELAY = 20;
    
    static constexpr u8 HOURGLASS_X = 124;
    static constexpr u8 HOURGLASS_Y = 100;
    
    static constexpr u8 PIECES[] = {
        Tileset1::HOURGLASS,
        Tileset1::WHITE_PAWN,
        Tileset1::WHITE_KNIGHT,
        Tileset1::WHITE_BISHOP,
        Tileset1::WHITE_ROOK,
        Tileset1::WHITE_QUEEN,
        Tileset1::WHITE_KING,
        Tileset1::BLACK_PAWN,
        Tileset1::BLACK_KNIGHT,
        Tileset1::BLACK_BISHOP,
        Tileset1::BLACK_ROOK,
        Tileset1::BLACK_QUEEN,
        Tileset1::BLACK_KING,
    };

    enum class State {
        INIT,
        FADE_IN,
        MY_TURN,
        OPPONENT_TURN,
        GAME_OVER,
        TO_MENU,
        MENU,
        TO_GAME,
        TO_TITLE,
    };
    State state;
    Position position;
    BoardRenderer board_renderer;
    ScreenFader screen_fader;
    bool player_is_white;
    u8 last_update_frame;
    bool hourglass_state;
    Square cursor_square;
    Square selected_square;
    Move last_move;
    chess::AI ai;

    PpuSprite& hourglass_sprite = Ppu::sprites[0];
    PpuSprite& thinking_t_sprite = Ppu::sprites[1];
    PpuSprite& thinking_h_sprite = Ppu::sprites[2];
    PpuSprite& thinking_i_sprite = Ppu::sprites[3];
    PpuSprite& thinking_n_sprite = Ppu::sprites[4];
    PpuSprite& thinking_k_sprite = Ppu::sprites[5];
    PpuSprite& thinking_i2_sprite = Ppu::sprites[6];
    PpuSprite& thinking_n2_sprite = Ppu::sprites[7];
    PpuSprite& thinking_g_sprite = Ppu::sprites[8];
    Metasprite select_sprite = Metasprite(9, 12, 12);
    Metasprite piece_sprite = Metasprite(13);
    Metasprite move_from_sprite = Metasprite(17, 12, 12);
    Metasprite move_to_sprite = Metasprite(21, 12, 12);
};
