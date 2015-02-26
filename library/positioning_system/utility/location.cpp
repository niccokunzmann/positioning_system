
#include "Location.hpp"
#include "configuration.hpp"
#include "RunningMedian.h"
#include "convolution.hpp"
#include "position.hpp"
#include "unit_conversion.hpp"
#include "samples.hpp"
#include "peak_detection.hpp"
#include "math.h"
#include "positioning_system_test.hpp"

Location::Location(
      PositioningSystemConfiguration *_configuration
      ) {
  configuration = _configuration;
  const uint8_t running_median_size = configuration->running_median_size();
  frequency_1_offset_medians = new RunningMedian(running_median_size);
  frequency_2_offset_medians = new RunningMedian(running_median_size);
  frequency_3_offset_medians = new RunningMedian(running_median_size);
  
  valid = frequency_1_offset_medians && frequency_1_offset_medians->is_valid() &&
          frequency_2_offset_medians && frequency_2_offset_medians->is_valid() &&
          frequency_3_offset_medians && frequency_3_offset_medians->is_valid();
  
  const short samples_in_buffer = configuration->number_of_samples_in_convolution_buffer();
  const uint8_t sample_bits = configuration->bits_used_by_samples();
  frequency_1_convolver = new Convolver(
        configuration->wave_length_in_samples_for_frequency_1(), 
        samples_in_buffer, sample_bits);
  frequency_2_convolver = new Convolver(
        configuration->wave_length_in_samples_for_frequency_2(), 
        samples_in_buffer, sample_bits);
  frequency_3_convolver = new Convolver(
        configuration->wave_length_in_samples_for_frequency_3(), 
        samples_in_buffer, sample_bits);
       
  valid = frequency_1_convolver && frequency_1_convolver->is_valid() && 
          frequency_2_convolver && frequency_2_convolver->is_valid() && 
          frequency_3_convolver && frequency_3_convolver->is_valid() && valid;

  average_sample = new ExponentialAverage(
        configuration->exponential_average_decay(),
        configuration->expected_average_sample());
  normalized_samples = new SampleBuffer(samples_in_buffer);
  valid = normalized_samples && normalized_samples->is_valid() &&
          average_sample && valid;
  
  peak_detection = new PeakDetectionInAWindow(
        configuration->samples_between_signal_beginnings(),
         samples_in_buffer,
         configuration->maximum_change_of_following_signal_in_number_of_samples());
  
  location.x = NAN;
  location.y = NAN;
}

Location::~Location() {
  delete frequency_1_offset_medians;
  delete frequency_2_offset_medians;
  delete frequency_3_offset_medians;
  
  delete frequency_1_convolver;
  delete frequency_2_convolver;
  delete frequency_3_convolver;
  
  delete average_sample;
  delete normalized_samples;
  
  delete peak_detection;
  valid = false;
}

int index = -1;
long max_intensity1 = -1;
long max_intensity2 = -1;
long max_intensity3 = -1;

void Location::add_sample(Sample new_sample) {
  if (!valid) {
    return;
  }
  ++index;
  //average_sample->add_sample(new_sample);
  //println2("new_sample: ", new_sample);
  Sample normalized_new_sample = average_sample->normalize(new_sample);
  //println2("normalized_new_sample: ", normalized_new_sample);
  Sample normalized_old_sample = normalized_samples->replaced_by(normalized_new_sample);
  //println2("normalized_old_sample: ", normalized_old_sample);
  frequency_1_convolver->replace_sample(normalized_old_sample, normalized_new_sample);
  frequency_2_convolver->replace_sample(normalized_old_sample, normalized_new_sample);
  frequency_3_convolver->replace_sample(normalized_old_sample, normalized_new_sample);
  Intensity intensity_1 = frequency_1_convolver->squared_intensity();
  Intensity intensity_2 = frequency_2_convolver->squared_intensity();
  Intensity intensity_3 = frequency_3_convolver->squared_intensity();
//  if (max_intensity1 < intensity_1) max_intensity1 = intensity_1; else if (max_intensity1 == intensity_1) println2("max1 at: ", index);
//  if (max_intensity2 < intensity_2) max_intensity2 = intensity_2; else if (max_intensity2 == intensity_2) println2("max2 at: ", index);
//  if (max_intensity3 < intensity_3) max_intensity3 = intensity_3; else if (max_intensity3 == intensity_3) println2("max3 at: ", index);
  peak_detection->add_intensities(intensity_1, intensity_2, intensity_3);
  if (peak_detection->reached_end_of_window()) {
    double offset1 = peak_detection->offset_of_base_frequency();
    double offset2 = peak_detection->offset_of_second_frequency();
    double offset3 = peak_detection->offset_of_third_frequency();
    pvar(offset1);
    pvar(offset2);
    pvar(offset3);
    frequency_1_offset_medians->add(offset1);
    frequency_2_offset_medians->add(offset2);
    frequency_3_offset_medians->add(offset3);
    peak_detection->reset_window();
  }
}



void Location::compute_new_coordinates() {
  if (!valid) {
    return;
  }
  
  double offset_1 = frequency_1_offset_medians->getMedian();
  double offset_2 = frequency_2_offset_medians->getMedian();
  double offset_3 = frequency_3_offset_medians->getMedian();
  pvar(offset_1);
  pvar(offset_2);
  pvar(offset_3);
  if (isnan(offset_1) || isnan(offset_2) || isnan(offset_3)) {
    location.x = NAN;
    location.y = NAN;
  } else {
    Seconds time_difference_1;
    Seconds time_difference_2;
    compute_time_difference(
          offset_1, offset_2, offset_3, 
          configuration->sampling_frequency_in_hertz, 
          &time_difference_1, &time_difference_2);
    const Meters BP_minus_CP = configuration->speed_of_sound_in_meters_per_second * time_difference_1;
    const Meters BP_minus_AP = configuration->speed_of_sound_in_meters_per_second * time_difference_2;
    location = position(
          BP_minus_CP, BP_minus_AP, 
          configuration->A(), 
          configuration->B(), 
          configuration->C());
  }
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
    
