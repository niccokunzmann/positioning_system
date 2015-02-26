
#include "test_location.hpp"
#include "math.h"

double position_to_offset(          
          double x, double y, 
          SpeakerPosition P,
          PositioningSystemConfiguration *configuration) {
  double dx = P.x - x;
  double dy = P.y - y;
  double distance = sqrt(dx * dx + dy * dy);
  Time sound_difference = distance / configuration->speed_of_sound_in_meters_per_second;
  return sound_difference * configuration->sampling_frequency_in_hertz;
}

void add_samples_for_position(
          double x, double y, Location *location, 
          PositioningSystemConfiguration *configuration
          ) {
  int do_samples_again = configuration->samples_between_signal_beginnings();
  int length_of_tone = configuration->length_of_a_tone_in_samples();
  int samples_to_generate = 
        configuration->running_median_size() * do_samples_again + 
        configuration->samples_in_convolution_buffer();
  int number_of_samples[3] = {
        wave_length_in_samples_for_frequency_1();
        wave_length_in_samples_for_frequency_2();
        wave_length_in_samples_for_frequency_3();
        };
  double frequency_start_index[3] = {
        position_to_offset(x, y, configuration->B(), configuration), 
        position_to_offset(x, y, configuration->C(), configuration) + samples_between_signal_beginnings() / 3,
        position_to_offset(x, y, configuration->A(), configuration) + samples_between_signal_beginnings() * 2 / 3,
        };
  for (int sample_index = 0; sample_index < samples_to_generate; ++sample_index) {
    sample = 0; // add noise here
    for (int frequency_number = 0; frequency_number < 3; ++frequency_number) {
      double start = frequency_start_index[frequency_number];
      if (start < sample_index) {
        // started frequency
        double end = start + do_samples_again;
        if (end < sample_index) {
          // reached end
          frequency_start_index[frequency_number] += do_samples_again;
        } else {
          // within tone
          sample += 255 * sin((sample_index - start) / number_of_samples[frequency_number] * 2 * M_PI);
        }
      }
    }
    location.add_sample(sample);
  }
}