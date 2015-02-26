
#ifndef configuration_hpp
#define configuration_hpp

#include "Arduino.h"
#include "units.hpp"

// https://en.wikipedia.org/wiki/Speed_of_sound
#define SPEED_OF_SOUND_IN_DRY_AIR_AT_20_DEGREES_TEMPERATURE 343.2/*meters per second*/

short GCD(short a, short b);
long LCM(long a, long b);

class PositioningSystemConfiguration {
  public:
    PositioningSystemConfiguration(
          // for both
          double distance_between_speaker_1_and_speaker_2_in_meters = 0.6,
          double distance_between_speaker_2_and_speaker_3_in_meters = 0.8,
          double distance_between_speaker_3_and_speaker_1_in_meters = 1.0,
          int frequency_1_in_hertz = 2000, 
          int frequency_2_in_hertz = 1600, 
          int frequency_3_in_hertz = 1333,
          int length_of_a_tone_in_milliseconds = 30,
          double speed_of_sound_in_meters_per_second = SPEED_OF_SOUND_IN_DRY_AIR_AT_20_DEGREES_TEMPERATURE,
          // for location
          int microphone_input_pin = A0,
          int sampling_frequency_in_hertz = 8000,
          double time_to_listen_to_signals_for_location_in_seconds = 1,
          int minimum_sample_value = 0,
          int maximum_sample_value = 1023,
          double maximum_speed_of_robot_in_meters_per_second = 0.2,
          // for speakers
          int speaker_1_output_pin = 8,
          int speaker_2_output_pin = 9,
          int speaker_3_output_pin = 10);
          
          
    // for both
    /* Speaker 1 to speaker 2 is the x axis
     * Speaker 1 is at (0, 0)
     * Speaker 3 is at (x, y) | y > 0
     */
    double distance_between_speaker_1_and_speaker_2_in_meters;
    double distance_between_speaker_2_and_speaker_3_in_meters;
    double distance_between_speaker_3_and_speaker_1_in_meters;

    int frequency_1_in_hertz;
    int frequency_2_in_hertz;
    int frequency_3_in_hertz;
    
    int length_of_a_tone_in_milliseconds;

    double speed_of_sound_in_meters_per_second;
    
    // for location
    int microphone_input_pin;
    int sampling_frequency_in_hertz; // in samples / second
    double time_to_listen_to_signals_for_location_in_seconds;
    int minimum_sample_value;
    int maximum_sample_value;
    double maximum_speed_of_robot_in_meters_per_second;
  
    // for speakers
    int speaker_1_output_pin;
    int speaker_2_output_pin;
    int speaker_3_output_pin;
    
    // functions for all
    const boolean is_valid();
    
    // functions for location
    const uint8_t running_median_size();
    const NumberOfSamples wave_length_in_samples_for_frequency_1();
    const NumberOfSamples wave_length_in_samples_for_frequency_2();
    const NumberOfSamples wave_length_in_samples_for_frequency_3();
    const NumberOfSamples number_of_samples_in_convolution_buffer();
    const int8_t bits_used_by_samples();
    const NumberOfSamples samples_between_signal_beginnings();
    const NumberOfSamples minimum_samples_between_signal_beginnings();
    const NumberOfSamples length_of_a_tone_in_samples();
    const NumberOfSamples maximum_change_of_following_signal_in_number_of_samples();
    const SpeakerPosition A(); // frequency 3
    const SpeakerPosition B(); // base frequency 1
    const SpeakerPosition C(); // frequency 2
    
    // functions for speakers
    const int speaker_1_frequency_in_hertz();
    const int speaker_2_frequency_in_hertz();
    const int speaker_3_frequency_in_hertz();
    
    const NumberOfSamples frequency_to_samples(int frequency);
};

extern PositioningSystemConfiguration default_configuration;


#endif