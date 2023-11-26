/**
 * @author Steven Goldade
 * @date 11/7/2023
 */
#pragma once
#include "nespp/include/nespp/types.h"
#include <chess/piece.h>

enum class GameState : u8 {
    TITLE_SCREEN,
    IN_GAME
};

struct GameSettings {
    chess::Side player_side;
    u8 difficulty;
};

namespace NESChess {
    extern GameState state;
    extern GameSettings settings;
    
    auto run() noexcept -> void;
    auto transition_state(GameState new_state) noexcept -> void;
}
