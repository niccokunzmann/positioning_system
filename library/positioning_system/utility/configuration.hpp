
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
    int use_interrupt_number = 2;
        
    // for speakers
    int speaker_1_output_pin = 8;
    int speaker_2_output_pin = 9;
    int speaker_3_output_pin = 10;
}

#endif