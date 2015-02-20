
#ifndef cubic_root_hpp
#define cubic_root_hpp

#include "numbers.hpp"

Number curt(NumberArgument x);

Number curt_1(NumberArgument x);

template <typename Number>
Number curt_2(Number x) {
  // http://stackoverflow.com/a/28273079/1320237
  if (x == 0) {
    // would otherwise return something like 4.257959840008151e-109
    return 0;
  }
  Number b = 1; // use any value except 0
  for (int i = 0; i < 50; ++i) {
    b = (b + x / (b * b)) / 2;
  }
  return b;
}

Number curt_3(NumberArgument x);

#endif 
