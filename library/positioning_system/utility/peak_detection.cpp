
#include "peak_detection.hpp"
#include "positioning_system_test.h"

PeakDetectionInAWindow::PeakDetectionInAWindow(
      NumberOfSamples distance_between_peaks,
      NumberOfSamples offset_to_avoid_base_frequency_peak_duplication,
      NumberOfSamples maximum_latency) {
  window_size = distance_between_peaks + maximum_latency;
  f1_offset = offset_to_avoid_base_frequency_peak_duplication - 1;
  offset1 = 0;
  next_offset_in_window = 1;
  reset_window();
}
      
PeakDetectionInAWindow::~PeakDetectionInAWindow() {
  
}

void PeakDetectionInAWindow::reset_window() {
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
  println8("intensities: ", intensity1, " ", intensity2, " ", intensity3, " offset: ", next_offset_in_window);
  if ((intensity1 >= maximum_intensity1) && 
      (next_offset_in_window > f1_offset)) {
    maximum_intensity1 = intensity1;
    offset1 = next_offset_in_window;
  }
  if (intensity2 >= maximum_intensity2) {
    maximum_intensity2 = intensity2;
    offset2 = next_offset_in_window;
  }
  if (intensity3 >= maximum_intensity3) {
    maximum_intensity3 = intensity3;
    offset3 = next_offset_in_window;
  }
  next_offset_in_window++;
}



boolean PeakDetectionInAWindow::reached_end_of_window() {
  return next_offset_in_window > window_size;
}

SignalPosition PeakDetectionInAWindow::offset_of_base_frequency() {
  return offset1;
}
SignalPosition PeakDetectionInAWindow::offset_of_second_frequency() {
  return offset2;
}
SignalPosition PeakDetectionInAWindow::offset_of_third_frequency() {
  return offset3;
}