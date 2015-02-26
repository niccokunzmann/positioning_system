
#include "positioning_system_test.h"
#line 4

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

test(number_of_samples_in_convolution_buffer_1) {
  PositioningSystemConfiguration configuration = PositioningSystemConfiguration();
  configuration.frequency_1_in_hertz = 2000; //4
  configuration.frequency_2_in_hertz = 1600; //5
  configuration.frequency_3_in_hertz = 1333; //6
  configuration.length_of_a_tone_in_milliseconds = 10; // minimum 80 samples
  configuration.sampling_frequency_in_hertz = 8000;
  assertEqual(configuration.number_of_samples_in_convolution_buffer(), 120);
}

test(number_of_samples_in_convolution_buffer_2) {
  PositioningSystemConfiguration configuration = PositioningSystemConfiguration();
  configuration.frequency_1_in_hertz = 2000; //4
  configuration.frequency_2_in_hertz = 1600; //5
  configuration.frequency_3_in_hertz = 800;  //10
  configuration.length_of_a_tone_in_milliseconds = 30; // minimum 240 samples
  configuration.sampling_frequency_in_hertz = 8000;
  assertEqual(configuration.number_of_samples_in_convolution_buffer(), 240);
}

test(number_of_samples_in_convolution_buffer_3) {
  PositioningSystemConfiguration configuration = PositioningSystemConfiguration();
  configuration.frequency_1_in_hertz = 100; //10
  configuration.frequency_2_in_hertz = 333; //3
  configuration.frequency_3_in_hertz = 200; //5
  configuration.length_of_a_tone_in_milliseconds = 13; // minimum 13 samples
  configuration.sampling_frequency_in_hertz = 1000;
  assertEqual(configuration.number_of_samples_in_convolution_buffer(), 30);
}

test(length_of_a_tone_in_samples) {
  PositioningSystemConfiguration configuration = PositioningSystemConfiguration();
  configuration.length_of_a_tone_in_milliseconds = 23;
  configuration.sampling_frequency_in_hertz = 1000;
  assertEqual(configuration.length_of_a_tone_in_samples(), 23);
}

test(minimum_samples_between_signal_beginnings_and_running_median_size) {
  PositioningSystemConfiguration configuration = PositioningSystemConfiguration();
  configuration.length_of_a_tone_in_milliseconds = 10;
  configuration.sampling_frequency_in_hertz = 4000;
  configuration.distance_between_speaker_1_and_speaker_2_in_meters = 3;
  configuration.distance_between_speaker_2_and_speaker_3_in_meters = 4;
  configuration.distance_between_speaker_3_and_speaker_1_in_meters = 5; // 5 meters
  configuration.speed_of_sound_in_meters_per_second = 100; // totally wrong but nice to compute
  // 50 ms run time max
  assertEqual(configuration.minimum_samples_between_signal_beginnings(), 200 /*0.05 * 4000*/);
  configuration.time_to_listen_to_signals_for_location_in_seconds = 1;
  assertEqual(configuration.running_median_size(), 21/*20*/);
}

test(bits_used_by_samples_127) {
  PositioningSystemConfiguration configuration = PositioningSystemConfiguration();
  configuration.minimum_sample_value = 0;
  configuration.maximum_sample_value = 127;
  assertEqual(configuration.bits_used_by_samples(), 7);
}

test(bits_used_by_samples_1023) {
  PositioningSystemConfiguration configuration = PositioningSystemConfiguration();
  configuration.minimum_sample_value = 0;
  configuration.maximum_sample_value = 1023;
  assertEqual(configuration.bits_used_by_samples(), 10);
}

test(bits_used_by_samples_511) {
  PositioningSystemConfiguration configuration = PositioningSystemConfiguration();
  configuration.minimum_sample_value = -511;
  configuration.maximum_sample_value = +511;
  assertEqual(configuration.bits_used_by_samples(), 10);
}

test(maximum_change_of_following_signal_in_number_of_samples) {
  PositioningSystemConfiguration configuration = PositioningSystemConfiguration();
  configuration.speed_of_sound_in_meters_per_second = 200; // totally wrong but nice to compute
  configuration.maximum_speed_of_robot_in_meters_per_second = 2;
  double t2 = configuration.samples_between_signal_beginnings();
  assertEqual(configuration.maximum_change_of_following_signal_in_number_of_samples(), round(t2 / 100));
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  Test::run();
}
