
#include "math.h"
#include "positioning_system.h"
#include "assertions.hpp"
#include "test_convolution_functions.hpp"

void assertConvolutes(int wave_length_in_samples, double given_phase_in_samples, short buffer_size) {
  SampleBuffer sample_buffer = SampleBuffer(buffer_size);
  assertTrue(sample_buffer.is_valid());
  int samples = wave_length_in_samples * 10 + buffer_size * 2;
  Convolver convolver = Convolver(wave_length_in_samples, buffer_size);
  given_phase_in_samples = fmod(given_phase_in_samples + wave_length_in_samples / 2., wave_length_in_samples) - wave_length_in_samples / 2.;
  for (int i = 0; i < samples; ++i) {
    short with_new_sample = round(511 * sin(2 * M_PI * (i - given_phase_in_samples) / wave_length_in_samples));
    short old_sample = sample_buffer.replaced_by(with_new_sample);
    convolver.replace_sample(old_sample, with_new_sample);
    if (i > samples - wave_length_in_samples * 2) {
      double closest_wave_end = i + wave_length_in_samples / 4. - given_phase_in_samples + buffer_size;
      closest_wave_end = wave_length_in_samples / 4. - fmod(closest_wave_end, wave_length_in_samples / 2.);
      WaveState wave_state = convolver.wave_state();
      //pvar(i);
      double wave_state_phase_in_samples = fmod(wave_state.phase_in_samples() + wave_length_in_samples / 2., wave_length_in_samples) - wave_length_in_samples / 2.;
      if (wave_state_phase_in_samples < -wave_length_in_samples / 2.) {
        wave_state_phase_in_samples += wave_length_in_samples;
      }
      //pvar(given_phase_in_samples);
      //pvar(wave_state.phase_in_samples());
      //pvar(closest_wave_end);
      //pvar(wave_state.expected_closest_end_of_wave());
      assertAboutTheSame(wave_state_phase_in_samples, given_phase_in_samples);
      assertAboutTheSame(wave_state.expected_closest_end_of_wave(), closest_wave_end);
    }
  }
}

