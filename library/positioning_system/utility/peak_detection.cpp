
#include "peak_detection.hpp"

PeakDetectionInAWindow::PeakDetectionInAWindow(
      NumberOfSamples distance_between_peaks,
      NumberOfSamples maximum_latency,
      NumberOfSamples offset_to_avoid_base_frequency_peak_duplication) {
  window_size = distance_between_peaks + maximum_latency;
  f1_offset = offset_to_avoid_base_frequency_peak_duplication;
  offset1 = 0;
  next_offset_in_window = 0;
  reset_window();
}
      
PeakDetectionInAWindow::~PeakDetectionInAWindow() {
  
}

PeakDetectionInAWindow::reset_window() {
  next_offset_in_window -= offset1;
  maximum_intensity1 = 0;
  maximum_intensity2 = 0;
  maximum_intensity3 = 0;
  offset1 = next_offset_in_window;
  offset2 = next_offset_in_window;
  offset3 = next_offset_in_window;
}
    
void PeakDetectionInAWindow::add_intensities(
      Intensity intensity1, 
      Intensity intensity2,
      Intensity intensity3) {
  if ((intensity1 > maximum_intensity1) && 
      (next_offset_in_window > f1_offset)) {
    maximum_intensity1 = intensity1;
    offset1 = next_offset_in_window;
  }
  if (intensity2 > maximum_intensity2) {
    maximum_intensity2 = intensity2;
    offset2 = next_offset_in_window;
  }
  if (intensity3 > maximum_intensity3) {
    maximum_intensity3 = intensity3;
    offset3 = next_offset_in_window;
  }
  next_offset_in_window++;
}



boolean PeakDetectionInAWindow::has_offsets() {
  return current_offset_in_window >= window_size;
}

SignalPosition offset_of_base_frequency() {
  return offset1;
}
SignalPosition offset_of_second_frequency() {
  return offset2;
}
SignalPosition offset_of_third_frequency() {
  return offset3;
}