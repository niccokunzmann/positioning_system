
#include "Location.hpp"

Location::Location(
      PositioningSystemConfiguration _configuration
      ) {
  configuration = _configuration;
  const uint_8 running_median_size = configuration.running_median_size()
  frequency_1_offset_medians = RunningMedian(running_median_size);
  frequency_2_offset_medians = RunningMedian(running_median_size);
  frequency_3_offset_medians = RunningMedian(running_median_size);
  
  const short samples_in_buffer = configuration.number_of_samples_in_convolution_buffer();
  const uint_8 sample_bits = configuration.bits_used_by_samples()
  frequency_1_convolver = Convolver(
        configuration.wave_length_in_samples_for_frequency_1(), 
        samples_in_buffer, sample_bits);
  frequency_2_convolver = Convolver(
        configuration.wave_length_in_samples_for_frequency_2(), 
        samples_in_buffer, sample_bits);
  frequency_3_convolver = Convolver(
        configuration.wave_length_in_samples_for_frequency_3(), 
        samples_in_buffer, sample_bits);

}

Location::~Location() {
  
}
    
Location::compute_new_coordinates() {
  
}

Location::x() {
  
}

Location::y() {
  
}

boolean Location::is_valid() {
  return frequency_1_convolver.is_valid() && 
         frequency_2_convolver.is_valid() &&
         frequency_3_convolver.is_valid()
}
    
