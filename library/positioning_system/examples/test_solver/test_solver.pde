
#include "positioning_system.h"


void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  test_println("Starting Tests");
  test_success = true;
  test_all();
  if (test_success) {
    test_println("\nall tests passed");
  }
  
}

void loop() {
  
  
}