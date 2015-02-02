
#include "positioning_system.h"

void setup() {
  Serial.begin(9600);
  while (!Serial);
}

void loop() {
  int start_time;
  int end_time;
  int number_of_tests = 10000;
  double sum;
  
  test_print("curt_1: ");
  sum = 0;
  start_time = millis();
  for (int i = number_of_tests; i > 0; --i) {
    sum += curt_1(i);
  }
  end_time = millis();
  test_println("Needed ", end_time - start_time, "ms for ", number_of_tests, " curt_1(i). Sum: ", sum);
  
  test_print("curt_2: ");
  sum = 0;
  start_time = millis();
  for (int i = number_of_tests; i > 0; --i) {
    sum += curt_2(i);
  }
  end_time = millis();
  test_println("Needed ", end_time - start_time, "ms for ", number_of_tests, " curt_2(i). Sum: ", sum);
  
  test_print("curt_3: ");
  sum = 0;
  start_time = millis();
  for (int i = number_of_tests; i > 0; --i) {
    sum += curt_3(i);
  }
  end_time = millis();
  test_println("Needed ", end_time - start_time, "ms for ", number_of_tests, " curt_3(i). Sum: ", sum);
  
}