
#include "convolution.hpp"
// http://www.nongnu.org/avr-libc/user-manual/group__avr__math.html
#include "math.h"

Convolver::Convolver(short _wave_length_in_samples, short remove_samples_delayed_by_buffer) {
  wave_length_in_samples = _wave_length_in_samples;
  add_sample_index = remove_samples_delayed_by_buffer % wave_length_in_samples;
  remove_sample_index = 0;
  valid = true;
  sum_sinus = 0;
  sum_cosinus = 0;
  
  allocate_memory_for_wave();
  fill_wave();
}

void Convolver::allocate_memory_for_wave() {
  sinus_values =   (byte*)malloc(wave_length_in_samples * sizeof(byte));
  cosinus_values = (byte*)malloc(wave_length_in_samples * sizeof(byte));
  valid = cosinus_values && sinus_values;}

void Convolver::fill_wave() {
  if (valid) {
    double PI_2_N = M_PI * 2.0 / wave_length_in_samples;
    for (int i = 0; i < wave_length_in_samples; ++i) {
      double phase = i * PI_2_N;
      sinus_values[i]   = (byte)(127 * sin(phase));
      cosinus_values[i] = (byte)(127 * cos(phase));
    }
  }
}
  
Convolver::~Convolver() {
  free(sinus_values);
  free(cosinus_values);
}

void Convolver::add_sample(Sample sample) {
  if (!is_valid()) {
    return;
  }
  ++add_sample_index;
  add_sample_index %= wave_length_in_samples;
  sum_sinus += sample * sinus_values[add_sample_index];
  sum_cosinus += sample * cosinus_values[add_sample_index];
}

void Convolver::remove_sample(Sample sample) {
  if (!is_valid()) {
    return;
  }
  ++remove_sample_index;
  remove_sample_index %= wave_length_in_samples;
  sum_sinus -= sample * sinus_values[remove_sample_index];
  sum_cosinus -= sample * cosinus_values[remove_sample_index];
}

boolean Convolver::is_valid() {
  return valid;
}

unsigned long Convolver::current_squared_intensity() { 
  if (!is_valid()) {
    return 0;
  }
  return sum_sinus * sum_sinus + sum_cosinus * sum_cosinus;
}