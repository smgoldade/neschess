/**
 * @author Steven Goldade
 * @date 11/8/2023
 */
#pragma once
#include "low_level.h"
#include "types.h"

extern "C" LEAF INTERRUPT_NO_RECURSE void __poll_joypad(); // NOLINT(*-reserved-identifier)

namespace nespp {
    struct Joypad_Buttons {
        const bool right : 1;
        const bool left : 1;
        const bool down : 1;
        const bool up : 1;
        const bool start : 1;
        const bool select : 1;
        const bool b : 1;
        const bool a : 1;
    };
    
    struct Joypad1 {
        volatile static const Joypad_Buttons& pressed;
        volatile static const Joypad_Buttons& released;
        volatile static const Joypad_Buttons& held;
        Joypad1() = delete;
    };
    
    struct Joypad2 {
        volatile static const Joypad_Buttons& pressed;
        volatile static const Joypad_Buttons& released;
        volatile static const Joypad_Buttons& held;
        Joypad2() = delete;
    };
}