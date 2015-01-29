
#ifndef test_h
#define test_h

#include "Arduino.h"

void test_debug_print(const char* message, int line, const char* file);

static boolean test_success;

// Macros
// https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html#Standard-Predefined-Macros
#define assert2(truth, Message) \
  if (!(truth)) { \
    test_debug_print(Message, __LINE__, __FILE__); \
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

