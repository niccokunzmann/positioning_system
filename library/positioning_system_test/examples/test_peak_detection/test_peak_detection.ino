
#include "positioning_system_test.h"

test(no_peak_at_start) {
  PeakDetection peak_detection = PeakDetection();
  assertEqual(peak_detection.maximum_value(), 0);
  assertEqual(peak_detection.maximum_index(), 0);
}

test(first_value_is_best_value) {
  PeakDetection peak_detection = PeakDetection();
  peak_detection.add_intensity(3L);
  assertEqual(peak_detection.maximum_value(), 3);
  assertEqual(peak_detection.maximum_index(), 1);
}

test(adding_several_values_and_finding_peak) {
  PeakDetection peak_detection = PeakDetection();
  peak_detection.add(4L);
  peak_detection.add(29L);
  peak_detection.add(218928398L);
  peak_detection.add(4L);
  assertEqual(peak_detection.maximum_value(), 218928398L);
  assertEqual(peak_detection.maximum_index(), 3);
}

test(skipping_values_yields_correct_value) {
  SkippingPeakDetection peak_detection = PeakDetection();
  peak_detection.skip_values(3);
  peak_detection.add(4L);
  peak_detection.add(4L);
  peak_detection.add(4L);
  peak_detection.add(2L);
  peak_detection.add(1L);
  assertEqual(peak_detection.maximum_value(), 2L);
  assertEqual(peak_detection.maximum_index(), 4);
}


test(skipping_values_can_be_tested_asked) {
  SkippingPeakDetection peak_detection = PeakDetection();
  peak_detection.skip_values(3);
  assertTrue(peak_detection.is_skipping_values());
}

test(is_not_skipping_values_after_a_while) {
  SkippingPeakDetection peak_detection = PeakDetection();
  peak_detection.skip_values(2);
  peak_detection.add(0L);
  peak_detection.add(0L);
  assertFalse(peak_detection.is_skipping_values());
}

test(can_use_skip_value_to_skip_values) {
  SkippingPeakDetection peak_detection = PeakDetection();
  peak_detection.skip_values(3);
  peak_detection.skip_value();
  peak_detection.skip_value();
  peak_detection.skip_value();
  assertFalse(peak_detection.is_skipping_values());
  peak_detection.skip_value();
  assertFalse(peak_detection.is_skipping_values());
}

test(peak_detection_is_not_skipping_values_at_the_beginning) {
  SkippingPeakDetection peak_detection = PeakDetection();
  assertFalse(peak_detection.is_skipping_values());
}




void setup() {
  Serial.begin(9600);
}

void loop() {
  Test::run();
}



