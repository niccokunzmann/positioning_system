
#ifndef samples_hpp
#define samples_hpp

#include "Arduino.h"

typedef unsigned short Sample;
typedef short NormalizedSample;

class SampleBuffer {
  public:
    SampleBuffer(short number_of_normalized_samples);
    ~SampleBuffer();
    
    NormalizedSample replaced_by(NormalizedSample new_sample);
    long sum();
    NormalizedSample average();
    
    NormalizedSample normalize(Sample sample);
    
    boolean is_valid();
    
  private:
    short number_of_samples;
    short current_sample_index;
    long sum_of_all_samples;
    Sample *samples;
    boolean valid;
  
}

#endif