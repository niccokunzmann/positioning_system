
#include "test_positioning_system.h"
#include "Arduino.h"
#include "test_solve.h"
//#include "string.h"

int tests_succeeded;
int tests_failed;
boolean verbose_tests = false;
boolean last_message_was_success;

void test_succeeded(const char* message, int line, const char* file) {
  tests_succeeded++;
  if (Serial) {
    test_print("."); 
  }
  last_message_was_success = true;
}

void test_failed(const char* message, int line, const char* file) {
  tests_failed++;
  if (Serial) {
    if (last_message_was_success) {
      test_println();
    }
    if (verbose_tests) {
      test_print("In line "); 
      test_print(line); 
      test_print("\tin file "); 
      test_println(file); 
    }      
    test_print("AssertionError: "); 
    test_println(message); 
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

void test_all() {
  setup_tests();
  run_tests();
  teardown_tests();
}

void setup_tests() {
  tests_succeeded = 0;
  tests_failed = 0;
  last_message_was_success = true;
  test_println("Running tests: ");
}

void run_tests() {
  test_solve();
}

void teardown_tests() {
  test_println();
  test_print(tests_succeeded);
  test_print(" tests passed. ");
  test_print(tests_failed);
  test_print(" tests failed. Ran ");
  test_print(tests_succeeded + tests_failed);
  test_println(" tests.");
}

////////////////////// Output //////////////////////

void test_delay(const char* bytes) {
  // strlen https://www.gnu.org/software/libc/manual/html_node/String-Length.html
  test_delay(strlen(bytes));
} 
void test_delay(int bytes) {
  delay(1 + bytes / 9);
}


void test_print(const char* message){
  Serial.print(message);
  test_delay(message);
}

void test_println() {
  test_print("\n");
}
void test_println(const char* message) {
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
}
void test_println(int message) {
  test_print(message);
  test_println();
}
void test_print(double message){
  // 0.3333333333333333 18 bytes
  Serial.print(message);
  test_delay(18);
}
void test_println(double message){
  test_print(message);
  test_println();
}

void test_print(const char* message1, double message2) {
  test_print(message1);
  test_print(message2);
}
void test_println(const char* message1, double message2) {
  test_print(message1);
  test_println(message2);
}
void test_print(const char* message1, double message2, const char* message3, double message4) {
  test_print(message1, message2);
  test_print(message3, message4);
}
void test_println(const char* message1, double message2, const char* message3, double message4) {
  test_print(message1, message2);
  test_println(message3, message4);
}

void test_print(const char* message1, double message2, const char* message3, double message4, 
                const char* message5, double message6) {
  test_print(message1, message2);
  test_print(message3, message4);
  test_print(message5, message6);
}
void test_println(const char* message1, double message2, const char* message3, double message4, 
                  const char* message5, double message6) {
  test_print(message1, message2);
  test_print(message3, message4);
  test_println(message5, message6);
}
void test_print(const char* message1, double message2, const char* message3, double message4, 
                const char* message5, double message6, const char* message7, double message8) {
  test_print(message1, message2);
  test_print(message3, message4);
  test_print(message5, message6);
  test_print(message7, message8);
}
void test_println(const char* message1, double message2, const char* message3, double message4, 
                  const char* message5, double message6, const char* message7, double message8) {
  test_print(message1, message2);
  test_print(message3, message4);
  test_print(message5, message6);
  test_println(message7, message8);
}

void test_print(const char* message1, double message2, const char* message3, double message4, 
                const char* message5, double message6, const char* message7, double message8, 
                const char* message9, double message10) {
  test_print(message1, message2);
  test_print(message3, message4);
  test_print(message5, message6);
  test_print(message7, message8);
  test_print(message9, message10);
}
void test_println(const char* message1, double message2, const char* message3, double message4, 
                  const char* message5, double message6, const char* message7, double message8, 
                  const char* message9, double message10) {
  test_print(message1, message2);
  test_print(message3, message4);
  test_print(message5, message6);
  test_print(message7, message8);
  test_println(message9, message10);
}


