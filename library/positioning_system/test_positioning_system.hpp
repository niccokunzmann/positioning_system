
#ifndef positioning_system_h
#define positioning_system_h

#include "hpa.h"
#include "Arduino.h"

// from http://forum.arduino.cc/index.php/topic,85840.0.html
#ifdef PROGMEM
#undef PROGMEM
#define PROGMEM __attribute__((section(".progmem.data")))
#endif


void setup_tests();
void teardown_tests();
void test_positioning_system_1();
void test_positioning_system_2();
void test_positioning_system_3();
void test_positioning_system_4();

int get_number_of_succeeded_tests();
int get_number_of_failed_tests();
void use_verbose_output(boolean verbose);

void println0();

template <typename Type1> 
void print1(Type1 message1) {
  Serial.print(message1);
  Serial.flush();
}
template <>
void print1<HPA::xreal> (HPA::xreal message1);

template <typename Type1> 
void println1(Type1 message1) {
  print1(message1);
  println0();
}


template <typename Type1, typename Type2>
void println2(Type1 message1, Type2 message2) {
  print2(message1, message2);
  println0();
}                 

template <typename Type1, typename Type2>
void print2(Type1 message1, Type2 message2) {
  print1(message1);
  print1(message2);  
}

template <typename Type1, typename Type2, typename Type3>
void println3(Type1 message1, Type2 message2, 
              Type3 message3){
  print3(message1, message2, message3);
  println0();
}                  
template <typename Type1, typename Type2, typename Type3>
void print3(Type1 message1, Type2 message2, 
            Type3 message3){
  print2(message1, message2);
  print1(message3);
}                  

template <typename Type1, typename Type2, typename Type3, typename Type4>
void println4(Type1 message1, Type2 message2, 
              Type3 message3, Type4 message4){
  print4(message1, message2, message3, message4);
  println0();
}                  
template <typename Type1, typename Type2, typename Type3, typename Type4>
void print4(Type1 message1, Type2 message2, 
            Type3 message3, Type4 message4){
  print2(message1, message2);
  print2(message3, message4);
}                  

template <typename Type1, typename Type2, typename Type3, typename Type4, 
          typename Type5>
void println5(Type1 message1, Type2 message2, 
              Type3 message3, Type4 message4,  
              Type5 message5){
  print5(message1, message2, message3, message4, message5);
  println0();
}                  
template <typename Type1, typename Type2, typename Type3, typename Type4, 
          typename Type5>
void print5(Type1 message1, Type2 message2, 
            Type3 message3, Type4 message4,  
            Type5 message5){
  print4(message1, message2, message3, message4);
  print1(message5);
}                  

template <typename Type1, typename Type2, typename Type3, typename Type4, 
          typename Type5, typename Type6>
void println6(Type1 message1, Type2 message2, 
              Type3 message3, Type4 message4,  
              Type5 message5, Type6 message6){
  print6(message1, message2, message3, message4, message5, message6);
  println0();
}                 
template <typename Type1, typename Type2, typename Type3, typename Type4, 
          typename Type5, typename Type6>
void print6(Type1 message1, Type2 message2, 
            Type3 message3, Type4 message4,  
            Type5 message5, Type6 message6){
  print4(message1, message2, message3, message4);
  print2(message5, message6);
}                  

template <typename Type1, typename Type2, typename Type3, typename Type4, 
          typename Type5, typename Type6, typename Type7>
void println7(Type1 message1, Type2 message2, 
              Type3 message3, Type4 message4,  
              Type5 message5, Type6 message6,  
              Type7 message7){
  print7(message1, message2, message3, message4, message5, message6, message7);
  println0();
}                  
template <typename Type1, typename Type2, typename Type3, typename Type4, 
          typename Type5, typename Type6, typename Type7>
void print7(Type1 message1, Type2 message2, 
            Type3 message3, Type4 message4,  
            Type5 message5, Type6 message6,  
            Type7 message7){
  print4(message1, message2, message3, message4);
  print3(message5, message6, message7);
}                  

template <typename Type1, typename Type2, typename Type3, typename Type4, 
          typename Type5, typename Type6, typename Type7, typename Type8>
