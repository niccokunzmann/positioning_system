
#ifndef test_positioning_system_h
#define test_positioning_system_h

#include "Arduino.h"

// from http://forum.arduino.cc/index.php/topic,85840.0.html
#ifdef PROGMEM
#undef PROGMEM
#define PROGMEM __attribute__((section(".progmem.data")))
#endif

typedef String TEST_PRINT_STRING;

void test_succeeded(const TEST_PRINT_STRING message, int line, const TEST_PRINT_STRING file);
void test_failed(const TEST_PRINT_STRING message, int line, const TEST_PRINT_STRING file);

void setup_tests();
void teardown_tests();
void test_positioning_system_1();
void test_positioning_system_2();
void test_positioning_system_3();
void test_positioning_system_4();

void test_delay(const TEST_PRINT_STRING bytes);
void test_delay(int bytes);

void test_println();
void test_print(const TEST_PRINT_STRING message);
void test_println(const TEST_PRINT_STRING message);
void test_print(const __FlashStringHelper* message);
void test_println(const __FlashStringHelper* message);
void test_print(int message);
void test_println(int message);
void test_print(double message);
void test_println(double message);

void test_print(const TEST_PRINT_STRING message1, double message2);
void test_println(const TEST_PRINT_STRING message1, double message2);
void test_print(const TEST_PRINT_STRING message1, double message2, const TEST_PRINT_STRING message3, double message4);
void test_println(const TEST_PRINT_STRING message1, double message2, const TEST_PRINT_STRING message3, double message4);
void test_print(const TEST_PRINT_STRING message1, double message2, const TEST_PRINT_STRING message3, double message4, 
                const TEST_PRINT_STRING message5, double message6);
void test_println(const TEST_PRINT_STRING message1, double message2, const TEST_PRINT_STRING message3, double message4, 
                  const TEST_PRINT_STRING message5, double message6);
void test_print(const TEST_PRINT_STRING message1, double message2, const TEST_PRINT_STRING message3, double message4, 
                const TEST_PRINT_STRING message5, double message6, const TEST_PRINT_STRING message7, double message8);
void test_println(const TEST_PRINT_STRING message1, double message2, const TEST_PRINT_STRING message3, double message4, 
                  const TEST_PRINT_STRING message5, double message6, const TEST_PRINT_STRING message7, double message8);
void test_print(const TEST_PRINT_STRING message1, double message2, const TEST_PRINT_STRING message3, double message4, 
                const TEST_PRINT_STRING message5, double message6, const TEST_PRINT_STRING message7, double message8, 
                const TEST_PRINT_STRING message9, double message10);
void test_println(const TEST_PRINT_STRING message1, double message2, const TEST_PRINT_STRING message3, double message4, 
                  const TEST_PRINT_STRING message5, double message6, const TEST_PRINT_STRING message7, double message8, 
                  const TEST_PRINT_STRING message9, double message10);


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

#define assert_equals2(A, B, Message) assert2((A) == (B), Message)
#define _assert_equals(A, B, Message) assert_equals2(A, B, #Message)
#define assert_equals(A, B) _assert_equals(A, B, A == B)

#define assert_not_equals2(A, B, Message) assert2((A) != (B), Message)
#define _assert_not_equals(A, B, Message) assert_not_equals2(A, B, #Message)
#define assert_not_equals(A, B) _assert_not_equals(A, B, A != B)

#define assert_approximates2(A, B, Message) assert2(approximates((A),(B)), Message)
#define _assert_approximates(A, B, Message) assert_approximates2(A, B, #Message)
#define assert_approximates(A, B) _assert_approximates(A, B, A =~= B)

#endif

