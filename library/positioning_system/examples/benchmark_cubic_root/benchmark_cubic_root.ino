
#include "positioning_system.h"

int start_time;
int end_time;
int number_of_tests = 10000;
double sum;

void setup() {
  Serial.begin(9600);
  while (!Serial);
}

void print_result() {
  Serial.print("Needed ");
  Serial.print(end_time - start_time);
  Serial.print("ms for ");
  Serial.print(number_of_tests);
  Serial.print(" curt_1(i). Sum: ");
  Serial.print(sum);
  Serial.println();
}

void loop() {
  
  Serial.print("curt_1: ");
  sum = 0;
  start_time = millis();
  for (int i = number_of_tests; i > 0; --i) {
    sum += curt_1(i);
  }
  end_time = millis();
  print_result();
  
  Serial.print("curt_2: ");
  sum = 0;
  start_time = millis();
  for (int i = number_of_tests; i > 0; --i) {
    sum += curt_2(i);
  }
  end_time = millis();
  print_result();
  
  Serial.print("curt_3: ");
  sum = 0;
  start_time = millis();
  for (int i = number_of_tests; i > 0; --i) {
    sum += curt_3(i);
  }
  end_time = millis();
  print_result();
  
}