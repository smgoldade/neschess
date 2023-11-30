/**
 * @author Steven Goldade
 * @date 11/27/2023
 */
#pragma once
#include "circular_queue.h"
#include "low_level.h"
#include "types.h"

namespace nespp {
    enum class Pitch : u8 {
        A1 = 0, Bb1, B1, C1,Db1,D1,Eb1,E1,F1,Gb1,G1,Ab1,
        A2,Bb2,B2,C2,Db2,D2,Eb2,E2,F2,Gb2,G2,Ab2,
        A3,Bb3,B3,C3,Db3,D3,Eb3,E3,F3,Gb3,G3,Ab3,
        A4,Bb4,B4,C4,Db4,D4,Eb4,E4,F4,Gb4,G4,Ab4,
        A5,Bb5,B5,C5,Db5,D5,Eb5,E5,F5,Gb5,G5,Ab5,
        A6,Bb6,B6,C6,Db6,D6,Eb6,E6,F6,Gb6,G6,Ab6,
        A7,Bb7,B7,C7,Db7,D7,Eb7,E7,F7,Gb7,G7,Ab7,
        A8,Bb8,B8,C8,Db8,D8,Eb8,E8,F8,Gb8,
    };

    static constexpr u8 PERIOD_HIGH[] = {
        0x7,0x7,0x7,0x6,0x6,0x5,0x5,0x5,0x5,0x4,0x4,0x4,
        0x3,0x3,0x3,0x3,0x3,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
        0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    };
    
    static constexpr u8 PERIOD_LOW[] = {
        0xF1, 0x80, 0x13, 0xAD, 0x4D, 0xF3, 0x9D, 0x4D, 0x00, 0xB8, 0x75, 0x35,
        0xF8, 0xBF, 0x89, 0x56, 0x26, 0xF9, 0xCE, 0xA6, 0x7F, 0x5C, 0x3A, 0x1A,
        0xFB, 0xDF, 0xC4, 0xAB, 0x93, 0x7C, 0x67, 0x52, 0x3F, 0x2D, 0x1C, 0x0C,
        0xFD,0xEF,0xE2,0xD2,0xC9,0xBD,0xB3,0xA9,0x9F,0x96,0x8E,0x86,
        0x7E,0x77,0x70,0x6A,0x64,0x5E,0x59,0x54,0x4F,0x4B,0x46,0x42,
        0x3F,0x3B,0x38,0x34,0x31,0x2F,0x2C,0x29,0x27,0x25,0x23,0x21,
        0x1F,0x1D,0x1B,0x1A,0x18,0x17,0x15,0x14,0x13,0x12,0x11,0x10,
        0x0F,0x0E,0x0D,0x0C,0xC,0x0B,0x0A,0x0A,0x09,0x08
    };

    enum class Length {
        _2_1_SECONDS = 0x01,
        _1_6_SECONDS = 0x18,
        _1_333_SECONDS = 0x08,
        _0_8_SECONDS = 0x16,
        _0_666_SECONDS = 0x06,
        _0_6_SECONDS = 0x1A,
        _0_5_SECONDS = 0x0A,
        _0_4_SECONDS = 0x14,
        _0_333_SECONDS = 0x04,
        _0_266_SECONDS = 0x1E,
        _0_25_SECONDS = 0x1F,
        _0_233_SECONDS = 0x1D,
        _0_216_SECONDS = 0x1B,
        _0_2_SECONDS = 0x19,
        _0_183_SECONDS = 0x17,
        _0_166_SECONDS = 0x15,
        _0_15_SECONDS = 0x13,
        _0_133_SECONDS = 0x11,
        _0_116_SECONDS = 0x0F,
        _0_1_SECONDS = 0x0D,
        _0_083_SECONDS = 0x0B,
        _0_066_SECONDS = 0x09,
        _0_05_SECONDS = 0x07,
        _0_033_SECONDS = 0x05,
        _0_016_SECONDS = 0x03,

        _150_BPM_WHOLE = 0x18,
        _150_BPM_HALF = 0x16,
        _150_BPM_DOTTED_QUARTER = 0x1A,
        _150_BPM_QUARTER = 0x14,
        _150_BPM_QUARTER_TRIPLET = 0x1E,
        _150_BPM_EIGHTH = 0x12,
        _150_BPM_EIGHTH_TRIPLET = 0x1C,
        _150_BPM_SIXTEENTH = 0x10,

        _180_BPM_WHOLE = 0x08,
        _180_BPM_HALF = 0x06,
        _180_BPM_DOTTED_QUARTER = 0x0A,
        _180_BPM_QUARTER = 0x04,
        _180_BPM_QUARTER_TRIPLET = 0x0E,
        _180_BPM_EIGHTH = 0x02,
        _180_BPM_EIGHTH_TRIPLET = 0x0C,
        _180_BPM_SIXTEENTH = 0x00,
    };

