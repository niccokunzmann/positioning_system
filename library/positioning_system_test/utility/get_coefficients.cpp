
#include "get_coefficients.hpp"

void get_coefficients_from_zeros(NumberArgument zero1, 
                                 NumberPointer d, NumberPointer e) {
  *d = 1;
  *e = -zero1;
}
void get_coefficients_from_zeros(NumberArgument zero1, NumberArgument zero2, 
                                 NumberPointer c, NumberPointer d, NumberPointer e) {
  *c = 1;
  *d = -zero1 - zero2;
  *e = zero1 * zero2;
}
void get_coefficients_from_zeros(NumberArgument zero1, NumberArgument zero2, NumberArgument zero3, 
                                 NumberPointer b, NumberPointer c, NumberPointer d, NumberPointer e) {
  *b = 1;
  *c = -zero1 - zero2 - zero3;
  *d = zero1 * zero2 + zero1 * zero3 + zero2 * zero3;
  *e = - zero1 * zero2 * zero3;
}
void get_coefficients_from_zeros(NumberArgument zero1, NumberArgument zero2, NumberArgument zero3, NumberArgument zero4, 
                                 NumberPointer a, NumberPointer b, NumberPointer c, NumberPointer d, NumberPointer e) {
  *a = 1;
  *b = -zero1 - zero2 - zero3 - zero4;
  *c = zero1 * zero2 + zero1 * zero3 + zero1 * zero4 + zero2 * zero3 + zero2 * zero4 + zero3 * zero4;
  *d = - zero2 * zero3 * zero4 - zero1 * zero3 * zero4 - zero1 * zero2 * zero4 - zero1 * zero2 * zero3;
  *e = zero1 * zero2 * zero3 * zero4;
}