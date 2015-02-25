
#include "positioning_system_test.h"



test(default_configuration_fits_into_memory) {
  Location location = Location(&default_configuration);
  assertTrue(location.is_valid());
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  Test::run();
}
