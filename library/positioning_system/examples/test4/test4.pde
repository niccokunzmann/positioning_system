
#include "positioning_system.h"


void setup() {

  Serial.begin(9600);
  while (!Serial);
  
  test_positioning_system_4();

}

void loop() {
  
}