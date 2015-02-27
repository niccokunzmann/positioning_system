
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
  start_window();
  offset_1_between_samples = 0;
}
      
PeakDetectionInAWindow::~PeakDetectionInAWindow() {
  
}

void PeakDetectionInAWindow::end_window() {
  offset_1_between_samples = next_offset_1_between_samples;
  next_offset_1_between_samples = maximum1.phase_between_samples();
}

void PeakDetectionInAWindow::start_window() {
  next_offset_in_window -= offset1;
  maximum1 = WaveState();
  maximum2 = WaveState();
  maximum3 = WaveState();
  offset1 = next_offset_in_window;
  offset2 = next_offset_in_window;
  offset3 = next_offset_in_window;
}

void PeakDetectionInAWindow::reset_window() {
  end_window();
  start_window();
}

void PeakDetectionInAWindow::add_intensities(
      Intensity intensity1, 
      Intensity intensity2,
      Intensity intensity3) {
  add_wave_states(
        WaveState(intensity1), 
        WaveState(intensity2), 
        WaveState(intensity3));
}

void PeakDetectionInAWindow::add_wave_states(
      WaveState wave_state_1, 
      WaveState wave_state_2,
      WaveState wave_state_3) {
  if ((wave_state_1.squared_intensity >= maximum1.squared_intensity) && 
      (next_offset_in_window > f1_offset)) {
    maximum1 = wave_state_1;
    offset1 = next_offset_in_window;
  }
  if (wave_state_2.squared_intensity >= maximum2.squared_intensity) {
    maximum2 = wave_state_2;
    offset2 = next_offset_in_window;
  }
  if (wave_state_3.squared_intensity >= maximum3.squared_intensity) {
    maximum3 = wave_state_3;
    offset3 = next_offset_in_window;
  }
  next_offset_in_window++;
}



boolean PeakDetectionInAWindow::reached_end_of_window() {
  return next_offset_in_window > window_size;
}

SignalPosition PeakDetectionInAWindow::offset_of_base_frequency() {
  pvar(maximum1.expected_closest_end_of_wave());
  //pvar(maximum1.phase_in_samples());
  //maximum1.expected_closest_end_of_wave();
  
  return offset1 + next_offset_1_between_samples - offset_1_between_samples;//+ maximum1.phase_between_samples();//+ maximum1.expected_closest_end_of_wave();
}
SignalPosition PeakDetectionInAWindow::offset_of_second_frequency() {
  pvar(maximum2.expected_closest_end_of_wave());
  //pvar(maximum2.phase_in_samples());
  //maximum2.expected_closest_end_of_wave();
  //pvar(maximum2.phase_between_samples());
  return offset2 + maximum2.phase_between_samples() - offset_1_between_samples;//+ maximum2.expected_closest_end_of_wave();
}
SignalPosition PeakDetectionInAWindow::offset_of_third_frequency() {
  pvar(maximum3.expected_closest_end_of_wave());
  //pvar(maximum3.phase_in_samples());
  //maximum3.expected_closest_end_of_wave();
  //pvar(maximum3.phase_between_samples());
  return offset3 + maximum3.phase_between_samples() - offset_1_between_samples;//+ maximum3.expected_closest_end_of_wave();
}