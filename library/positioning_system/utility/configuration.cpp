
#include "configuration.hpp"
#include "Arduino.h"
#include "math.h"

short GCD(short a, short b) {
  // https://en.wikipedia.org/wiki/Greatest_common_divisor
  short t;
  while (b) {
    t = b;
    b = a % b;
    a = t;
  }
  return a;
}

long LCM(long a, long b) {
  // https://en.wikipedia.org/wiki/Least_common_multiple
  return a * b / GCD(a, b);
}

const uint8_t configuration::running_median_size() {
  time_to_listen_to_signals_for_location_in_seconds
  return ;
}
const short configuration::wave_length_in_samples_for_frequency_1() {
  return sampling_frequency_in_hertz / frequency_1_in_hertz;
}
const short configuration::wave_length_in_samples_for_frequency_2() {
  return sampling_frequency_in_hertz / frequency_2_in_hertz;
}
const short configuration::wave_length_in_samples_for_frequency_3() {
  return sampling_frequency_in_hertz / frequency_3_in_hertz;
}
const short configuration::number_of_samples_in_convolution_buffer() {
  long n;
  n = LCM(wave_length_in_samples_for_frequency_1(), wave_length_in_samples_for_frequency_2());
  n = LCM(wave_length_in_samples_for_frequency_3(), n);
  short minimum = length_of_a_tone_in_samples();
  return ((minimum - 1) / n + 1) * n;
}
const int speaker_1_frequency_in_hertz() {
  return sampling_frequency_in_hertz / wave_length_in_samples_for_frequency_1();
}
const int speaker_2_frequency_in_hertz() {
  return sampling_frequency_in_hertz / wave_length_in_samples_for_frequency_2();
}
const int speaker_3_frequency_in_hertz() {
  return sampling_frequency_in_hertz / wave_length_in_samples_for_frequency_3();
}

const int8_t configuration::bits_used_by_samples() {
  int bits = 0;
  int sample_difference = maximum_sample_value - minimum_sample_value;
  if (sample_difference < 0) {
    sample_difference = -sample_difference;
  }
  while (sample_difference) {
    sample_difference >>= 1;
    ++bits;
  }
  return bits;
}
const NumberOfSamples configuration::samples_between_signal_beginnings() {
  double maximum_distance_in_meters = max(max(
        distance_between_speaker_1_and_speaker_2_in_meters, 
        distance_between_speaker_2_and_speaker_3_in_meters), 
        distance_between_speaker_3_and_speaker_1_in_meters);
  double maximum_distance_in_seconds = maximum_distance_in_meters / speed_of_sound_in_meters_per_second;
  return round(maximum_distance_in_seconds * sampling_frequency_in_hertz);
}
const NumberOfSamples configuration::maximum_change_of_following_signal_in_number_of_samples() {
  double time_robot_travelled_in_samples = samples_between_signal_beginnings();
  double time_robot_travelled_in_seconds = time_robot_travelled_in_samples /* / sampling_frequency_in_hertz */;
  double distance_robot_travelled_in_meters = time_robot_travelled_in_seconds * maximum_speed_of_robot_in_meters_per_second;
  double time_sound_travelled_in_seconds = distance_robot_travelled_in_meters / speed_of_sound_in_meters_per_second;
  double time_sound_travelled_in_samples = time_sound_travelled_in_seconds /* * sampling_frequency_in_hertz */;
  return max(time_sound_travelled_in_samples, length_of_a_tone_in_samples());
}
const NumberOfSamples configuration::length_of_a_tone_in_samples() {
  return time_to_signal_position(length_of_a_tone_in_milliseconds / 1000., sampling_frequency_in_hertz);
}
const SpeakerPosition configuration::A() {
  SpeakerPosition p;
  SpeakerPosition.x = 0;
  SpeakerPosition.y = 0;
  return p;
} // frequency 3
const SpeakerPosition configuration::B() {
  SpeakerPosition p;
  SpeakerPosition.x = distance_between_speaker_1_and_speaker_2_in_meters;
  SpeakerPosition.y = 0;
  return p;
} // base frequency 1
const SpeakerPosition configuration::C() {
  SpeakerPosition p;
  double c = distance_between_speaker_1_and_speaker_2_in_meters;
  double a = distance_between_speaker_2_and_speaker_3_in_meters;
  double b = distance_between_speaker_3_and_speaker_1_in_meters;
  double x = (c * c + b * b - a * a) / (c + c);
  SpeakerPosition p;
  p.x = x;
  p.y = sqrt(b * b - x * x);
  return p;
} // frequency 2