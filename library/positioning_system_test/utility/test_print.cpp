
#include "test_print.hpp"

void print_coefficients_to_serial(NumberArgument a, NumberArgument b, NumberArgument c, NumberArgument d, NumberArgument e){
  if (a != 0) {
    print1(a);
    print1(F("*x^4 + "));
  }
  if (b != 0) {
    print1(b);
    print1(F("*x^3 + "));
  }
  if (c != 0) {
    print1(c);
    print1(F("*x^2 + "));
  }
  if (d != 0) {
    print1(d);
    print1(F("*x + "));
  }
  print1(e);
}

template <>
void print1<HPA::xreal> (HPA::xreal message1) {
  //print1(message1._2String());
  print1(message1._2double());
}
template <>
void print1<struct xpr> (const struct xpr message1) {
  print1(xtodbl(message1));
}
template <>
void print1<double> (const double message1) {
  Serial.print(message1, 10);
  delay(30);
  Serial.flush();
}

void println0() {
  print1(F("\n"));
}