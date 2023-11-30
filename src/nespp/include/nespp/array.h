/**
 * @author Steven Goldade
 * @date 11/11/2023
 */
#pragma once
#include "container.h"
#include "iterator.h"
#include "types.h"
#include <initializer_list>

namespace nespp {
    template <class T, size_t CAPACITY>
    struct Array {
        using data_type = T;
        using size_type = size_t;
        using iterator = T*;
        using const_iterator = const T*;

        constexpr Array() noexcept = default;
        constexpr Array(const std::initializer_list<T>& init) noexcept : data() {
            auto it = init.begin();
            for(size_t i = 0; i < init.size(); ++i)
                data[i] = it[i];
        }

        [[nodiscard]] auto constexpr at(const size_type index) const noexcept -> const T& {
            return data[index];
        }

        auto constexpr at(const size_type index) noexcept -> T& {
            return data[index];
        }

        auto constexpr operator[](const size_type index) const noexcept -> const T& {
            return at(index);
        }

        auto constexpr operator[](const size_type index) noexcept -> T& {
            return at(index);
        }

        [[nodiscard]] auto constexpr index_of(const T& value) const noexcept -> size_type {
            for(size_type i=0; i<CAPACITY; ++i)
                if(data[i] == value) return i;
            return CAPACITY;
        }

        [[nodiscard]] auto constexpr begin() const noexcept -> const_iterator {
            return data;
        }

        auto constexpr begin() noexcept -> iterator {
            return data;
        }

        [[nodiscard]] auto constexpr end() const noexcept -> const_iterator {
            return data + CAPACITY;
        }

        auto constexpr end() noexcept -> iterator {
            return data + CAPACITY;
        }

        [[nodiscard]] auto constexpr contains(const T& value) const noexcept -> bool {
            return container_contains(*this, value);
        }

        [[nodiscard]] auto consteval empty() const noexcept -> bool {
            return CAPACITY == 0;
        }

        [[nodiscard]] auto consteval size() const noexcept -> size_type {
            return CAPACITY;
        }

        [[nodiscard]] auto consteval capacity() const noexcept -> size_type {
            return CAPACITY;
        }

        template <class O, size_t OTHER_CAPACITY>
        auto constexpr operator==(const Array<O, OTHER_CAPACITY>& other) const noexcept -> bool {
            if(CAPACITY != OTHER_CAPACITY) return false;
            for(size_type i = 0; i < CAPACITY; ++i) {
                if(data[i] != other[i]) return false;
            }
            return true;
        }
    private:
        T data[CAPACITY];
    };

    static_assert(Container<Array<u8,0>>);
}// namespace nespp