
#include "positioning_system.h"


void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  Serial.println("Starting Tests");
  test_success = true;
  delay(1000);
  test_all();
//  if (test_success) {
//    Serial.println("ok... all tests passed.");
//  }
  
}

void loop() {
  
  
}