
#ifndef square_root_hpp
#define square_root_hpp

#include "Arduino.h"

template <typename Number>
Number square_root(Number a_number) {
  if (a_number == 0) {
    return 0;
  }
  Number b = 1;
  for (int i = 0; i < 15; ++i){
    b = (b + a_number / b) / 2;
  }
  return b;
}

#endif
