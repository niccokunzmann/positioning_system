
#ifndef test_print_hpp
#define test_print_hpp

#include "Arduino.h"
#include "hpa.h"
#include "positioning_system.h"

// from http://forum.arduino.cc/index.php/topic,85840.0.html
#ifdef PROGMEM
#undef PROGMEM
#define PROGMEM __attribute__((section(".progmem.data")))
#endif

#define pvar(V) println3(#V, F(": "), V);

void print_coefficients_to_serial(NumberArgument a, NumberArgument b, NumberArgument c, NumberArgument d, NumberArgument e);

void println0();

template <typename Type1> 
void print1(Type1 message1) {
  Serial.print(message1);
  delay(30);
  Serial.flush();
}
template <> void print1<HPA::xreal> (HPA::xreal message1);
template <> void print1<struct xpr> (const struct xpr message1);
template <> void print1<double> (const double message1);

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

template <typename Type1, typename Type2, typename Type3, typename Type4, 
          typename Type5, typename Type6, typename Type7, typename Type8, 
          typename Type9, typename Type10, typename Type11>
void println11(Type1 message1, Type2 message2, 
               Type3 message3, Type4 message4,  
               Type5 message5, Type6 message6,  
               Type7 message7, Type8 message8,  
               Type9 message9, Type10 message10, 
               Type11 message11) {
  print11(message1, message2, message3, message4, message5, message6, message7, message8, message9, message10, message11);
  println0();
}
template <typename Type1, typename Type2, typename Type3, typename Type4, 
          typename Type5, typename Type6, typename Type7, typename Type8, 
          typename Type9, typename Type10, typename Type11>
void print11(Type1 message1, Type2 message2, 
             Type3 message3, Type4 message4,  
             Type5 message5, Type6 message6,  
             Type7 message7, Type8 message8,  
             Type9 message9, Type10 message10, 
             Type11 message11) {
  print8(message1, message2, message3, message4, message5, message6, message7, message8);
  print3(message9, message10, message11);
}

template <typename Type1, typename Type2, typename Type3, typename Type4, 
          typename Type5, typename Type6, typename Type7, typename Type8, 
          typename Type9, typename Type10, typename Type11, typename Type12>
void println12(Type1 message1, Type2 message2, 
               Type3 message3, Type4 message4,  
               Type5 message5, Type6 message6,  
               Type7 message7, Type8 message8,  
               Type9 message9, Type10 message10, 
               Type11 message11, Type12 message12) {
  print12(message1, message2, message3, message4, message5, message6, message7, message8, message9, message10, message11, message12);
  println0();
}
template <typename Type1, typename Type2, typename Type3, typename Type4, 
          typename Type5, typename Type6, typename Type7, typename Type8, 
          typename Type9, typename Type10, typename Type11, typename Type12>
void print12(Type1 message1, Type2 message2, 
             Type3 message3, Type4 message4,  
             Type5 message5, Type6 message6,  
             Type7 message7, Type8 message8,  
             Type9 message9, Type10 message10, 
             Type11 message11, Type12 message12) {
  print8(message1, message2, message3, message4, message5, message6, message7, message8);
  print4(message9, message10, message11, message12);
}

#endif