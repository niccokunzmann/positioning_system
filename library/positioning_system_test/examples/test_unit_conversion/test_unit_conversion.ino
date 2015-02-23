
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

void setup() {
  Serial.begin(9600);
}

void loop() {
  Test::run();
}



