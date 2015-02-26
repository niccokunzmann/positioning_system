
#include "test_location_functions.hpp"
#include "test_print.hpp"
#include "assertions.hpp"
#include "math.h"

double position_to_offset(          
          double x, double y, 
          SpeakerPosition P,
          PositioningSystemConfiguration *configuration) {
  double distance = hypot(P.x - x, P.y - y);
  Time sound_difference = distance / configuration->speed_of_sound_in_meters_per_second;
  return sound_difference * configuration->sampling_frequency_in_hertz;
}

void add_samples_for_position(
          double x, double y, Location *location, 
          PositioningSystemConfiguration *configuration
          ) {
  int do_samples_again = configuration->samples_between_signal_beginnings();
  pvar(do_samples_again);
  int length_of_tone = configuration->length_of_a_tone_in_samples();
  pvar(length_of_tone);
  int samples_to_generate = 
        6 * do_samples_again + 
        configuration->number_of_samples_in_convolution_buffer();
  int number_of_samples[3];
  number_of_samples[0] = configuration->wave_length_in_samples_for_frequency_1();
  number_of_samples[1] = configuration->wave_length_in_samples_for_frequency_2();
  number_of_samples[2] = configuration->wave_length_in_samples_for_frequency_3();
  pvar(number_of_samples[0]);
  pvar(number_of_samples[1]);
  pvar(number_of_samples[2]);
  double frequency_start_index[3];
  frequency_start_index[0] = position_to_offset(x, y, configuration->B(), configuration);
  frequency_start_index[1] = position_to_offset(x, y, configuration->C(), configuration) + 
                             do_samples_again / 3.;
  frequency_start_index[2] = position_to_offset(x, y, configuration->A(), configuration) + 
                             do_samples_again * 2. / 3;
  pvar(frequency_start_index[0]);
  pvar(frequency_start_index[1]);
  pvar(frequency_start_index[2]);
  for (int sample_index = 0; sample_index < samples_to_generate; ++sample_index) {
    double sample = configuration->expected_average_sample(); // add noise here
    for (int frequency_number = 0; frequency_number < 3; ++frequency_number) {
      double start = frequency_start_index[frequency_number];
      if (start > sample_index) {
        // before tone
      } else if (start + length_of_tone < sample_index) {
        //println2("end: ", frequency_number);
        // after tone
        frequency_start_index[frequency_number] += do_samples_again;
      } else {
        // within tone
        if (start > sample_index - 1) {
          //println2("start: ", frequency_number);
        }
        sample += 255 * sin((sample_index - start) / number_of_samples[frequency_number] * 2 * M_PI);
      }
    }
    location->add_sample(round(sample));
  }
}

void assertLocates(double x, double y) {
  Location location = Location(&default_configuration);
  assertTrue(location.is_valid());
  add_samples_for_position(x, y, &location, &default_configuration);
  location.compute_new_coordinates();
  pvar(location.y());
  pvar(location.x());
  assertApproximately(location.y(), y);
  assertApproximately(location.x(), x);
}