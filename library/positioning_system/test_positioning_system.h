
#ifndef test_positioning_system_h
#define test_positioning_system_h

#include "Arduino.h"

void test_succeeded(const char* message, int line, const char* file);
void test_failed(const char* message, int line, const char* file);
void test_all();

void test_delay(char* bytes);
void test_delay(int bytes)

void test_println();
void test_print(char* message);
void test_println(char* message);
void test_print(int message);
void test_println(int message);
void test_print(double message);
void test_println(double message);


static boolean test_success;
static boolean verbose_tests = true;

// Macros
// https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html#Standard-Predefined-Macros
#define assert2(truth, Message) \
  if (truth) { \
    test_succeeded(Message, __LINE__, __FILE__); \
  } else { \
    test_failed(Message, __LINE__, __FILE__); \
    test_success = false; \
  };
  
#define assert1(truth) assert2(truth, #truth)

#define assert_equals2(A, B, Message) assert2((A) == (B), #Message)
#define _assert_equals(A, B, Message) assert_equals2(A, B, #Message)
#define assert_equals(A, B) _assert_equals(A, B, A == B)

#define assert_not_equals2(A, B, Message) assert2((A) != (B), #Message)
#define _assert_not_equals(A, B, Message) assert_not_equals2(A, B, #Message)
#define assert_not_equals(A, B) _assert_not_equals(A, B, A != B)


#endif

