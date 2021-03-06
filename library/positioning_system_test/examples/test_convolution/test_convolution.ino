
#include "positioning_system_test.h"

test(frequency_of_1_is_invalid) {
  Convolver convolver = Convolver(1, 7);
  assertFalse(convolver.is_valid());
}

test(frequency_of_0_is_invalid) {
  Convolver convolver = Convolver(0, 7);
  assertFalse(convolver.is_valid());
}

test(frequencies_must_be_positive) {
  Convolver convolver = Convolver(-31, 7);
  assertFalse(convolver.is_valid());
}

test(frequency_does_not_convolve_with_doubled_frequency) {
  Convolver convolver = Convolver(4, 7);
  convolver.add_sample(-1);
  convolver.add_sample(1);
  convolver.add_sample(-1);
  convolver.add_sample(1);
  assertEqual(convolver.squared_intensity(), 0L);
}

test(frequency_does_not_convolve_with_half_frequency) {
  Convolver convolver = Convolver(2, 7);
  convolver.add_sample(0);
  convolver.add_sample(1);
  convolver.add_sample(0);
  convolver.add_sample(-1);
  assertEqual(convolver.squared_intensity(), 0L);
}

test(recognize_own_frequency) {
  Convolver convolver = Convolver(4, 7);
  convolver.add_sample(0);
  convolver.add_sample(1);
  convolver.add_sample(0);
  convolver.add_sample(-1);
  assertMore(convolver.squared_intensity(), 0L);
}

test(one_value_is_recognized) {
  Convolver convolver = Convolver(12, 7);
  convolver.add_sample(3);
  assertMore(convolver.squared_intensity(), 0L);
}

test(removing_values_4) {
  // precondition is one_value_is_recognized
  Convolver convolver = Convolver(12, 5);
  convolver.add_sample(333);
  for (int i = 0; i < 5; ++i) {
    convolver.remove_sample(0);
    convolver.add_sample(0);
  }
  convolver.remove_sample(333);
  assertEqual(convolver.squared_intensity(), 0L);
}

test(maximum_samples_are_no_overflow_problem_2) {
  Convolver convolver = Convolver(2, 100);
  for (int i = 0; i < 50 ; ++i) {
    convolver.add_sample(-511);
    convolver.add_sample(511);
  }
  assertMore(convolver.squared_intensity(), 0L);
}

test(maximum_samples_are_no_overflow_problem_4) {
  Convolver convolver = Convolver(4, 100);
  for (int i = 0; i < 25 ; ++i) {
    convolver.add_sample(-511);
    convolver.add_sample(-511);
    convolver.add_sample(511);
    convolver.add_sample(511);
  }
  assertMore(convolver.squared_intensity(), 0L);
}

test(constant_value_added_to_samples_does_not_influence_value) {
  Convolver convolver1 = Convolver(4, 100);
  Convolver convolver2 = Convolver(4, 100);
  for (int i = 0; i < 50 ; ++i) {
    convolver1.add_sample(-511);
    convolver2.add_sample(0);
    convolver1.add_sample(511);
    convolver2.add_sample(1022);
  }
  assertEqual(convolver1.squared_intensity(), convolver2.squared_intensity());
}

test(too_big_sample_size_does_not_work) {
  // 31 bit long - 8 bit - bits(length of samples) - sample_bits > 0
  Convolver convolver = Convolver(4, 128, 32);
  assertFalse(convolver.is_valid());
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  Test::run();
}
