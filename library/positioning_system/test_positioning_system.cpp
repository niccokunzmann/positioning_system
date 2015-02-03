
#include "test_positioning_system.h"
#include "Arduino.h"
#include "test_solve.h"
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

void test_delay(const TEST_PRINT_STRING bytes) {
  // strlen https://www.gnu.org/software/libc/manual/html_node/String-Length.html
  // 
  test_delay(bytes.length());
} 
void test_delay(int bytes) {
  delay(1 + bytes / 9);
}


void test_print(const TEST_PRINT_STRING message){
  Serial.print(message);
  test_delay(message);
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
  int digits = 1;
  while (message) {
    ++digits;
    message /= 10;
  }
  test_delay(digits);
  Serial.flush();
}
void test_println(int message) {
  test_print(message);
  test_println();
}
void test_print(double message){
  // 0.3333333333333333 18 bytes
  Serial.print(message, 8);
  test_delay(30);
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

void test_print(const TEST_PRINT_STRING message1, double message2) {
  test_print(message1);
  test_print(message2);
}
void test_println(const TEST_PRINT_STRING message1, double message2) {
  test_print(message1);
  test_println(message2);
}
void test_print(const TEST_PRINT_STRING message1, double message2, const TEST_PRINT_STRING message3, double message4) {
  test_print(message1, message2);
  test_print(message3, message4);
}
void test_println(const TEST_PRINT_STRING message1, double message2, const TEST_PRINT_STRING message3, double message4) {
  test_print(message1, message2);
  test_println(message3, message4);
}

void test_print(const TEST_PRINT_STRING message1, double message2, const TEST_PRINT_STRING message3, double message4, 
                const TEST_PRINT_STRING message5, double message6) {
  test_print(message1, message2);
  test_print(message3, message4);
  test_print(message5, message6);
}
void test_println(const TEST_PRINT_STRING message1, double message2, const TEST_PRINT_STRING message3, double message4, 
                  const TEST_PRINT_STRING message5, double message6) {
  test_print(message1, message2);
  test_print(message3, message4);
  test_println(message5, message6);
}
void test_print(const TEST_PRINT_STRING message1, double message2, const TEST_PRINT_STRING message3, double message4, 
                const TEST_PRINT_STRING message5, double message6, const TEST_PRINT_STRING message7, double message8) {
  test_print(message1, message2);
  test_print(message3, message4);
  test_print(message5, message6);
  test_print(message7, message8);
}
void test_println(const TEST_PRINT_STRING message1, double message2, const TEST_PRINT_STRING message3, double message4, 
                  const TEST_PRINT_STRING message5, double message6, const TEST_PRINT_STRING message7, double message8) {
  test_print(message1, message2);
  test_print(message3, message4);
  test_print(message5, message6);
  test_println(message7, message8);
}

void test_print(const TEST_PRINT_STRING message1, double message2, const TEST_PRINT_STRING message3, double message4, 
                const TEST_PRINT_STRING message5, double message6, const TEST_PRINT_STRING message7, double message8, 
                const TEST_PRINT_STRING message9, double message10) {
  test_print(message1, message2);
  test_print(message3, message4);
  test_print(message5, message6);
  test_print(message7, message8);
  test_print(message9, message10);
}
void test_println(const TEST_PRINT_STRING message1, double message2, const TEST_PRINT_STRING message3, double message4, 
                  const TEST_PRINT_STRING message5, double message6, const TEST_PRINT_STRING message7, double message8, 
                  const TEST_PRINT_STRING message9, double message10) {
  test_print(message1, message2);
  test_print(message3, message4);
  test_print(message5, message6);
  test_print(message7, message8);
  test_println(message9, message10);
}