void println8(Type1 message1, Type2 message2, 
              Type3 message3, Type4 message4,  
              Type5 message5, Type6 message6,  
              Type7 message7, Type8 message8){
  print8(message1, message2, message3, message4, message5, message6, message7, message8);
  println0();
}                  
template <typename Type1, typename Type2, typename Type3, typename Type4, 
          typename Type5, typename Type6, typename Type7, typename Type8>
void print8(Type1 message1, Type2 message2, 
            Type3 message3, Type4 message4,  
            Type5 message5, Type6 message6,  
            Type7 message7, Type8 message8){
  print4(message1, message2, message3, message4);
  print4(message5, message6, message7, message8);
}                  

template <typename Type1, typename Type2, typename Type3, typename Type4, 
          typename Type5, typename Type6, typename Type7, typename Type8, 
          typename Type9>
void println9(Type1 message1, Type2 message2, 
              Type3 message3, Type4 message4,  
              Type5 message5, Type6 message6,  
              Type7 message7, Type8 message8,  
              Type9 message9){
  print9(message1, message2, message3, message4, message5, message6, message7, message8, message9);
  println0();
}                  
template <typename Type1, typename Type2, typename Type3, typename Type4, 
          typename Type5, typename Type6, typename Type7, typename Type8, 
          typename Type9>
void print9(Type1 message1, Type2 message2, 
            Type3 message3, Type4 message4,  
            Type5 message5, Type6 message6,  
            Type7 message7, Type8 message8,  
            Type9 message9){
  print8(message1, message2, message3, message4, message5, message6, message7, message8);
  print1(message9);
}                  

template <typename Type1, typename Type2, typename Type3, typename Type4, 
          typename Type5, typename Type6, typename Type7, typename Type8, 
          typename Type9, typename Type10>
void println10(Type1 message1, Type2 message2, 
               Type3 message3, Type4 message4,  
               Type5 message5, Type6 message6,  
               Type7 message7, Type8 message8,  
               Type9 message9, Type10 message10) {
  print10(message1, message2, message3, message4, message5, message6, message7, message8, message9, message10);
  println0();
}
template <typename Type1, typename Type2, typename Type3, typename Type4, 
          typename Type5, typename Type6, typename Type7, typename Type8, 
          typename Type9, typename Type10>
void print10(Type1 message1, Type2 message2, 
             Type3 message3, Type4 message4,  
             Type5 message5, Type6 message6,  
             Type7 message7, Type8 message8,  
             Type9 message9, Type10 message10) {
  print8(message1, message2, message3, message4, message5, message6, message7, message8);
  print2(message9, message10);
}

extern int tests_succeeded;
extern int tests_failed;
extern boolean verbose_tests;
extern boolean last_message_was_success;

template <typename MessageType>
void succeeded(MessageType message) {
  tests_succeeded++;
  if (Serial) {
    if (verbose_tests) {
      println2(F("Success: "), message);
    } else {
      print1(F(".")); 
    }
  }
  last_message_was_success = true;
}

template <typename MessageType>
void failed(MessageType message) {
  tests_failed++;
  if (Serial) {
    if (verbose_tests) {
      if (last_message_was_success) {
        println0();
      }
      println2(F("AssertionError: "), message); 
    } else {
      print1(F("F"));
    }
  }
  last_message_was_success = false;
}
                  
template <typename MessageType>
void assert2(boolean truth, MessageType assertion_message) {
  if (truth) { 
    succeeded(assertion_message); 
  } else { 
    failed(assertion_message); 
  }
}

// Macros
// https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html#Standard-Predefined-Macros
  
#define assert1(truth) assert2(truth, F(#truth))

#define assert_equals2(A, B, Message) assert2((A) == (B), Message)
#define _assert_equals(A, B, Message) assert_equals2(A, B, F(#Message))
#define assert_equals(A, B) _assert_equals(A, B, A == B)

#define assert_not_equals2(A, B, Message) assert2((A) != (B), Message)
#define _assert_not_equals(A, B, Message) assert_not_equals2(A, B, F(#Message))
#define assert_not_equals(A, B) _assert_not_equals(A, B, A != B)

#define assert_approximates2(A, B, Message) assert2(approximates((A),(B)), Message)
#define _assert_approximates(A, B, Message) assert_approximates2(A, B, F(#Message))
#define assert_approximates(A, B) _assert_approximates(A, B, A =~= B)

#endif

