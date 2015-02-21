

#ifndef convolution_hpp
#define convolution_hpp

#include "Arduino.h"
#include "samples.hpp"

class Convolver {
  public:
    // remove_samples_delayed_by_buffer == number_of_normalized_samples
    Convolver(short wave_length_in_samples, short remove_samples_delayed_by_buffer);
    ~Convolver();

    boolean is_valid();

    void add_sample   (Sample sample);
    void remove_sample(Sample sample);
    
    unsigned long current_squared_intensity();
    
  private:
    void allocate_memory_for_wave();
    void fill_wave();
    
    // 2 bytes
    short wave_length_in_samples;
    short add_sample_index;
    short remove_sample_index;

    // 1 byte
    boolean valid;

    // 2 or more bytes
    Sample *samples;
    byte   *sinus_values;
    byte   *cosinus_values;
    
    // four bytes
    long sum_sinus;
    long sum_cosinus;

    
};

#endif