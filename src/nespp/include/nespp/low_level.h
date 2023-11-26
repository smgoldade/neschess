/**
 * @author Steven Goldade
 * @date 10/26/2023
 */
#pragma once
#include "types.h"

#ifdef __mos6502__
    #define LEAF __attribute__((leaf))
    #define NONREENTRANT __attribute__((nonreentrant))
#else
    #define LEAF
    #define NONREENTRANT
#endif

namespace nespp {
    template <class T>
    auto constexpr read_only_memory(const u16 address) noexcept -> const volatile T& {
        return *bit_cast<const volatile T*>(address);
    }
    
    template <class T>
    auto constexpr memory(const u16 address) noexcept -> volatile T& {
        return *bit_cast<volatile T*>(address);
    }
    
    template <class T, u16 ADDRESS>
    struct WriteOnly {
        constexpr WriteOnly() = default;
        
        auto constexpr operator=(const T& value) volatile noexcept -> void { // NOLINT(*-unconventional-assign-operator) Return void to prevent chaining as this is WRITE ONLY
            memory<T>(ADDRESS) = value;
        }
    };
}// namespace nespp
