
#include "sorting.hpp"

void switch_numbers(NumberPointer a, NumberPointer b) {
  Number temp;
  temp = *a;
  *a = *b;
  *b = temp;
}

void sort_numbers(NumberPointer a, NumberPointer b) {
  if ((*a > *b) || is_not_a_number(*a)) {
    switch_numbers(a, b);
  }
}