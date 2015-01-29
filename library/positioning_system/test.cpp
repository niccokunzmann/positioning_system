
#include "test.h"


void test_debug_print(const char* message, int line, const char* file) {
  if (Serial) {
    Serial.print("In line "); 
    Serial.print(line); 
    Serial.print("\tin file "); 
    Serial.println(file); 
    Serial.print("AssertionError: "); 
    Serial.println(message); 
  }
};