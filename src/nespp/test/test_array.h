/**
 * @author Steven Goldade
 * @date 11/11/2023
 */
#pragma once
#include <nespp/array.h>

auto constexpr test_array() noexcept -> bool {
    auto constexpr empty = nespp::Array<u8, 8>();
    auto constexpr filled1 = nespp::Array<u8, 4> {0 , 1, 3, 9};
    auto constexpr filled2 = filled1;
    auto constexpr filled3 = nespp::Array<u8, 4> {0 , 3, 5, 9};
    auto constexpr partially_filled = nespp::Array<u8,4> {1, 2};
    
    static_assert(empty[0] == 0);
    static_assert(empty[1] == 0);
    static_assert(empty[2] == 0);
    static_assert(empty[3] == 0);
    static_assert(empty[4] == 0);
    static_assert(empty[5] == 0);
    static_assert(empty[6] == 0);
    static_assert(empty[7] == 0);
    static_assert(empty.size() == 8);
    static_assert(empty.capacity() == 8);
    static_assert(!empty.empty());
    static_assert(filled1[0] == 0);
    static_assert(filled1[1] == 1);
    static_assert(filled1[2] == 3);
    static_assert(filled1[3] == 9);
    static_assert(empty.contains(0));
    static_assert(!filled2.contains(2));

    static_assert(empty != filled1);
    static_assert(filled1 == filled2);
    static_assert(filled1 != filled3);
    static_assert(partially_filled != filled1);

    static_assert(partially_filled[0] == 1);
    static_assert(partially_filled[1] == 2);
    static_assert(partially_filled[2] == 0);
    static_assert(partially_filled[3] == 0);

    for(auto & val : empty) {
        (void)val;
    }
    auto sum = 0;
    for(auto & val : filled2) {
        sum += val;
    }
    if(sum != 13) return false;
    
    return true;
}