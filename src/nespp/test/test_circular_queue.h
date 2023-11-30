/**
 * @author Steven Goldade
 * @date 11/29/2023
 */
#pragma once
#include <nespp/circular_queue.h>

auto constexpr test_circular_queue() noexcept -> bool {
    auto circular_queue = nespp::CircularQueue<u8, 4>();

    circular_queue.push_back(0);
    circular_queue.push_back(1);
    circular_queue.push_back(2);
    circular_queue.push_back(3);
    circular_queue.push_back(4);

    if(!circular_queue.contains(2)) return false;
    if(*circular_queue.begin() != 4) return false;
    if(*(++circular_queue.begin()) != 1) return false;
    if(*circular_queue.end() != 1) return false;

    for(auto & var : circular_queue) {
        (void)var;
    }

    if(circular_queue.pop_front() != 4) return false;
    if(circular_queue.pop_front() != 1) return false;
    if(circular_queue.pop_front() != 2) return false;
    if(circular_queue.pop_front() != 3) return false;
    if(circular_queue.pop_front() != 4) return false;
    if(circular_queue.pop_front() != 1) return false;

    return true;
}