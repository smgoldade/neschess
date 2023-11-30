/**
 * @author Steven Goldade
 * @date 11/12/2023
 */
#pragma once
#include "types.h"

template<Pointer T, bool DIRECTION>
struct DirectionalIterator {
    explicit constexpr DirectionalIterator(const T pointer) noexcept : pointer(pointer) {}

    auto constexpr operator*() const noexcept -> std::remove_pointer_t<T>& {
        return *pointer;
    }

    auto constexpr operator++() noexcept -> DirectionalIterator<T, DIRECTION>& {
        if constexpr(DIRECTION) {
            ++pointer;
        } else {
            --pointer;
        }
        return *this;
    }

    auto constexpr operator++(int) noexcept -> DirectionalIterator<T, DIRECTION> {
        auto copy(*this);
        ++(*this);
        return copy;
    }

    auto constexpr operator==(const DirectionalIterator<T, DIRECTION>& other) const noexcept -> bool {
        return pointer == other.pointer;
    }
private:
    T pointer;
};

template<Pointer T>
using Iterator = DirectionalIterator<T, true>;

template<Pointer T>
using ReverseIterator = DirectionalIterator<T, false>;

static_assert(Iterable<Iterator<u8*>>);
static_assert(Iterable<ReverseIterator<u8*>>);