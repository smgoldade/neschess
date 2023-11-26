/**
 * @author Steven Goldade
 * @date 10/27/2023
 */
#pragma once
#include <type_traits>

namespace nespp {
    template <class T> requires std::is_integral_v<T>
    auto constexpr min(T a, T b) -> T {
        return ((a < b) ? a : b);
    }

    template <class T> requires std::is_integral_v<T>
    auto constexpr max(T a, T b) -> T {
        return ((a > b) ? a : b);
    }

    template <class T, T MIN, T MAX> requires std::is_integral_v<T>
    auto constexpr clamp(T value) -> T {
        static_assert(MAX > MIN);
        return min(MAX, max(MIN, value));
    }
    
    template <class T> requires std::is_integral_v<T>
    auto constexpr abs(T value) -> T  {
        if(value < 0) {
            return -value; // this could overflow and go kaboom
        }
        return value;
    }

    template <s8>
    auto constexpr abs(s8 value) -> s8  {
        if(value < 0) {
            if(value == -128) return 127;
            return static_cast<s8>(-value);
        }
        return value;
    }

    template <s16>
    auto constexpr abs(s16 value) -> s16  {
        if(value < 0) {
            if(value == -32768) return 32767;
            return static_cast<s8>(-value);
        }
        return value;
    }
}// namespace nespp
