
#ifndef test_positioning_system_h
#define test_positioning_system_h

#include "Arduino.h"

void test_succeeded(const char* message, int line, const char* file);
void test_failed(const char* message, int line, const char* file);

void setup_tests();
void run_tests();
void teardown_tests();
void test_all();

void test_delay(char* bytes);
void test_delay(int bytes);

void test_println();
void test_print(const char* message);
void test_println(const char* message);
void test_print(int message);
void test_println(int message);
void test_print(double message);
void test_println(double message);

void test_print(const char* message1, double message2);
void test_println(const char* message1, double message2);
void test_print(const char* message1, double message2, const char* message3, double message4);
void test_println(const char* message1, double message2, const char* message3, double message4);
void test_print(const char* message1, double message2, const char* message3, double message4, 
                const char* message5, double message6);
void test_println(const char* message1, double message2, const char* message3, double message4, 
                  const char* message5, double message6);
void test_print(const char* message1, double message2, const char* message3, double message4, 
                const char* message5, double message6, const char* message7, double message8);
void test_println(const char* message1, double message2, const char* message3, double message4, 
                  const char* message5, double message6, const char* message7, double message8);
void test_print(const char* message1, double message2, const char* message3, double message4, 
                const char* message5, double message6, const char* message7, double message8, 
                const char* message9, double message10);
void test_println(const char* message1, double message2, const char* message3, double message4, 
                  const char* message5, double message6, const char* message7, double message8, 
                  const char* message9, double message10);


int get_number_of_succeeded_tests();
int get_number_of_failed_tests();
void use_verbose_test_output(boolean verbose);


// Macros
// https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html#Standard-Predefined-Macros
#define assert2(truth, Message) \
  if (truth) { \
    test_succeeded(Message, __LINE__, __FILE__); \
  } else { \
    test_failed(Message, __LINE__, __FILE__); \
  };
  
#define assert1(truth) assert2(truth, #truth)

#define assert_equals2(A, B, Message) assert2((A) == (B), #Message)
#define _assert_equals(A, B, Message) assert_equals2(A, B, #Message)
#define assert_equals(A, B) _assert_equals(A, B, A == B)

#define assert_not_equals2(A, B, Message) assert2((A) != (B), #Message)
#define _assert_not_equals(A, B, Message) assert_not_equals2(A, B, #Message)
#define assert_not_equals(A, B) _assert_not_equals(A, B, A != B)

#define assert_approximates2(A, B, Message) assert2(approximates((A),(B)), #Message)
#define _assert_approximates(A, B, Message) assert_approximates2(A, B, #Message)
#define assert_approximates(A, B) _assert_approximates(A, B, A =~= B)

#endif

