
#include "positioning_system_test.h"

test(gcd) {
  assertEqual(GCD(4, 5), 1);
  assertEqual(GCD(40, 5), 5);
  assertEqual(GCD(44, 55), 11);
  assertEqual(GCD(40, 56), 8);
}

test(lcm) {
  assertEqual(LCM(100, 101), 10100);
  assertEqual(LCM(5, 10), 10);
  assertEqual(LCM(50, 15), 150);
  assertEqual(LCM(2, 1), 2);
}

test(coordinates_of_the_speakers_with_90_degrees) {
  PositioningSystemConfiguration configuration = PositioningSystemConfiguration();
  configuration.distance_between_speaker_1_and_speaker_2_in_meters = 3;
  configuration.distance_between_speaker_2_and_speaker_3_in_meters = 4;
  configuration.distance_between_speaker_3_and_speaker_1_in_meters = 5;
  assertApproximately(configuration.A().x, 0.);
  assertApproximately(configuration.A().y, 0.);
  assertApproximately(configuration.B().x, 3.);
  assertApproximately(configuration.B().y, 0.);
  assertApproximately(configuration.C().x, 3.);
  assertApproximately(configuration.C().y, 4.);
}

test(coordinates_of_the_speakers) {
  PositioningSystemConfiguration configuration = PositioningSystemConfiguration();
  configuration.distance_between_speaker_1_and_speaker_2_in_meters = 0.2;
  configuration.distance_between_speaker_2_and_speaker_3_in_meters = sqrt(0.2 * 0.2 + 0.6 * 0.6);
  configuration.distance_between_speaker_3_and_speaker_1_in_meters = sqrt(0.4 * 0.4 + 0.6 * 0.6);
  assertApproximately(configuration.A().x, 0.);
  assertApproximately(configuration.A().y, 0.);
  assertApproximately(configuration.B().x, 0.2);
  assertApproximately(configuration.B().y, 0.);
  assertApproximately(configuration.C().x, 0.4);
  assertApproximately(configuration.C().y, 0.6);
}

test(wave_length_in_samples_for_frequency_1) {
  PositioningSystemConfiguration configuration = PositioningSystemConfiguration();
  configuration.frequency_1_in_hertz = 400;
  configuration.sampling_frequency_in_hertz = 2000;
  assertEqual(configuration.wave_length_in_samples_for_frequency_1(), 5);
  assertEqual(configuration.speaker_1_frequency_in_hertz(), 400);
}

test(wave_length_in_samples_for_frequency_2) {
  PositioningSystemConfiguration configuration = PositioningSystemConfiguration();
  configuration.frequency_2_in_hertz = 1607;
  configuration.sampling_frequency_in_hertz = 8000;
  assertEqual(configuration.wave_length_in_samples_for_frequency_2(), 5);
  assertEqual(configuration.speaker_2_frequency_in_hertz(), 1600);
}

test(wave_length_in_samples_for_frequency_3) {
  PositioningSystemConfiguration configuration = PositioningSystemConfiguration();
  configuration.frequency_3_in_hertz = 1400;
  configuration.sampling_frequency_in_hertz = 8000;
  assertEqual(configuration.wave_length_in_samples_for_frequency_3(), 6);
  assertEqual(configuration.speaker_3_frequency_in_hertz(), 1333);
}

    const uint8_t running_median_size();
    const short number_of_samples_in_convolution_buffer();
    const int8_t bits_used_by_samples();
    const NumberOfSamples samples_between_signal_beginnings();
    const NumberOfSamples length_of_a_tone_in_samples();
    const NumberOfSamples maximum_change_of_following_signal_in_number_of_samples();

void setup() {
  Serial.begin(9600);
}

void loop() {
  Test::run();
}
