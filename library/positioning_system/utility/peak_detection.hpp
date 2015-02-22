
#ifndef peak_detection_hpp
#define peak_detection_hpp

#include "Arduino.h"
#include "convolution.hpp"

typedef short NumberOfSamples;
typedef double SignalPosition;

class PeakDetectionInAWindow {
  public:
    PeakDetectionInAWindow(NumberOfSamples samples_between_signal_beginnings,
                           NumberOfSamples number_of_samples_of_the_base_signal,
                           NumberOfSamples maximum_change_of_the_base_signal_position_between_windows);
    ~PeakDetectionInAWindow();
    
    void add_intensities(Intensity of_base_frequency, 
                         Intensity of_second_frequency,
                         Intensity of_third_frequency);
    
    boolean has_offsets();
    
    /* shall only be called when has_offsets() is true */
    SignalPosition offset_of_base_frequency(); 
    SignalPosition offset_of_second_frequency(); 
    SignalPosition offset_of_third_frequency(); 
    
    void reset_window();
  
  private:
    NumberOfSamples offset1;
    NumberOfSamples offset2;
    NumberOfSamples offset3;
    
    Intensity maximum_intensity1;
    Intensity maximum_intensity2;
    Intensity maximum_intensity3;
    
    NumberOfSamples next_offset_in_window;
    NumberOfSamples window_size;
    NumberOfSamples f1_offset;
}





#endif