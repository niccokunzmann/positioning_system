
#include "positioning_system_test.h"

test(default_configuration_fits_into_memory) {
  Location location = Location(&default_configuration);
  assertTrue(location.is_valid());
}

test(add_a_sample) {
  Location location = Location(&default_configuration);
  assertTrue(location.is_valid());
  location.add_sample(12);
  location.compute_new_coordinates();
  assertTrue(isnan(location.x()));
  assertTrue(isnan(location.y()));
}

test(no_x_and_y_coordinates_at_start) {
  Location location = Location(&default_configuration);
  assertTrue(location.is_valid());
  location.add_sample(12);
  location.compute_new_coordinates();
  assertTrue(isnan(NAN));
  assertTrue(isnan(location.x()));
  assertTrue(isnan(location.y()));
}

test(try_out_a_signal) {
  assertLocates(0.3, 0.4);
}

void setup() {
  TEST_APPROXIMATION_EPSILON = 0.01;
  Serial.begin(9600);
}

void loop() {
  Test::run();
}
