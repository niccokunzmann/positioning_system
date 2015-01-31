
#include "test_positioning_system.h"
#include "Arduino.h"
#include "test_solve.h"


void test_succeeded(const char* message, int line, const char* file) {
  if (Serial) {
    if (verbose_tests) {
     Serial.print("."); 
    };
  };
};

void test_failed(const char* message, int line, const char* file) {
  if (Serial) {
    if (verbose_tests) {
      Serial.print("In line "); 
      Serial.print(line); 
      Serial.print("\tin file "); 
      Serial.println(file); 
      Serial.print("AssertionError: "); 
      Serial.println(message); 
    } else {
      Serial.print("F");
    }
  }
}

void test_all() {
  Serial.println("a2");
  test_coefficients();
}