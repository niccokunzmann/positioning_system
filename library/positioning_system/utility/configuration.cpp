
#include "configuration.hpp"
#include "Arduino.h"
#include "math.h"
#include "unit_conversion.hpp"

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

PositioningSystemConfiguration::PositioningSystemConfiguration(
      // for both
      double distance_between_speaker_1_and_speaker_2_in_meters,
      double distance_between_speaker_2_and_speaker_3_in_meters,
      double distance_between_speaker_3_and_speaker_1_in_meters,
      int frequency_1_in_hertz, 
      int frequency_2_in_hertz, 
      int frequency_3_in_hertz,
      int length_of_a_tone_in_milliseconds,
      double speed_of_sound_in_meters_per_second,
      // for location
      int microphone_input_pin,
      int sampling_frequency_in_hertz,
      double time_to_listen_to_signals_for_location_in_seconds,
      int minimum_sample_value,
      int maximum_sample_value,
      double maximum_speed_of_robot_in_meters_per_second,
      // for speakers
      int speaker_1_output_pin,
      int speaker_2_output_pin,
      int speaker_3_output_pin
      ): 
      // for both
      distance_between_speaker_1_and_speaker_2_in_meters(distance_between_speaker_1_and_speaker_2_in_meters),
      distance_between_speaker_2_and_speaker_3_in_meters(distance_between_speaker_2_and_speaker_3_in_meters),
      distance_between_speaker_3_and_speaker_1_in_meters(distance_between_speaker_3_and_speaker_1_in_meters),
      frequency_1_in_hertz(frequency_1_in_hertz),
      frequency_2_in_hertz(frequency_2_in_hertz),
      frequency_3_in_hertz(frequency_3_in_hertz),
      length_of_a_tone_in_milliseconds(length_of_a_tone_in_milliseconds),
      speed_of_sound_in_meters_per_second(speed_of_sound_in_meters_per_second),
      // for location
      microphone_input_pin(microphone_input_pin),
      sampling_frequency_in_hertz(sampling_frequency_in_hertz),
      time_to_listen_to_signals_for_location_in_seconds(time_to_listen_to_signals_for_location_in_seconds),
      minimum_sample_value(minimum_sample_value),
      maximum_sample_value(maximum_sample_value),
      maximum_speed_of_robot_in_meters_per_second(maximum_speed_of_robot_in_meters_per_second),
      // for speakers
      speaker_1_output_pin(speaker_1_output_pin),
      speaker_2_output_pin(speaker_2_output_pin),
      speaker_3_output_pin(speaker_3_output_pin) {
  
}
          
PositioningSystemConfiguration default_configuration = PositioningSystemConfiguration();

const uint8_t PositioningSystemConfiguration::running_median_size() {
  double time_to_listen_to_signals_for_location_in_samples = time_to_listen_to_signals_for_location_in_seconds * sampling_frequency_in_hertz;
  double offsets_produced_while_listening = time_to_listen_to_signals_for_location_in_samples / samples_between_signal_beginnings();
  if (offsets_produced_while_listening > 128) {
    return 128;
  }
  if (offsets_produced_while_listening < 0) {
    return 0;
  }
  return round(offsets_produced_while_listening + 0.5);
}

const NumberOfSamples PositioningSystemConfiguration::frequency_to_samples(int frequency) {
  return round(double(sampling_frequency_in_hertz) / double(frequency));
}

const short PositioningSystemConfiguration::wave_length_in_samples_for_frequency_1() {
  return frequency_to_samples(frequency_1_in_hertz);
}
const short PositioningSystemConfiguration::wave_length_in_samples_for_frequency_2() {
  return frequency_to_samples(frequency_2_in_hertz);
}
const short PositioningSystemConfiguration::wave_length_in_samples_for_frequency_3() {
  return frequency_to_samples(frequency_3_in_hertz);
}
const NumberOfSamples PositioningSystemConfiguration::number_of_samples_in_convolution_buffer() {
  long n;
  n = LCM(wave_length_in_samples_for_frequency_1(), wave_length_in_samples_for_frequency_2());
  n = LCM(wave_length_in_samples_for_frequency_3(), n);
  short minimum = length_of_a_tone_in_samples();
  return ((minimum - 1) / n + 1) * n;
}
const int PositioningSystemConfiguration::speaker_1_frequency_in_hertz() {
  return sampling_frequency_in_hertz / wave_length_in_samples_for_frequency_1();
}
const int PositioningSystemConfiguration::speaker_2_frequency_in_hertz() {
  return sampling_frequency_in_hertz / wave_length_in_samples_for_frequency_2();
}
const int PositioningSystemConfiguration::speaker_3_frequency_in_hertz() {
  return sampling_frequency_in_hertz / wave_length_in_samples_for_frequency_3();
}

const boolean PositioningSystemConfiguration::is_valid() {
  int f1 = speaker_1_frequency_in_hertz();
  int f2 = speaker_2_frequency_in_hertz();
  int f3 = speaker_3_frequency_in_hertz();
  return (f1 != f2) && (f2 != f3) && (f1 != f3);
}

const int8_t PositioningSystemConfiguration::bits_used_by_samples() {
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
const NumberOfSamples PositioningSystemConfiguration::samples_between_signal_beginnings() {
  double maximum_distance_in_meters = max(max(
        distance_between_speaker_1_and_speaker_2_in_meters, 
        distance_between_speaker_2_and_speaker_3_in_meters), 
        distance_between_speaker_3_and_speaker_1_in_meters);
  double maximum_distance_in_seconds = maximum_distance_in_meters / speed_of_sound_in_meters_per_second;
  return round(maximum_distance_in_seconds * sampling_frequency_in_hertz);
}
const NumberOfSamples PositioningSystemConfiguration::maximum_change_of_following_signal_in_number_of_samples() {
  double time_robot_travelled_in_samples = samples_between_signal_beginnings();
  double time_robot_travelled_in_seconds = time_robot_travelled_in_samples /* / sampling_frequency_in_hertz */;
  double distance_robot_travelled_in_meters = time_robot_travelled_in_seconds * maximum_speed_of_robot_in_meters_per_second;
  double time_sound_travelled_in_seconds = distance_robot_travelled_in_meters / speed_of_sound_in_meters_per_second;
  double time_sound_travelled_in_samples = time_sound_travelled_in_seconds /* * sampling_frequency_in_hertz */;
  return max(time_sound_travelled_in_samples, length_of_a_tone_in_samples());
}
const NumberOfSamples PositioningSystemConfiguration::length_of_a_tone_in_samples() {
  return time_to_signal_position(length_of_a_tone_in_milliseconds / 1000., sampling_frequency_in_hertz);
}
const SpeakerPosition PositioningSystemConfiguration::A() {
  SpeakerPosition p;
  p.x = 0;
  p.y = 0;
  return p;
} // frequency 3
const SpeakerPosition PositioningSystemConfiguration::B() {
  SpeakerPosition p;
  p.x = distance_between_speaker_1_and_speaker_2_in_meters;
  p.y = 0;
  return p;
} // base frequency 1
const SpeakerPosition PositioningSystemConfiguration::C() {
  SpeakerPosition p;
  double c = distance_between_speaker_1_and_speaker_2_in_meters;
  double a = distance_between_speaker_2_and_speaker_3_in_meters;
  double b = distance_between_speaker_3_and_speaker_1_in_meters;
  double x = (c * c + b * b - a * a) / (c + c);
  p.x = x;
  p.y = sqrt(b * b - x * x);
  return p;
} // frequency 2