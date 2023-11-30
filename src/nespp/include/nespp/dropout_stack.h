/**
 * @author Steven Goldade
 * @date 11/26/2023
 */
#pragma once
#include "array.h"
#include "container.h"
#include "error.h"
#include "circular_iterator.h"
#include "nesmath.h"
#include "types.h"

namespace nespp {
    template <class T, size_t CAPACITY>
    class DropoutStack {
    public:
        using data_type = T;
        using size_type = size_t;
        using iterator = ReverseCircularIterator<T*, CAPACITY>;
        using const_iterator = ReverseCircularIterator<const T*, CAPACITY>;

        constexpr DropoutStack() noexcept : pointer(0), count(0), data(){};
        constexpr DropoutStack(const std::initializer_list<T>& init) noexcept : pointer(init.size()), count(init.size()), data() {
            auto it = init.begin();
            for(size_t i = 0; i < count; ++i)
                data[i] = it[i];
        }

        auto constexpr push(const T& value) noexcept -> void {
            data[pointer++] = value;
            count++;
            count = min(count, CAPACITY);
            pointer %= CAPACITY;
        }

        auto constexpr pop() noexcept -> const T& {
            if(pointer == 0) {
                pointer = CAPACITY;
            }
            count--;
            if(count > CAPACITY) count = 0;
            return data[--pointer];
        }

        [[nodiscard]] auto constexpr peek() const noexcept -> const T& {
            if(pointer-1 == 0xFFFF) {
                return data[CAPACITY - 1];
            }
            return data[(pointer - 1)];
        }

        [[nodiscard]] auto constexpr begin() const noexcept -> const_iterator {
            return const_iterator { data.begin(), static_cast<size_t>(count-pointer) };
        }

        auto constexpr begin() noexcept -> iterator {
            return iterator { data.begin(), static_cast<size_t>(count-pointer) };
        }

        [[nodiscard]] auto constexpr end() const noexcept -> const_iterator {
            return const_iterator { data.begin(), static_cast<size_t>((pointer-1+count) % CAPACITY) };
        }

        auto constexpr end() noexcept -> iterator {
            return iterator{ data.begin(), static_cast<size_t>((pointer-1+count) % CAPACITY)};
        }

        [[nodiscard]] auto constexpr contains(const T& value) const noexcept -> bool {
            for(size_type i = 0; i < count; i++) {
                if(data[i] == value) return true;
            }
            return false;
        }

        [[nodiscard]] auto constexpr empty() const noexcept -> bool {
            return count == 0;
        }

        [[nodiscard]] auto constexpr size() const noexcept -> size_type {
            return count;
        }

        [[nodiscard]] auto consteval capacity() const noexcept -> size_type {
            return CAPACITY;
        }

        template <class O, size_t OTHER_CAPACITY>
        auto constexpr operator==(const DropoutStack<O, OTHER_CAPACITY>& other) const noexcept -> bool {
            if(CAPACITY != OTHER_CAPACITY) return false;
            if(pointer != other.pointer) return false;
            if(count != other.count) return false;

            for(size_type i = 0; i < count; ++i) {
                if(data[i] != other.data[i]) return false;
            }
            return true;
        }

    private:
        size_type pointer;
        size_type count;
        Array<T, CAPACITY> data;
    };

    static_assert(Container<DropoutStack<u8, 0>>);
}// namespace nespp