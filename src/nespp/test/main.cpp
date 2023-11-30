/**
* @author Steven Goldade
* @date 11/11/2023
*/
#include "test_array.h"
#include "test_circular_queue.h"
#include "test_dropout_stack.h"
#include "test_stack.h"
#include "test_types.h"
#include "test_vector.h"

int main() {
   static_assert(test_array(), "Array");
   static_assert(test_circular_queue(), "Circular Queue");
   static_assert(test_dropout_stack(), "Dropout Stack");
   static_assert(test_stack(), "Stack");
   static_assert(test_types(), "Types");
   static_assert(test_vector(), "Vector");
}