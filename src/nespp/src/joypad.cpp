/**
 * @author Steven Goldade
 * @date 11/8/2023
 */
#include "nespp/joypad.h"

u8 joypad_1_raw;
u8 joypad_2_raw;
u8 joypad_1_pressed;
u8 joypad_2_pressed;
u8 joypad_1_held;
u8 joypad_2_held;
u8 joypad_1_released;
u8 joypad_2_released;

namespace nespp {
    volatile const Joypad_Buttons& Joypad1::pressed = reinterpret_cast<Joypad_Buttons&>(joypad_1_pressed);
    volatile const Joypad_Buttons& Joypad1::held = reinterpret_cast<Joypad_Buttons&>(joypad_1_held);
    volatile const Joypad_Buttons& Joypad1::released = reinterpret_cast<Joypad_Buttons&>(joypad_1_released);
    volatile const Joypad_Buttons& Joypad2::pressed = reinterpret_cast<Joypad_Buttons&>(joypad_2_pressed);
    volatile const Joypad_Buttons& Joypad2::held = reinterpret_cast<Joypad_Buttons&>(joypad_2_held);
    volatile const Joypad_Buttons& Joypad2::released = reinterpret_cast<Joypad_Buttons&>(joypad_2_released);
}