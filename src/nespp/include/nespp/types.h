/**
* @author Steven Goldade
* @date 9/4/2023
*/
#pragma once
#include <cstdint>
#include <type_traits>

// Oh no, I shortened the stdint definitions and some people hate this. *shocked Pikachu face*
using u8 = uint8_t;
using s8 = int8_t;
using u16 = uint16_t;
using s16 = int16_t;
using u32 = uint32_t;
using s32 = int32_t;
using u64 = uint64_t;
using s64 = int64_t;

template <class TO, class FROM>
constexpr TO bit_cast(const FROM& from) {
    return __builtin_bit_cast(TO, from);
}

template<class T, class U>
concept Convertible = std::is_convertible_v<T, U>;

template<class T>
concept Iterable = requires(T t) {
    *t;
    t++;
    ++t;
};

template<class T>
concept IsConst = std::is_const_v<T>;

template<class T>
concept Pointer = std::is_pointer_v<T>;
