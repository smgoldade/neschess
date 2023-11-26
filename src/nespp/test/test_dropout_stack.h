/**
* @author Steven Goldade
* @date 11/26/2023
*/
#pragma once
#include <nespp/dropout_stack.h>

auto constexpr test_dropout_stack() noexcept -> bool {
   auto stack = nespp::DropoutStack<u8, 4>();

   stack.push(0);
   stack.push(1);
   stack.push(2);
   stack.push(3);
   stack.push(4);

   if(!stack.contains(2)) return false;
   if(*stack.begin() != 3) return false;
   if(*(stack.begin()++) != 2) return false;
   if(*stack.end() != 4) return false;

   for(auto & var : stack) {
       (void)var;
   }

   if(stack.pop() != 4) return false;
   auto p = stack.peek();
   p = 5;
   (void)p;
   if(stack.pop() != 3) return false;
   if(stack.pop() != 2) return false;
   if(stack.pop() != 1) return false;
   if(stack.pop() != 4) return false;
   if(stack.pop() != 3) return false;

   return true;
}