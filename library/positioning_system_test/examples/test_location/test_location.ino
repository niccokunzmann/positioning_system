
#include "positioning_system_test.h"
/*
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
*/
test(try_out_a_signal) {
  Location location = Location(&default_configuration);
  assertTrue(location.is_valid());
  add_samples_for_position(0.3, 0.4, &location, &default_configuration);
  location.compute_new_coordinates();
  pvar(location.y());
  pvar(location.x());
  assertApproximately(location.y(), 0.4);
  assertApproximately(location.x(), 0.3);
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  Test::run();
}
