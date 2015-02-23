
#ifndef samples_hpp
#define samples_hpp

#include "Arduino.h"
#include "units.hpp"

class SampleBuffer {
  public:
    SampleBuffer(short number_of_normalized_samples);
    ~SampleBuffer();
    
    Sample replaced_by(Sample new_sample);
    long sum();
    Sample average();
    
    Sample normalize(Sample sample);
    
    boolean is_valid();
    
    short size();
    
  private:
    short number_of_samples;
    short current_sample_index;
    Sample *samples;
    boolean valid;
  
};

#endif