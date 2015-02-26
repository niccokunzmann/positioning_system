
#ifndef peak_detection_hpp
#define peak_detection_hpp

#include "Arduino.h"
#include "convolution.hpp"

#include "units.hpp"

class PeakDetectionInAWindow {
  public:
    PeakDetectionInAWindow(NumberOfSamples samples_between_signal_beginnings,
                           NumberOfSamples number_of_samples_of_the_base_signal,
                           NumberOfSamples maximum_change_of_the_base_signal_position_between_windows);
    ~PeakDetectionInAWindow();
    
    void add_intensities(Intensity of_base_frequency, 
                         Intensity of_second_frequency,
                         Intensity of_third_frequency);

    void add_wave_state(WaveState of_base_frequency, 
                        WaveState of_second_frequency,
                        WaveState of_third_frequency);
                         
    boolean reached_end_of_window();
    
    /* shall only be called when reached_end_of_window() is true */
    SignalPosition offset_of_base_frequency(); 
    SignalPosition offset_of_second_frequency(); 
    SignalPosition offset_of_third_frequency(); 
    
    /* when reached_end_of_window() is true you should call reset_window()
     * to begin an new window.
     */
    void reset_window();
  
  private:
    NumberOfSamples offset1;
    NumberOfSamples offset2;
    NumberOfSamples offset3;
    
    WaveState maximum1;
    WaveState maximum2;
    WaveState maximum3;
    
    NumberOfSamples next_offset_in_window;
    NumberOfSamples window_size;
    NumberOfSamples f1_offset;
};





#endif