
#include "positioning_system_test.h"

test(sum_is_0_when_started) {
  AveragingSampleBuffer samples = AveragingSampleBuffer(100);
  assertEqual(samples.sum(), 0);
}

test(sums_increasing) {
  AveragingSampleBuffer samples = AveragingSampleBuffer(5);
  samples.replaced_by(7);
  assertEqual(samples.sum(), 7);
}

test(sums_increasing_2) {
  AveragingSampleBuffer samples = AveragingSampleBuffer(5);
  samples.replaced_by(7);
  samples.replaced_by(1);
  assertEqual(samples.sum(), 8);
}

test(sum_loses_values) {
  AveragingSampleBuffer samples = AveragingSampleBuffer(2);
  samples.replaced_by(7);
  samples.replaced_by(1);
  samples.replaced_by(1);
  assertEqual(samples.sum(), 2);
}

test(replaced_sample_comes_out) {
  SampleBuffer samples = SampleBuffer(2);
  samples.replaced_by(-1);
  samples.replaced_by(2);
  assertEqual(samples.replaced_by(3), -1);
}

test(starting_samples_are_zero) {
  SampleBuffer samples = SampleBuffer(8);
  for(int i = 0; i < 8; ++i) {
    assertEqual(samples.replaced_by(i), 0);
  }
}

test(samples_know_the_size) {
  SampleBuffer samples = SampleBuffer(100);
  assertEqual(samples.size(), 100);
}
test(samples_know_the_size_2) {
  SampleBuffer samples = SampleBuffer(5);
  assertEqual(samples.size(), 5);
}

test(samples_with_positive_size_are_valid) {
  SampleBuffer samples = SampleBuffer(5);
  assertTrue(samples.is_valid());
}
test(samples_with_negative_size_are_invalid) {
  SampleBuffer samples = SampleBuffer(-5);
  assertFalse(samples.is_valid());
}

test(samples_with_zero_size_are_invalid) {
  SampleBuffer samples = SampleBuffer(0);
  assertFalse(samples.is_valid());
}

test(average_samples_is_zero_when_created) {
  AveragingSampleBuffer samples = AveragingSampleBuffer(5);
  assertEqual(samples.average(), 0);
}

test(adding_samples_changes_the_average) {
  AveragingSampleBuffer samples = AveragingSampleBuffer(5);
  samples.replaced_by(5);
  assertEqual(samples.average(), 1);
}

test(adding_a_lot_of_samples_changes_the_average) {
  AveragingSampleBuffer samples = AveragingSampleBuffer(5);
  samples.replaced_by(300); // does not count
  samples.replaced_by(1);
  samples.replaced_by(13);
  samples.replaced_by(3);
  samples.replaced_by(5);
  samples.replaced_by(-7);
  assertEqual(samples.average(), 3);
}

test(half_life_sample_to_multiplier) {
  double m = half_life_sample_to_multiplier(2);
  assertApproximately(m * m, 0.5);
  m = half_life_sample_to_multiplier(4);
  assertApproximately(m * m * m * m, 0.5);
}

test(adding_samples) {
  ExponentialAverage average = ExponentialAverage(half_life_sample_to_multiplier(2), 0);
  average.add_sample(100);
  average.add_sample(100);
  assertEqual(average.average(), 50);
  assertEqual(average.normalize(20), -30);
  assertEqual(average.normalize(100), 50);
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  Test::run();
}