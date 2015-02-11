
#include "test_positioning_system.hpp"
#include "Arduino.h"
#include "test_solve.hpp"
//#include "string.h"

int tests_succeeded;
int tests_failed;
boolean verbose_tests = true;
boolean last_message_was_success;

int get_number_of_succeeded_tests() {
  return tests_succeeded;
}
int get_number_of_failed_tests() {
  return tests_failed;
}
void use_verbose_test_output(boolean verbose) {
  verbose_tests = verbose;
}

void test_positioning_system_1() {
  setup_tests();
  test_solve_1();
  teardown_tests();
}

void test_positioning_system_2() {
  setup_tests();
  test_solve_2();
  teardown_tests();
}

void test_positioning_system_3() {
  setup_tests();
  
  teardown_tests();
}

void test_positioning_system_4() {
  setup_tests();
  
  teardown_tests();
}

void setup_tests() {
  tests_succeeded = 0;
  tests_failed = 0;
  last_message_was_success = true;
  println1(F("Running tests: "));
}

void teardown_tests() {
  println0();
  println6(tests_succeeded, F(" tests passed. "),
           tests_failed,    F(" tests failed. Ran "), 
           tests_succeeded + tests_failed, 
                            F(" tests."));
}

////////////////////// Output //////////////////////


template <>
void print1<HPA::xreal> (HPA::xreal message1) {
  print1(message1._2double());
}
template <>
void print1<struct xpr> (const struct xpr message1) {
  print1(xtodbl(message1));
}

void println0() {
  print1(F("\n"));
}

