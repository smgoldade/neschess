/**
* @author Steven Goldade
* @date 11/12/2023
*/
#pragma once
#include "array.h"
#include "container.h"
#include "error.h"
#include "types.h"

namespace nespp {
    auto static constexpr ILLEGAL_VECTOR_ACCESS = "Illegal vector access";
    static constexpr u16 ILLEGAL_VECTOR_ACCESS_SIZE = 21;

    template <class T, size_t CAPACITY>
    class Vector {
    public:
        using data_type = T;
        using size_type = size_t;
        using iterator = const T*;
        using const_iterator = const T*;

        constexpr Vector() noexcept : internal_size(0), data(){};
        constexpr Vector(const std::initializer_list<T> init) noexcept : data() {
            internal_size = init.size();
            auto it = init.begin();
            for(size_type i = 0; i < init.size(); ++i)
                data[i] = it[i];
        }
        template <size_type CAPACITY2> requires(CAPACITY2 <= CAPACITY)
        explicit constexpr Vector(const Vector<T, CAPACITY2>& other) noexcept : internal_size(0), data() {
            push_back_all(other);
        }

        [[nodiscard]] auto constexpr at(const size_type index) const noexcept -> const T& {
            if(index >= internal_size)
                Error::fatal_error(ILLEGAL_VECTOR_ACCESS, ILLEGAL_VECTOR_ACCESS_SIZE);
            return data[index];
        }

        auto constexpr at(const size_type index) noexcept -> T& {
            if(index >= internal_size)
                Error::fatal_error(ILLEGAL_VECTOR_ACCESS, ILLEGAL_VECTOR_ACCESS_SIZE);
            return data[index];
        }

        auto constexpr operator[](const size_type index) const noexcept -> const T& {
            return at(index);
        }

        auto constexpr operator[](const size_type index) noexcept -> T& {
            return at(index);
        }

        auto constexpr push_back(const T& value) noexcept -> void {
            if(internal_size == CAPACITY) return;
            data[internal_size++] = value;
        }

        template <size_type CAPACITY2> requires(CAPACITY2 <= CAPACITY)
        auto constexpr push_back_all(const Vector<T, CAPACITY2>& vector) noexcept -> void {
            for(size_type i = 0; i < vector.size(); ++i) {
                push_back(vector[i]);
            }
        }

        auto constexpr push_front(const T& value) noexcept -> void {
            if(internal_size == CAPACITY) return;
            for(size_type i = internal_size; i >= 1; --i) {
                data[i] = data[i - 1];
            }
            data[0] = value;
            ++internal_size;
        }

        [[nodiscard]] auto constexpr index_of(const T& value) const noexcept -> size_t {
            for(size_type i = 0; i < internal_size; ++i)
                if(data[i] == value) return i;
            return CAPACITY;
        }

        [[nodiscard]] auto constexpr begin() const noexcept -> const_iterator {
            return data.begin();
        }

        auto constexpr begin() noexcept -> iterator {
            return data.begin();
        }

        [[nodiscard]] auto constexpr end() const noexcept -> const_iterator {
            return data.begin() + internal_size;
        }

        auto constexpr end() noexcept -> iterator {
            return data.begin() + internal_size;
        }

        [[nodiscard]] auto constexpr contains(const T& value) const noexcept -> bool {
            return index_of(value) != CAPACITY;
        }

        [[nodiscard]] auto constexpr empty() const noexcept -> bool {
            return internal_size == 0;
        }

        [[nodiscard]] auto constexpr size() const noexcept -> size_type {
            return internal_size;
        }

        [[nodiscard]] auto consteval capacity() const noexcept -> size_type {
            return CAPACITY;
        }

        template <class O, size_t OTHER_CAPACITY>
        auto constexpr operator==(const Vector<O, OTHER_CAPACITY>& other) const noexcept -> bool {
            if(CAPACITY != OTHER_CAPACITY) return false;
            if(internal_size != other.internal_size) return false;
            for(size_type i = 0; i < internal_size; ++i) {
                if(data[i] != other[i]) return false;
            }
            return true;
        }

    private:
        size_type internal_size;
        Array<T, CAPACITY> data;
    };

    static_assert(Container<Vector<u8, 0>>);
}// namespace nespp