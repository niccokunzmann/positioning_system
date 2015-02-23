
#ifndef unit_conversion_hpp
#define unit_conversion_hpp

#include "units.hpp"

Time signal_position_to_time_difference(
      const SignalPosition signal_offset, 
      const SamplingRate sampling_rate
      );

SignalPosition time_to_signal_position(
      const Time signal_time, 
      const SamplingRate sampling_rate
      );

void compute_time_difference(
      const SignalPosition base_frequency_offset, 
      const SignalPosition second_frequency_offset, 
      const SignalPosition third_frequency_offset, 
      const SamplingRate sampling_rate, 
      Time *time_difference_1, 
      Time *time_difference_2, 
      );

SignalPosition maximum_sample_position(
      const NumberOfSamples signal_length, 
      const SamplingRate sampling_rate
      );

#endif