/**
 * @author Steven Goldade
 * @date 11/12/2023
 */
#pragma once
#include "types.h"

template<Pointer T>
struct ReverseIterator {
    explicit constexpr ReverseIterator(const T pointer) noexcept : pointer(pointer) {}

    auto constexpr operator*() noexcept -> std::remove_pointer_t<T>& {
        return *pointer;
    }

    auto constexpr operator++() noexcept -> ReverseIterator<T>& {
        pointer--;
        return *this;
    }

    auto constexpr operator++(int) noexcept -> ReverseIterator<T>& {
        pointer--;
        return *this;
    }

    auto constexpr operator==(const ReverseIterator<T>& other) const noexcept -> bool {
        return pointer == other.pointer;
    }
private:
    T pointer;
};
static_assert(Iterable<ReverseIterator<u8*>>);