    struct Note {
        Pitch pitch;
        Length length;
        u8 volume;

        constexpr Note() noexcept : pitch(Pitch::A1), length(Length::_180_BPM_SIXTEENTH), volume(0) {}
        constexpr Note(const Pitch pitch, const Length length, const u8 volume) noexcept : pitch(pitch), length(length), volume(volume) {}
    };
    
    enum class PulseDuty : u8 {
        _12_5 = 0,
        _25 = 1,
        _50 = 2,
        _75 = 3
    };

    union PulseEnvelope {
        struct {
            u8 volume : 4;
            bool constant_volume : 1;
            bool loop_envelope : 1;
            PulseDuty duty : 2;
        };
        u8 value;

        auto constexpr operator=(const PulseEnvelope& other) volatile noexcept -> volatile PulseEnvelope& {
            value = other.value;
            return *this;
        }
    };

    union PulseSweep {
        struct {
            u8 shift_count : 3;
            bool negate_flag : 1;
            u8 divider : 3;
            bool enabled : 1;
        };
        u8 value;

        auto constexpr operator=(const PulseSweep& other) volatile noexcept -> volatile PulseSweep& {
            value = other.value;
            return *this;
        }
    };

    union PulseLength {
        struct {
            u8 timer_high : 3;
            Length length : 5;
        };
        u8 value;

        auto constexpr operator=(const PulseLength& other) volatile noexcept -> volatile PulseLength& {
            value = other.value;
            return *this;
        }
    };

    template<u16 ADDRESS>
    struct Pulse {
        WriteOnly<PulseEnvelope, ADDRESS> envelope;
        WriteOnly<PulseSweep, ADDRESS+1> sweep;
        WriteOnly<u8, ADDRESS+2> timer_low;
        WriteOnly<PulseLength, ADDRESS+3> length;

        CircularQueue<Note, 10> play_queue;

        auto constexpr queue_note(const Note& note) {
            play_queue.push_back(note);
        }
        auto constexpr queue_note(const Pitch pitch, const Length length, const u8 volume) {
            play_queue.push_back({pitch, length, volume});
        }
    };

    union ApuControl {
        struct {
            bool pulse_1_length_enabled : 1;
            bool pulse_2_length_enabled : 1;
            bool triangle_length_enabled : 1;
            bool noise_length_enabled : 1;
            bool dmc_enable : 1;
            bool unused : 1;
            bool frame_interrupt : 1;
            bool dmc_interrupt : 1;
        };
        u8 value;

        auto constexpr operator=(const ApuControl& other) volatile noexcept -> volatile ApuControl& {
            value = other.value;
            return *this;
        }
    };

    enum class FrameCounterMode : u8 {
        _4_STEP = 0,
        _5_STEP = 1,
    };

    union ApuFrameCounter {
        struct {
            u8 unused : 6;
            bool irq_inhibit : 1;
            FrameCounterMode mode : 1;
        };
        u8 value;

        auto constexpr operator=(const ApuFrameCounter& other) volatile noexcept -> volatile ApuFrameCounter& {
            value = other.value;
            return *this;
        }
    };

    struct Apu {
        Apu() = delete;
        ~Apu() = delete;

        static constexpr u16 PULSE_1 = 0x4000;
        static Pulse<PULSE_1> pulse_1;

        static constexpr u16 PULSE_2 = 0x4004;
        static Pulse<PULSE_2> pulse_2;

        static constexpr u16 APU_CONTROL = 0x4015;
        auto static constexpr control() noexcept -> WriteOnly<ApuControl, APU_CONTROL> {
            return {};
        }

        auto static constexpr status() noexcept -> volatile const ApuControl& {
            return read_only_memory<ApuControl>(APU_CONTROL);
        }

        static constexpr u16 APU_FRAME_COUNTER = 0x4017;
        auto static constexpr frame_counter() noexcept -> WriteOnly<ApuFrameCounter, APU_FRAME_COUNTER> {
            return {};
        }
    private:
        friend void ::__nmi_update();

        auto static constexpr background_update() -> void {
            auto constexpr play_note = [&](bool playing, auto & pulse) {
                if(playing) return;
                if(pulse.play_queue.empty()) return;
                auto & note = pulse.play_queue.pop_front();

                pulse.envelope = {.duty = PulseDuty::_50, .loop_envelope = false, .constant_volume = true, .volume = static_cast<u8>(note.volume & 0xF)};
                pulse.timer_low = PERIOD_LOW[static_cast<u8>(note.pitch)];
                pulse.length = PulseLength{.length = note.length, .timer_high = PERIOD_HIGH[static_cast<u8>(note.pitch)]};
            };
            play_note(status().pulse_1_length_enabled, pulse_1);
            play_note(status().pulse_2_length_enabled, pulse_2);
        }

        struct Initializer {
            Initializer();
        };
        static Initializer init;
    };
}