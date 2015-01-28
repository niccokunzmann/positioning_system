
#include "positioning_system.h"


void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  if (Function<double>::test_all()) {
    Serial.println("ok... all tests passed.");
  }
  
}

void loop() {
  
  
}

