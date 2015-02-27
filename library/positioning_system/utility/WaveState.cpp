
#include "convolution.hpp"
// http://www.nongnu.org/avr-libc/user-manual/group__avr__math.html
#include "math.h"

WaveState::WaveState(
      long squared_intensity, 
      long sum_sinus, 
      long sum_cosinus, 
      short wave_length_in_samples,
      short convolutional_offset
      ) : 
          squared_intensity(squared_intensity), 
          sum_sinus(sum_sinus), 
          sum_cosinus(sum_cosinus), 
          wave_length_in_samples(wave_length_in_samples),
          convolutional_offset(convolutional_offset) {
}
    
double WaveState::phase_between_samples() {
  return fmod(phase_in_samples() + 0.5, 1) - 0.5;
}

double WaveState::phase_in_samples() {
  double phase_in_radian = atan2(sum_sinus, sum_cosinus);
  double phase_in_samples = phase_in_radian / M_PI / 2 * wave_length_in_samples;
  phase_in_samples -= wave_length_in_samples / 4.;
  return phase_in_samples;
}

double WaveState::expected_closest_end_of_wave() {
  // fmod can potentially yield negative results
  double closest_wave = convolutional_offset + wave_length_in_samples / 4. - phase_in_samples() + wave_length_in_samples;
  return wave_length_in_samples / 4. - fmod(closest_wave, wave_length_in_samples / 2.);
}
