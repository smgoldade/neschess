/**
 * @author Steven Goldade
 * @date 11/29/2023
 */
#pragma once
#include "iterator.h"
#include "types.h"

template<Pointer T, bool DIRECTION, size_t CAPACITY>
struct DirectionalCircularIterator {
    constexpr DirectionalCircularIterator(const DirectionalIterator<T, DIRECTION> iterator, const size_t offset) noexcept : offset(offset), pointer(&iterator.operator*()) {}
    constexpr DirectionalCircularIterator(const T pointer, const size_t offset) noexcept :offset(offset), pointer(pointer) {}

    auto constexpr operator*() noexcept -> std::remove_pointer_t<T>& {
        return *(pointer+offset);
    }

    auto constexpr operator++() noexcept -> DirectionalCircularIterator<T, DIRECTION, CAPACITY>& {
        if constexpr(DIRECTION) {
            ++offset;
            offset %= CAPACITY;
        } else {
            --offset;
            if(offset > CAPACITY) offset = CAPACITY-1;
        }
        return *this;
    }

    auto constexpr operator++(int) noexcept -> DirectionalCircularIterator<T, DIRECTION, CAPACITY> {
        auto copy = *this;
        ++(*this);
        return copy;
    }

    auto constexpr operator==(const DirectionalCircularIterator<T, DIRECTION, CAPACITY>& other) const noexcept -> bool {
        return offset == other.offset && pointer == other.pointer;
    }
private:
    size_t offset;
    T pointer;
};

template<class T, size_t CAPACITY>
using CircularIterator = DirectionalCircularIterator<T, true, CAPACITY>;

template<class T, size_t CAPACITY>
using ReverseCircularIterator = DirectionalCircularIterator<T, false, CAPACITY>;

static_assert(Iterable<CircularIterator<u8*, 4>>);
static_assert(Iterable<ReverseCircularIterator<u8*, 4>>);