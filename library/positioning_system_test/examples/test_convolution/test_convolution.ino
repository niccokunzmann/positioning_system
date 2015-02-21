
#include "test_positoining_system.h"



test(convolve_0) {
  Convolver convolver = Convolver(20, 100);
  assertEqual(convolver.current_value(), 0);
}  

test(convolve_samples) {
  Convolver convolver = Convolver(20, 100);
  convolver.addSample(5)
  convolver.addSample(10)
  assertNotEqual(convolver.current_value(), 0);
}

test(convolve_samples_returns_to_0) {
  Convolver convolver = Convolver(20, 100);
  for (int i = 0; i < 20; ++i) {
    convolver.add_sample(5)
  }
  assertEqual(convolver.current_value(), 0);
}

void setup() {
  TEST_APPROXIMATION_EPSILON = 0.001;
  Serial.begin(9600);
}

void loop() {
  Test::run();
}
