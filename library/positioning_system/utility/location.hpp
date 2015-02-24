
#ifndef location_hpp
#define location_hpp

#include "Arduino.h"
#include "configuration.hpp"
#include "RunningMedian.h"
#include "convolution.hpp"
#include "units.hpp"
#include "position.hpp"
#include "unit_conversion.hpp"

class Location {
  public:
    Location(PositioningSystemConfiguration configuration);
    ~Location();
    
    void compute_new_coordinates();
    double x();
    double y();
    
    boolean is_valid();

    void add_sample(Sample sample);
    
  private: 
    PositioningSystemConfiguration configuration;
    
    RunningMedian frequency_1_offset_medians;
    RunningMedian frequency_2_offset_medians;
    RunningMedian frequency_3_offset_medians;
    
    Convolver frequency_1_convolver; 
    Convolver frequency_2_convolver; 
    Convolver frequency_3_convolver;
    
    SampleBuffer sample_buffer;
    PeakDetectionInAWindow peak_detection;
    
    MicrophonePosition location;
    
    boolean valid;
};



#endif