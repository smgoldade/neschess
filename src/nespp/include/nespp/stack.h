/**
 * @author Steven Goldade
 * @date 10/26/2023
 */
#pragma once
#include "array.h"
#include "container.h"
#include "error.h"
#include "reverse_iterator.h"
#include "types.h"

namespace nespp {
    template <class T, size_t CAPACITY>
    class Stack {
    public:
        using data_type = T;
        using size_type = size_t;
        using iterator = ReverseIterator<const T*>;
        using const_iterator = ReverseIterator<const T* const>;

        constexpr Stack() noexcept : internal_size(0), data(){};
        constexpr Stack(const std::initializer_list<T>& init) noexcept : data() {
            internal_size = init.size();
            auto it = init.begin();
            for(size_t i = 0; i < init.size(); ++i)
                data[i] = it[i];
        }

        auto constexpr push(const T& value) noexcept -> void {
            if(internal_size == CAPACITY) {
                Error::fatal_error("Stack overflow", 14);
            }
            data[internal_size++] = value;
        }

        auto constexpr pop() noexcept -> const T& {
            if(internal_size == 0) {
                Error::fatal_error("Stack underflow", 15);
            }
            return data[--internal_size];
        }

        [[nodiscard]] auto constexpr peek() const noexcept -> const T& {
            if(internal_size == 0) {
                Error::fatal_error("Stack underflow", 15);
            }
            return data[internal_size - 1];
        }

        [[nodiscard]] auto constexpr begin() const noexcept -> const_iterator {
            return const_iterator{data.begin() + internal_size - 1};
        }

        auto constexpr begin() noexcept -> iterator {
            return iterator{data.begin() + internal_size - 1};
        }

        [[nodiscard]] auto constexpr end() const noexcept -> const_iterator {
            return const_iterator{data.begin()};
        }

        auto constexpr end() noexcept -> iterator {
            return iterator{data.begin()};
        }

        [[nodiscard]] auto constexpr contains(const T& value) const noexcept -> bool {
            for(size_type i = 0; i < internal_size; i++) {
                if(data[i] == value) return true;
            }
            return false;
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
        auto constexpr operator==(const Stack<O, OTHER_CAPACITY>& other) const noexcept -> bool {
            if(CAPACITY != OTHER_CAPACITY) return false;
            if(internal_size != other.internal_size) return false;
            for(size_type i = 0; i < internal_size; ++i) {
                if(data[i] != other.data[i]) return false;
            }
            return true;
        }

    private:
        size_type internal_size;
        Array<T, CAPACITY> data;
    };

    static_assert(Container<Stack<u8, 0>>);
}// namespace nespp