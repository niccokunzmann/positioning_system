
#ifndef test_positioning_system_h
#define test_positioning_system_h

#include "hpa.h"
#include "Arduino.h"

// from http://forum.arduino.cc/index.php/topic,85840.0.html
#ifdef PROGMEM
#undef PROGMEM
#define PROGMEM __attribute__((section(".progmem.data")))
#endif

typedef String TEST_PRINT_STRING;

void test_succeeded(const __FlashStringHelper* message);
void test_failed(const __FlashStringHelper* message);

void setup_tests();
void teardown_tests();
void test_positioning_system_1();
void test_positioning_system_2();
void test_positioning_system_3();
void test_positioning_system_4();

int get_number_of_succeeded_tests();
int get_number_of_failed_tests();
void use_verbose_test_output(boolean verbose);


void test_print(const TEST_PRINT_STRING message);
void test_println(const TEST_PRINT_STRING message);
void test_print(const __FlashStringHelper* message);
void test_println(const __FlashStringHelper* message);
void test_print(int message);
void test_println(int message);
void test_print(double message);
void test_println(double message);
void test_print(const char* message);
void test_println(const char* message);
void test_print(const HPA::xreal message);
void test_println(const HPA::xreal message);





const char* message3  = "";
const char* message4  = "";
const char* message5  = "";
const char* message6  = "";
const char* message7  = "";
const char* message8  = "";
const char* message9  = "";
const char* message10 = "";

template <typename Type1, typename Type2>
void test_println(const Type1 message1, const Type2 message2) {
  test_print(message1, message2, message3, message4, message5, message6, message7, message8, message9, message10);
  test_println();
}                 
template <typename Type1, typename Type2>
void test_print(const Type1 message1, const Type2 message2) {
  test_print(message1, message2, message3, message4, message5, message6, message7, message8, message9, message10);
}

template <typename Type1, typename Type2, typename Type3>
void test_println(const Type1 message1, const Type2 message2, 
                  const Type1 message3){
  test_print(message1, message2, message3, message4, message5, message6, message7, message8, message9, message10);
  test_println();
}                  
template <typename Type1, typename Type2, typename Type3>
void test_print(const Type1 message1, const Type2 message2, 
                  const Type1 message3){
  test_print(message1, message2, message3, message4, message5, message6, message7, message8, message9, message10);
}                  

template <typename Type1, typename Type2, typename Type3, typename Type4>
void test_println(const Type1 message1, const Type2 message2, 
                  const Type1 message3, const Type2 message4){
  test_print(message1, message2, message3, message4, message5, message6, message7, message8, message9, message10);
  test_println();
}                  
template <typename Type1, typename Type2, typename Type3, typename Type4>
void test_print(const Type1 message1, const Type2 message2, 
                  const Type1 message3, const Type2 message4){
  test_print(message1, message2, message3, message4, message5, message6, message7, message8, message9, message10);
}                  

template <typename Type1, typename Type2, typename Type3, typename Type4, 
          typename Type5>
void test_println(const Type1 message1, const Type2 message2, 
                  const Type1 message3, const Type2 message4,  
                  const Type1 message5){
  test_print(message1, message2, message3, message4, message5, message6, message7, message8, message9, message10);
  test_println();
}                  
template <typename Type1, typename Type2, typename Type3, typename Type4, 
          typename Type5>
void test_print(const Type1 message1, const Type2 message2, 
                  const Type1 message3, const Type2 message4,  
                  const Type1 message5){
  test_print(message1, message2, message3, message4, message5, message6, message7, message8, message9, message10);
}                  

template <typename Type1, typename Type2, typename Type3, typename Type4, 
          typename Type5, typename Type6>
void test_println(const Type1 message1, const Type2 message2, 
                  const Type1 message3, const Type2 message4,  
                  const Type1 message5, const Type2 message6){
  test_print(message1, message2, message3, message4, message5, message6, message7, message8, message9, message10);
  test_println();
}                 
template <typename Type1, typename Type2, typename Type3, typename Type4, 
          typename Type5, typename Type6>
void test_print(const Type1 message1, const Type2 message2, 
                  const Type1 message3, const Type2 message4,  
                  const Type1 message5, const Type2 message6){
  test_print(message1, message2, message3, message4, message5, message6, message7, message8, message9, message10);
}                  

template <typename Type1, typename Type2, typename Type3, typename Type4, 
          typename Type5, typename Type6, typename Type7>
void test_println(const Type1 message1, const Type2 message2, 
                  const Type1 message3, const Type2 message4,  
                  const Type1 message5, const Type2 message6,  
                  const Type1 message7){
  test_print(message1, message2, message3, message4, message5, message6, message7, message8, message9, message10);
  test_println();
}                  
template <typename Type1, typename Type2, typename Type3, typename Type4, 
          typename Type5, typename Type6, typename Type7>
