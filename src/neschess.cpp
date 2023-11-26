/**
 * @author Steven Goldade
 * @date 11/7/2023
 */
#include "neschess.h"
#include "game_screen.h"
#include "title_screen.h"

namespace NESChess {
    GameState state = GameState::TITLE_SCREEN;
    GameSettings settings = {chess::Side::WHITE, 1};
    static TitleScreen title_screen;
    static GameScreen game_screen;
    
    auto run() noexcept -> void {
        switch(state) {
            case GameState::TITLE_SCREEN:
                title_screen.run();
                break;
            case GameState::IN_GAME:
                game_screen.run();
                break;
        }
    }
    
    auto transition_state(GameState new_state) noexcept -> void {
        state = new_state;
    }
}


