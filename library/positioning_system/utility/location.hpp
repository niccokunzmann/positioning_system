
#ifndef location_hpp
#define location_hpp

#include "Arduino.h"
#include "units.hpp"

// forward declaration
// http://stackoverflow.com/questions/9119236/c-class-forward-declaration
class PositioningSystemConfiguration;
class RunningMedian;
class Convolver;
class SampleBuffer;
class ExponentialAverage;
class PeakDetectionInAWindow;


class Location {
  public:
    Location(PositioningSystemConfiguration *configuration);
    ~Location();
    
    void compute_new_coordinates();
    double x();
    double y();
    
    boolean is_valid();

    void add_sample(Sample sample);
    
  private: 
    PositioningSystemConfiguration *configuration;
    
    RunningMedian *frequency_1_offset_medians;
    RunningMedian *frequency_2_offset_medians;
    RunningMedian *frequency_3_offset_medians;
    
    Convolver *frequency_1_convolver; 
    Convolver *frequency_2_convolver; 
    Convolver *frequency_3_convolver;
    
    ExponentialAverage *average_sample;
    SampleBuffer *normalized_samples;
    PeakDetectionInAWindow *peak_detection;
    
    MicrophonePosition location;
    
    boolean valid;
};


#endif