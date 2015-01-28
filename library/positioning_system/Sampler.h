
#ifndef wave_detection_h
#define wave_detection_h

#include "Arduino.h"
#include "Samples.h"

// singleton from http://stackoverflow.com/questions/1008019/c-singleton-design-pattern
class Sampler
{
  public:
    static Sampler& getInstance();

    int timer_number();
    int sampling_frequency_in_Hz();

    void record_into(Samples samples);
    boolean is_recording();
    boolean is_recording_into(Samples samples);
    void wait_until_recorded();
    void wait_until_recorded_into(Samples samples);
    

    
    
  private:
    Sampler();  // Constructor? (the {} brackets) are needed here.
    
    // Dont forget to declare these two. You want to make sure they
    // are unaccessable otherwise you may accidently get copies of
    // your singleton appearing.
    Sampler(Sampler const&);        // Don't Implement
    void operator=(Sampler const&); // Don't implement
    
    // sampling
    
    void setup_timer2_frequency();
    // http://arduino.cc/en/Reference/AnalogRead
    // It takes about 100 microseconds (0.0001 s) to read an analog input, so the maximum reading rate is about 10,000 times a second. 
    //   5 * 5 * 5 * 5 * 2 * 5 = 6250    const int sample_frequency       = 8000; //Hz max 8000Hz
    const int sample_frequency       = 8000; //Hz max 8000Hz

    int microphone_pin;
    int samples[number_of_samples];
        
    int average_sample = -1;

    // for interrupt sampling
    int sample_index = 0;
    volatile boolean recording_samples = false;
        
    
    
    
};

#endif