void test_print(const Type1 message1, const Type2 message2, 
                  const Type1 message3, const Type2 message4,  
                  const Type1 message5, const Type2 message6,  
                  const Type1 message7){
  test_print(message1, message2, message3, message4, message5, message6, message7, message8, message9, message10);
}                  

template <typename Type1, typename Type2, typename Type3, typename Type4, 
          typename Type5, typename Type6, typename Type7, typename Type8>
void test_println(const Type1 message1, const Type2 message2, 
                  const Type1 message3, const Type2 message4,  
                  const Type1 message5, const Type2 message6,  
                  const Type1 message7, const Type2 message8){
  test_print(message1, message2, message3, message4, message5, message6, message7, message8, message9, message10);
  test_println();
}                  
template <typename Type1, typename Type2, typename Type3, typename Type4, 
          typename Type5, typename Type6, typename Type7, typename Type8>
void test_print(const Type1 message1, const Type2 message2, 
                  const Type1 message3, const Type2 message4,  
                  const Type1 message5, const Type2 message6,  
                  const Type1 message7, const Type2 message8){
  test_print(message1, message2, message3, message4, message5, message6, message7, message8, message9, message10);
}                  

template <typename Type1, typename Type2, typename Type3, typename Type4, 
          typename Type5, typename Type6, typename Type7, typename Type8, 
          typename Type9>
void test_println(const Type1 message1, const Type2 message2, 
                  const Type1 message3, const Type2 message4,  
                  const Type1 message5, const Type2 message6,  
                  const Type1 message7, const Type2 message8,  
                  const Type1 message9){
  test_print(message1, message2, message3, message4, message5, message6, message7, message8, message9, message10);
  test_println();
}                  
template <typename Type1, typename Type2, typename Type3, typename Type4, 
          typename Type5, typename Type6, typename Type7, typename Type8, 
          typename Type9>
void test_print(const Type1 message1, const Type2 message2, 
                  const Type1 message3, const Type2 message4,  
                  const Type1 message5, const Type2 message6,  
                  const Type1 message7, const Type2 message8,  
                  const Type1 message9){
  test_print(message1, message2, message3, message4, message5, message6, message7, message8, message9, message10);
}                  

template <typename Type1, typename Type2, typename Type3, typename Type4, 
          typename Type5, typename Type6, typename Type7, typename Type8, 
          typename Type9, typename Type10>
void test_println(const Type1 message1, const Type2 message2, 
                  const Type1 message3, const Type2 message4,  
                  const Type1 message5, const Type2 message6,  
                  const Type1 message7, const Type2 message8,  
                  const Type1 message9, const Type2 message10);                  
template <typename Type1, typename Type2, typename Type3, typename Type4, 
          typename Type5, typename Type6, typename Type7, typename Type8, 
          typename Type9, typename Type10>
void test_print(const Type1 message1, const Type2 message2, 
                  const Type1 message3, const Type2 message4,  
                  const Type1 message5, const Type2 message6,  
                  const Type1 message7, const Type2 message8,  
                  const Type1 message9, const Type2 message10);                  


template <typename Type1, typename Type2, typename Type3, typename Type4, 
          typename Type5, typename Type6, typename Type7, typename Type8, 
          typename Type9, typename Type10>
void test_println(const Type1 message1, const Type2 message2, 
                  const Type1 message3, const Type2 message4,  
                  const Type1 message5, const Type2 message6,  
                  const Type1 message7, const Type2 message8,  
                  const Type1 message9, const Type2 message10) {
  test_print(message1, message2, message3, message4, message5, message6, message7, message8, message9, message10);
  test_println();
}
template <typename Type1, typename Type2, typename Type3, typename Type4, 
          typename Type5, typename Type6, typename Type7, typename Type8, 
          typename Type9, typename Type10>
void test_print(const Type1 message1, const Type2 message2, 
                  const Type1 message3, const Type2 message4,  
                  const Type1 message5, const Type2 message6,  
                  const Type1 message7, const Type2 message8,  
                  const Type1 message9, const Type2 message10) {
  test_print(message1);
  test_print(message2);
  test_print(message3);
  test_print(message4);
  test_print(message5);
  test_print(message6);
  test_print(message7);
  test_print(message8);
  test_print(message9);
  test_print(message10);
}
                  
                  

// Macros
// https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html#Standard-Predefined-Macros
#define assert2(truth, Message) \
  if (true) { \
    const __FlashStringHelper* __assertion_message = F(Message); \
    if (truth) { \
      test_succeeded(__assertion_message); \
    } else { \
      test_failed(__assertion_message); \
    }\
  }
  
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

