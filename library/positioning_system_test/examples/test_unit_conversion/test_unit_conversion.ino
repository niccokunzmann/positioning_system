
#include "positioning_system_test.h"
#line 4

test(signal_position_to_time) {
  assertEqual(signal_position_to_time(5, 5), 1.);
  assertEqual(signal_position_to_time(333, 4000), 333. / 4000.);
}

test(time_to_signal_position) {
  assertEqual(time_to_signal_position(5, 5), 25.);
  assertEqual(time_to_signal_position(0.05, 4000), 200); 
}

test(maximum_signal_time_difference) {
  assertEqual(maximum_signal_time_difference(2000, 10000), 0.1);
}

double dt1;
double dt2;

test(compute_time_difference_zero) {
  compute_time_difference(9, 3, 6, 1000, &dt1, &dt2);
  assertEqual(dt1, 0);
  assertEqual(dt2, 0);
}

test(compute_time_difference_plus_minus) {
  compute_time_difference(9, 4, 5, 1000, &dt1, &dt2);
  assertEqual(dt1,  0.001);
  assertEqual(dt2, -0.001);
}

test(time_difference_with_overflow) {
  compute_time_difference(20, 18, 2, 2000, &dt1, &dt2);
  assertApproximately(dt1 * 10000, -0.004333333333333333333  * 10000);
  assertApproximately(dt2 * 10000,  0.004333333333333333333 * 10000);
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  Test::run();
}



