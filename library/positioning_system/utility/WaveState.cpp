
#include "convolution.hpp"
// http://www.nongnu.org/avr-libc/user-manual/group__avr__math.html
#include "math.h"

WaveState::WaveState(long squared_intensity, long sum_sinus, long sum_cosinus, short wave_length_in_samples) : 
  squared_intensity(squared_intensity), sum_sinus(sum_sinus), sum_cosinus(sum_cosinus), wave_length_in_samples(wave_length_in_samples) {
}

WaveState::WaveState() : 
  squared_intensity(0), sum_sinus(1), sum_cosinus(0), wave_length_in_samples(0) {
}
    
double WaveState::phase_between_samples() {
  double phase_in_radian = atan2(sum_sinus, sum_cosinus);
  double phase_in_samples = phase_in_radian / M_PI / 2 * wave_length_in_samples;
  return fmod(-phase_in_samples + 0.5 + wave_length_in_samples / 4., 1) - 0.5;
}