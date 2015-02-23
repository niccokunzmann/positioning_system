
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





