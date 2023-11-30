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
    static constexpr nespp::Palette FINAL_PALETTE = {
        nespp::Color::BLACK,
        {nespp::Color::WHITE, nespp::Color::BLACK, nespp::Color::LIGHT_ORANGE},
        nespp::Color::BLACK,
        {nespp::Color::WHITE, nespp::Color::BLACK, nespp::Color::MEDIUM_ORANGE},
        nespp::Color::BLACK,
        {nespp::Color::WHITE, nespp::Color::MEDIUM_GRAY, nespp::Color::WHITE},
        nespp::Color::BLACK,
        {nespp::Color::DARK_RED, nespp::Color::MEDIUM_GRAY, nespp::Color::WHITE}
    };
    static constexpr nespp::Palette PAL2 = FINAL_PALETTE.darken();
    static constexpr nespp::Palette PAL1 = PAL2.darken();
    static constexpr nespp::Palette PAL0 = PAL1.darken();
    static constexpr nespp::Palette SPRITE_PALETTE = {
        nespp::Color::BLACK,
        {nespp::Color::WHITE, nespp::Color::BLACK, nespp::Color::LIGHT_ORANGE},
        nespp::Color::BLACK,
        {nespp::Color::WHITE, nespp::Color::BLACK, nespp::Color::MEDIUM_ORANGE},
        nespp::Color::BLACK,
        {nespp::Color::LIGHT_BLUE, nespp::Color::MEDIUM_BLUE, nespp::Color::WHITE},
        nespp::Color::BLACK,
        {nespp::Color::DARK_RED, nespp::Color::MEDIUM_GRAY, nespp::Color::WHITE}
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
    chess::Position position;
    BoardRenderer board_renderer;
    ScreenFader screen_fader;
    bool player_is_white;
    u8 last_update_frame;
    bool hourglass_state;
    chess::Square cursor_square;
    chess::Square selected_square;
    chess::Move last_move;
    chess::AI ai;

    nespp::PpuSprite& hourglass_sprite = nespp::Ppu::sprites[0];
    nespp::PpuSprite& thinking_t_sprite = nespp::Ppu::sprites[1];
    nespp::PpuSprite& thinking_h_sprite = nespp::Ppu::sprites[2];
    nespp::PpuSprite& thinking_i_sprite = nespp::Ppu::sprites[3];
    nespp::PpuSprite& thinking_n_sprite = nespp::Ppu::sprites[4];
    nespp::PpuSprite& thinking_k_sprite = nespp::Ppu::sprites[5];
    nespp::PpuSprite& thinking_i2_sprite = nespp::Ppu::sprites[6];
    nespp::PpuSprite& thinking_n2_sprite = nespp::Ppu::sprites[7];
    nespp::PpuSprite& thinking_g_sprite = nespp::Ppu::sprites[8];
    nespp::Metasprite select_sprite = nespp::Metasprite(9, 12, 12);
    nespp::Metasprite piece_sprite = nespp::Metasprite(13);
    nespp::Metasprite move_from_sprite = nespp::Metasprite(17, 12, 12);
    nespp::Metasprite move_to_sprite = nespp::Metasprite(21, 12, 12);
};
