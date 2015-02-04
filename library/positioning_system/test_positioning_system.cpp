
#include "test_positioning_system.hpp"
#include "Arduino.h"
#include "test_solve.hpp"
//#include "string.h"

int tests_succeeded;
int tests_failed;
boolean verbose_tests = true;
boolean last_message_was_success;


void test_succeeded(const __FlashStringHelper* message) {
  tests_succeeded++;
  if (Serial) {
    if (verbose_tests) {
      test_print(F("Success: "));
      test_println(message);
    } else {
      test_print(F(".")); 
    }
  }
  last_message_was_success = true;
}

void test_failed(const __FlashStringHelper* message) {
  tests_failed++;
  if (Serial) {
    if (verbose_tests) {
      if (last_message_was_success) {
        test_println();
      }
      test_print(F("AssertionError: ")); 
      test_println(message); 
    } else {
      test_print(F("F"));
    }
  }
  last_message_was_success = false;
}

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
  test_println(F("Running tests: "));
}

void teardown_tests() {
  test_println();
  test_print(tests_succeeded);
  test_print(F(" tests passed. "));
  test_print(tests_failed);
  test_print(F(" tests failed. Ran "));
  test_print(tests_succeeded + tests_failed);
  test_println(F(" tests."));
}

////////////////////// Output //////////////////////

void _test_print(const TEST_PRINT_STRING message){
  Serial.print(message);
  Serial.flush();
}

void test_println() {
  test_print(F("\n"));
}
void test_println(const TEST_PRINT_STRING message) {
  test_print(message);
  test_println();
}
void test_print(int message) {
  Serial.print(message);
  Serial.flush();
}
void test_println(int message) {
  test_print(message);
  test_println();
}
void test_print(double message){
  Serial.print(message, 8);
  Serial.flush();
}
void test_println(double message){
  test_print(message);
  test_println();
}

void test_print(const __FlashStringHelper* message) {
  Serial.print(message);
  Serial.flush();
}
void test_println(const __FlashStringHelper* message) {
  Serial.println(message);
  Serial.flush();
};

void test_print(const char* message) {
  Serial.print(message);
  Serial.flush();
}
void test_println(const char* message) {
  Serial.println(message);
  Serial.flush();
};

void test_print(HPA::xreal message){
  test_print(message._2double());
}
void test_println(HPA::xreal message){
  test_println(message._2double());
}

