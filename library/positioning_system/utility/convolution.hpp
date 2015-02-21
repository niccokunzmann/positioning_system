

#ifndef convolution_hpp
#define convolution_hpp

#include "Arduino.h"
#include "samples.hpp"

class Convolver {
  /** Convolution with a frequency
   *
   * samples should range from -511 to +511 (10 bit)
   * otherwise overflow errors in squared_intensity() may occur.
   * sample_bits represents this assumption and can be changed
   * when the assumption changes.
   */
  public:
    Convolver(short wave_length_in_samples, short number_of_samples_in_buffer, byte sample_bits = 10);
    ~Convolver();

    boolean is_valid();

    void add_sample   (Sample sample /* -511 <= sample <= +511 */);
    void remove_sample(Sample sample /* -511 <= sample <= +511 */);
    
    long squared_intensity();
    
  private:
    void allocate_memory_for_wave();
    void fill_wave();
    void compute_overflow_prevention(short number_of_samples_in_buffer, byte sample_bits);
    
    // 2 bytes
    short wave_length_in_samples;
    short add_sample_index;
    short remove_sample_index;

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