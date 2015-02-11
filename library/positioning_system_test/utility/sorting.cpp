
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

void sort_numbers(NumberPointer a, NumberPointer b, NumberPointer c) {
  // bubblesort
  sort_numbers(a, b);
  sort_numbers(b, c);
  sort_numbers(a, b);
}

void sort_numbers(NumberPointer a, NumberPointer b, NumberPointer c, NumberPointer d) {
  // bubblesort
  sort_numbers(a, b);
  sort_numbers(b, c);
  sort_numbers(c, d);
  sort_numbers(a, b, c);
}
