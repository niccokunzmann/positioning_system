
#include "Location.hpp"
#include "math.h"

Location::Location(
      PositioningSystemConfiguration _configuration
      ) {
  configuration = _configuration;
  const uint_8 running_median_size = configuration.running_median_size()
  frequency_1_offset_medians = RunningMedian(running_median_size);
  frequency_2_offset_medians = RunningMedian(running_median_size);
  frequency_3_offset_medians = RunningMedian(running_median_size);
  
  valid = frequency_1_offset_medians.is_valid() &&
          frequency_2_offset_medians.is_valid() &&
          frequency_3_offset_medians.is_valid();
  
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
       
  valid = frequency_1_convolver.is_valid() && 
          frequency_2_convolver.is_valid() && 
          frequency_3_convolver.is_valid() && valid;

  sample_buffer = SampleBuffer(samples_in_buffer);
  valid = sample_buffer.is_valid() && valid;
  
  peak_detection = PeakDetectionInAWindow(
        configuration.samples_between_signal_beginnings(),
         samples_in_buffer,
         configuration.maximum_change_of_following_signal_in_number_of_samples());
  
  location.x = NAN;
  location.y = NAN;
}

Location::~Location() {
  
}

void Location::add_sample(Sample new_sample) {
  if (!valid) {
    return;
  }
  Sample old_sample = sample_buffer.replaced_by(new_sample);
  frequency_1_convolver.replace_sample(old_sample, new_sample);
  frequency_2_convolver.replace_sample(old_sample, new_sample);
  frequency_3_convolver.replace_sample(old_sample, new_sample);
  peak_detection.add_intensities(
        frequency_1_convolver.squared_intensity(), 
        frequency_2_convolver.squared_intensity(), 
        frequency_3_convolver.squared_intensity());
  if (peak_detection.reached_end_of_window()) {
    frequency_1_offset_medians.add(peak_detection.offset_of_base_frequency());
    frequency_2_offset_medians.add(peak_detection.offset_of_second_frequency());
    frequency_3_offset_medians.add(peak_detection.offset_of_third_frequency());
    peak_detection.reset_window();
  }
}
    
void Location::compute_new_coordinates() {
  if (!valid) {
    return;
  }
  Seconds time_difference_1;
  Seconds time_difference_2;
  compute_time_difference(
        frequency_1_offset_medians.getMedian(), 
        frequency_2_offset_medians.getMedian(), 
        frequency_3_offset_medians.getMedian(), 
        configuration.sampling_frequency_in_hertz, 
        &time_difference_1, 
        &time_difference_2);
  const Meter BP_minus_CP = configuration.speed_of_sound_in_meters_per_second * time_difference_1;
  const Meter BP_minus_AP = configuration.speed_of_sound_in_meters_per_second * time_difference_2;
  location = position(
        BP_minus_CP, BP_minus_AP, 
        const SpeakerPosition configuration.A(), 
        const SpeakerPosition configuration.B(), 
        const SpeakerPosition configuration.C());
}

double Location::x() {
  if (!valid) {
    return NAN;
  }
  return location.x;
}

double Location::y() {
  if (!valid) {
    return NAN;
  }
  return location.y;
}

boolean Location::is_valid() {
  return valid;
}
    
