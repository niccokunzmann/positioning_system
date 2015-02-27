

#ifndef convolution_hpp
#define convolution_hpp

#include "Arduino.h"
#include "units.hpp"

class WaveState {
  public:
    WaveState(
          long squared_intensity = 0, 
          long sum_sinus = 1, 
          long sum_cosinus = 0, 
          short wave_length_in_samples = 1,
          short convolutional_offset = 0
          );
    
    double phase_in_samples();
    double phase_between_samples();
    double expected_closest_end_of_wave();
    
    long squared_intensity;
    long sum_sinus;
    long sum_cosinus;
    short wave_length_in_samples;
    short convolutional_offset;
};


class Convolver {
  /** Convolution with a frequency
   *
   * Samples should use 10 bit. (samples range from -511 to +511 or from 0 to 1023 for example)
   * If they use more bits than `sample_bits`, then an overflow error in squared_intensity() may occur.
   * sample_bits can be changed if more or less bits are required.
   */
  public:
    Convolver(short wave_length_in_samples = 0, short number_of_samples_in_buffer = 0, int8_t sample_bits = 10);
    ~Convolver();

    boolean is_valid();

    void add_sample   (Sample sample);
    void remove_sample(Sample sample);
    void replace_sample(Sample sample, Sample with_new_sample);
    
    long squared_intensity();
    
    WaveState wave_state();
    
  private:
    void allocate_memory_for_wave();
    void fill_wave();
    void compute_overflow_prevention(int8_t sample_bits);
    
    // 2 bytes
    short wave_length_in_samples;
    short add_sample_index;
    short remove_sample_index;
    short number_of_samples_in_buffer;

    // 1 byte
    boolean valid;
    // 32 bit long = 31 bit value = (8 bit wave + 10 bit sample + bits(number_of_samples_in_buffer) - overflow_preventing_intensity_divisor_bits) * 2
    int8_t overflow_preventing_intensity_divisor_bits;

    // 2 or more bytes
    // int8_t http://forum.arduino.cc/index.php?topic=72887.0
    int8_t *sinus_values;
    int8_t *cosinus_values;
    
    // four bytes
    long sum_sinus;
    long sum_cosinus;

    
};

#endif