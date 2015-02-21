
#ifndef sorting_hpp
#define sorting_hpp

// http://www.nongnu.org/avr-libc/user-manual/group__avr__math.html
#include "math.h"
#include "positioning_system.h"

void sort_numbers(double *a, double *b);
void sort_numbers(double *a, double *b, double *c);
void sort_numbers(double *a, double *b, double *c, double *d);

template <typename T>
void exchange(T *a, T *b) {
  T temp;
  temp = *a;
  *a = *b;
  *b = temp;
}

template <typename T>
void sort(T *a, T *b) {
  if (!(*a < *b)) {
    exchange(a, b);
  }
}

template <typename T>
void sort(T *a, T *b, T *c) {
  // bubblesort
  sort(a, b);
  sort(b, c);
  sort(a, b);
}

template <typename T>
void sort(T *a, T *b, T *c, T *d) {
  // bubblesort
  sort(a, b);
  sort(b, c);
  sort(c, d);
  sort(a, b, c);
}

#endif