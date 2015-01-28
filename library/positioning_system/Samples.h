#ifndef wave_detection_h
#define wave_detection_h

#include "Arduino.h"


class Samples
{
  public:
    Samples(int number_of_samples);
  
    void  print_to_serial();
    void  print_to_Serial();
    
    int   get_average_sample();
    int*  get_samples();
    int   get_number_of_samples();
    
    void  add_sample(int sample);
    
  private:
  
}

#endif