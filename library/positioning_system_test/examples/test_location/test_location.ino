
#include "positioning_system_test.h"



test(add_sample) {
  Location location = Location(&default_configuration);
  location.add_sample(12);
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  Test::run();
}
