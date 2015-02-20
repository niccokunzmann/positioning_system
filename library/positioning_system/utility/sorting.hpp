
#ifndef sorting_hpp
#define sorting_hpp

#include "positioning_system.h"

void sort_numbers(double *a, double *b);
void sort_numbers(double *a, double *b, double *c);
void sort_numbers(double *a, double *b, double *c, double *d);

template <typename T>
void exchange(T *a, T *b) {
  double temp;
  temp = *a;
  *a = *b;
  *b = temp;
}

template <typename T>
void sort(T *a, T *b) {
  if ((*a > *b) || is_not_a_number(*a)) {
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