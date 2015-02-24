
#ifndef configuration_hpp
#define configuration_hpp

#define SPEED_OF_SOUND_IN_DRY_AIR_AT_20_DEGREES_TEMPERATURE 343.2


class PositioningSystemConfiguration {
  public:
    // for both
    int frequency_1_in_hertz = 2000;
    int frequency_2_in_hertz = 1800;
    int frequency_3_in_hertz = 1600;
    
    int length_of_a_tone_in_milliseconds = 30;
    
    double distance_between_speaker_1_and_speaker_2_in_meters = 0.6;
    double distance_between_speaker_2_and_speaker_3_in_meters = 0.8;
    double distance_between_speaker_3_and_speaker_1_in_meters = 1.0;

    double speed_of_sound_in_meters_per_second = SPEED_OF_SOUND_IN_DRY_AIR_AT_20_DEGREES_TEMPERATURE;
    
    // for Location
    int microphone_input_pin = A0;
    int sampling_frequency_in_hertz = 8000;
    double time_to_listen_to_signals_for_location_in_seconds = 1;
    int minimum_sample_value = 0;
    int maximum_sample_value = 1023;
  
    // for speakers
    int speaker_1_output_pin = 8;
    int speaker_2_output_pin = 9;
    int speaker_3_output_pin = 10;
    
    // functions
    const uint8_t running_median_size();
    const short wave_length_in_samples_for_frequency_1();
    const short wave_length_in_samples_for_frequency_2();
    const short wave_length_in_samples_for_frequency_3();
    const short number_of_samples_in_convolution_buffer();
    const int8_t bits_used_by_samples();
    const NumberOfSamples samples_between_signal_beginnings();
    const NumberOfSamples maximum_change_of_following_signal_in_number_of_samples();
}

#endif