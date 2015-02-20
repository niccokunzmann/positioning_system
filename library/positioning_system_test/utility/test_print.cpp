
#include "test_print.hpp"

#ifdef HPA
template <>
void print1<HPA::xreal> (HPA::xreal message1) {
  //print1(message1._2String());
  print1(message1._2double());
}
template <>
void print1<struct xpr> (const struct xpr message1) {
  print1(xtodbl(message1));
}
#endif
template <>
void print1<double> (const double message1) {
  Serial.print(message1, 10);
  delay(30);
  Serial.flush();
}

void println0() {
  print1(F("\n"));
}