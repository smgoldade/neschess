/**
 * @author Steven Goldade
 * @date 11/12/2023
 */
#pragma once
#include <nespp/vector.h>

auto constexpr test_vector() noexcept -> bool {
    auto vec = nespp::Vector<u8, 4>();

    vec.push_back(1);
    if(vec[0] != 1) return false;
    vec.push_back(3);
    if(vec[1] != 3) return false;
    if(vec.size() != 2) return false;

    auto vec2 = nespp::Vector<u8, 5> {1, 2};
    auto vec3 = nespp::Vector<u8, 2> {3, 4};

    for(auto & vect : vec2) {
        (void)vect;
    }

    if(vec2.begin() + 2 != vec2.end()) return false;

    vec2.push_back_all(vec3);
    if(vec2[0] != 1) return false;
    if(vec2[1] != 2) return false;
    if(vec2[2] != 3) return false;
    if(vec2[3] != 4) return false;
    if(vec2.size() != 4) return false;

    vec2.push_front(9);
    if(vec2[0] != 9) return false;
    if(vec2[1] != 1) return false;
    if(vec2[2] != 2) return false;
    if(vec2[3] != 3) return false;
    if(vec2[4] != 4) return false;
    if(vec2.size() != 5) return false;

    for(auto vect : vec2) {
        (void)vect;
    }

    return true;
}