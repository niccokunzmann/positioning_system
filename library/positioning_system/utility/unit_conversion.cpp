
#include "Arduino.h"
#include "unit_conversion.hpp"

Time signal_position_to_time(
      const SignalPosition signal_offset, 
      const SamplingRate sampling_rate
      ) {
  Time t = signal_offset;
  t /= sampling_rate;
  return t;
}

SignalPosition time_to_signal_position(
      const Time signal_time, 
      const SamplingRate sampling_rate
      ) {
  return round(signal_time * sampling_rate);
}

void compute_time_difference(
      const SignalPosition base_frequency_offset, 
      const SignalPosition second_frequency_offset, 
      const SignalPosition third_frequency_offset, 
      const SamplingRate sampling_rate, 
      Time *time_difference_1, 
      Time *time_difference_2
      ) {
  const SignalPosition distance_between_peaks = base_frequency_offset;
  const SignalPosition expected_position_offset = distance_between_peaks / 3;
  SignalPosition position_difference_1 = second_frequency_offset - expected_position_offset;
  SignalPosition position_difference_2 = third_frequency_offset - (expected_position_offset + expected_position_offset);
  position_difference_1 = normalize_position_difference(position_difference_1, distance_between_peaks);
  position_difference_2 = normalize_position_difference(position_difference_2, distance_between_peaks);
  *time_difference_1 = signal_position_to_time(position_difference_1, sampling_rate);
  *time_difference_2 = signal_position_to_time(position_difference_2, sampling_rate);
}

SignalPosition normalize_position_difference(
      SignalPosition position_difference, 
      const SignalPosition distance_between_peaks
      ) {
  while (distance_between_peaks - position_difference < position_difference) {
    position_difference = position_difference - distance_between_peaks;
  }
  while (distance_between_peaks + position_difference < -position_difference) {
    position_difference = position_difference + distance_between_peaks;
  }
  return position_difference;
}

Time maximum_signal_time_difference(
      const NumberOfSamples samples_between_signal_beginnings, 
      const SamplingRate sampling_rate
      ) {
  Time t = samples_between_signal_beginnings;
  t /= 2;
  t /= sampling_rate;
  return t;
}





