/**
 * @author Steven Goldade
 * @date 11/27/2023
 */
#include "nespp/apu.h"

namespace nespp {
    Pulse<Apu::PULSE_1> Apu::pulse_1;
    Pulse<Apu::PULSE_2> Apu::pulse_2;

    Apu::Initializer::Initializer() {
        Apu::control() = {.value = 0};

        ApuFrameCounter frame_counter = {.value = 0};
        Apu::frame_counter() = frame_counter;
    }
    Apu::Initializer Apu::init;
}