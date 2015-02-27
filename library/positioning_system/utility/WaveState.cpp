
#include "convolution.hpp"
// http://www.nongnu.org/avr-libc/user-manual/group__avr__math.html
#include "math.h"
#include "positioning_system_test.h"

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
  double phase = fmod(phase_in_samples() + 0.5, 1) - 0.5;
  if (phase < - 0.5) {
    phase += 1;
  } else   if (phase > 0.5) {
    phase -= 1;
  }
  return phase;
}

double WaveState::phase_in_samples() {
  double phase_in_radian = atan2(-sum_cosinus, sum_sinus);
  double phase_in_samples = phase_in_radian / M_PI / 2 * wave_length_in_samples;
  return phase_in_samples;
}

double WaveState::expected_closest_end_of_wave() {
  // fmod can potentially yield negative results
  pvar(wave_length_in_samples);
  pvar(phase_in_samples());
  pvar(convolutional_offset);
  double closest_wave = convolutional_offset + wave_length_in_samples / 4. - phase_in_samples() + wave_length_in_samples;
  //pvar(closest_wave);
  closest_wave = wave_length_in_samples / 4. - fmod(closest_wave, wave_length_in_samples / 2.);
  /*if (closest_wave < - wave_length_in_samples / 2.) {
    closest_wave += wave_length_in_samples;
  } else   if (closest_wave > wave_length_in_samples / 2.) {
    closest_wave -= wave_length_in_samples;
  }*/
  return closest_wave;
}
