
#include "positioning_system.h"


void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  test_success = true;
  test_coefficients();
  if (test_success) {
    Serial.println("ok... all tests passed.")
  }
  
}

void loop() {
  
  
}