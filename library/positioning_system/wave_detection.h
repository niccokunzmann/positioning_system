
#ifndef wave_detection_h
#define wave_detection_h

#include "Arduino.h"

class WaveDetector
{
  public:
    WaveDetector(int pin);
    int get_frequency();
    long get_volume_squared();
    print_samples();
    
  private:
    setup_volume_recognition(int microphone_pin);
    setup_check_values();
    
    int microphone_pin;
    const int sample_frequency       = 8000; //Hz max 8000Hz
    const int samples_per_wave_cycle = 20;   // determines the frequency
    const int number_of_samples      = 300;  // number samples used to determine the volume

      // see compute_squared_volume()
      // 8 bit sinus_wave
      // 10 bit analogRead
      // 9 bit number_of_samples
      // == 27 bit sum_sinus
      // => shift by 12 bit to get 15 bit sum_sinus
      // => 30 bit sum_sinus squared
      // => 31 bit sum_sinus squared + sum_cosinus squared
      // so we should divide by 2048
      // but if we take 512 it may still be ok
      // if the frequency is between 0 and 1024 then this value prevents overflow errors.
      // if you get negative values you should turn it higher up to 2048 
      // where no overflow can occur
    const long overflow_preventing_volume_divisor = 512; // <= 2048

    int samples[number_of_samples];

    long sum_sinus = 0;
    long sum_cosinus = 0;

    int sinus_wave[samples_per_wave_cycle];
    int cosinus_wave[samples_per_wave_cycle];

    int average_sample = -1;    
    int sample_index = 0;
    volatile boolean recording_samples = false;
};

#endif