/**
 * @author Steven Goldade
 * @date 11/12/2023
 */
#pragma once
#include <nespp/stack.h>

auto constexpr test_stack() noexcept -> bool {
    auto stack = nespp::Stack<u8, 4>();

    stack.push(0);
    stack.push(1);
    stack.push(2);
    stack.push(3);

    if(!stack.contains(2)) return false;
    if(*stack.begin() != 3) return false;
    if(*(stack.begin()++) != 2) return false;
    if(*stack.end() != 0) return false;

    for(auto & var : stack) {
        (void)var;
    }

    if(stack.pop() != 3) return false;
    auto p = stack.peek();
    p = 5;
    (void)p;
    if(stack.pop() != 2) return false;
    if(stack.pop() != 1) return false;
    if(stack.pop() != 0) return false;

    auto stack2 = nespp::Stack<u8, 4> {3,5,7,9};
    auto constexpr stack3 = nespp::Stack<u8, 4> {3,5,7,9};

    if(stack2 != stack3) return false;
    if(stack2.pop() != 9) return false;
    if(stack2.peek() != 7) return false;
    if(stack2 == stack3) return false;
    stack2.push(9);
    if(stack2 != stack3) return false;

    auto constexpr partial_stack = nespp::Stack<u8, 4> {3, 5};
    static_assert(partial_stack.peek() == 5);
    static_assert(partial_stack.size() == 2);
    static_assert(partial_stack.capacity() == 4);

    return true;
}