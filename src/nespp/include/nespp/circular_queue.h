/**
 * @author Steven Goldade
 * @date 11/29/2023
 */
#pragma once
#include "array.h"
#include "circular_iterator.h"
#include "container.h"
#include "error.h"
#include "nesmath.h"
#include "types.h"

namespace nespp {
    template <class T, size_t CAPACITY>
    class CircularQueue {
    public:
        using data_type = T;
        using size_type = size_t;
        using iterator = CircularIterator<T*, CAPACITY>;
        using const_iterator = const T*;

        constexpr CircularQueue() noexcept : front_pointer(0), rear_pointer(0), count(0), data(){};
        constexpr CircularQueue(const std::initializer_list<T>& init) noexcept : front_pointer(0), rear_pointer(init.size()), count(init.size()), data() {
            auto it = init.begin();
            for(size_t i = 0; i < count; ++i)
                data[i] = it[i];
        }

        auto constexpr push_back(const T& value) noexcept -> void {
            data[rear_pointer++] = value;
            count++;
            count = min(count, CAPACITY);
            rear_pointer %= CAPACITY;
        }

        auto constexpr pop_front() noexcept -> const T& {
            auto const & value = data[front_pointer];
            front_pointer++;
            front_pointer %= CAPACITY;
            count--;
            if(count > CAPACITY) count = 0;
            return value;
        }

        [[nodiscard]] auto constexpr begin() const noexcept -> const_iterator {
            return const_iterator { data.begin(), front_pointer };
        }

        auto constexpr begin() noexcept -> iterator {
            return iterator { data.begin(), front_pointer };
        }

        [[nodiscard]] auto constexpr end() const noexcept -> const_iterator {
            return const_iterator { data.begin(), rear_pointer } ;
        }

        auto constexpr end() noexcept -> iterator {
            return iterator { data.begin(), rear_pointer };
        }

        [[nodiscard]] auto constexpr contains(const T& value) const noexcept -> bool {
            for(auto & datum : data) {
                if(datum == value) return true;
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
        auto constexpr operator==(const CircularQueue<O, OTHER_CAPACITY>& other) const noexcept -> bool {
            if(CAPACITY != OTHER_CAPACITY) return false;
            if(front_pointer != other.front_pointer) return false;
            if(rear_pointer != other.rear_pointer) return false;
            if(count != other.count) return false;

            return true;
        }

    private:
        size_type front_pointer;
        size_type rear_pointer;
        size_type count;
        Array<T, CAPACITY> data;
    };

    static_assert(Container<CircularQueue<u8, 0>>);
}// namespace nespp