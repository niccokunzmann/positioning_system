
#include "convolution.hpp"
// http://www.nongnu.org/avr-libc/user-manual/group__avr__math.html
#include "math.h"
//#include "positioning_system_test.h"

Convolver::Convolver(
      short wave_length_in_samples, 
      short number_of_samples_in_buffer, 
      int8_t sample_bits) : 
          wave_length_in_samples(wave_length_in_samples), 
          number_of_samples_in_buffer(number_of_samples_in_buffer) {
  valid = wave_length_in_samples > 1;
  if (valid) {
    
    add_sample_index = -1;
    remove_sample_index = (-number_of_samples_in_buffer) % wave_length_in_samples - 1;
    sum_sinus = 0;
    sum_cosinus = 0;
  }
  allocate_memory_for_wave();
  fill_wave();
  compute_overflow_prevention(sample_bits);
}
  
Convolver::~Convolver() {
  free(sinus_values);
  free(cosinus_values);
}

void Convolver::compute_overflow_prevention(int8_t sample_bits) {
  if(!valid) {
    return;
  }
  long sum = 0;
  for(int i = 0; i < wave_length_in_samples; ++i) {
    sum += abs(sinus_values[i]) + abs(cosinus_values[i]);
  }
  sum = sum * number_of_samples_in_buffer / wave_length_in_samples / 2;
  // compute bits out of sum of sinus_values
  // 10 bit samples
  // 16 bit value - 1 bit sign
  // sum <- wave and number_of_samples_in_buffer
  overflow_preventing_intensity_divisor_bits = sample_bits - 15;
  while (sum) {
    sum >>= 1;
    ++overflow_preventing_intensity_divisor_bits;
  }
  if (overflow_preventing_intensity_divisor_bits < 0) {
    overflow_preventing_intensity_divisor_bits = 0;
  } else if (overflow_preventing_intensity_divisor_bits > 15) {
    // In this case we shift out more than half of the long ->
    // This means we need more bits than a long has  
    // for the sum_cosinus and sum_sinus.
    // This indicates that the sums could overflow.
    // We should not operate under these conditions.
    valid = false;
  }
}
  
void Convolver::allocate_memory_for_wave() {
  if ((wave_length_in_samples > 1) && valid) {
    sinus_values =   (int8_t*)malloc(wave_length_in_samples * sizeof(int8_t));
    cosinus_values = (int8_t*)malloc(wave_length_in_samples * sizeof(int8_t));
    valid = cosinus_values && sinus_values;
  } else {
    sinus_values = NULL;
    cosinus_values = NULL;
    valid = false;
  }
}

void Convolver::fill_wave() {
  if (valid) {
    double PI_2_N = M_PI * 2.0 / wave_length_in_samples;
    for (int i = 0; i < wave_length_in_samples; ++i) {
      double phase = i * PI_2_N;
      sinus_values[i]   = (int8_t)(127 * sin(phase));
      cosinus_values[i] = (int8_t)(127 * cos(phase));
    }
  }
}

long convolve(Sample sample, int8_t value) {
  long long_sample = sample;
  long long_value = value;
  return long_sample * long_value;
}

void Convolver::add_sample(Sample sample) {
  if (!is_valid()) {
    return;
  }
  add_sample_index = (add_sample_index + 1) % wave_length_in_samples;
  sum_sinus +=   convolve(sample, sinus_values  [add_sample_index]);
  sum_cosinus += convolve(sample, cosinus_values[add_sample_index]);
}

void Convolver::remove_sample(Sample sample) {
  if (!is_valid()) {
    return;
  }
  remove_sample_index = (remove_sample_index + 1) % wave_length_in_samples;
  sum_sinus   -= convolve(sample, sinus_values  [remove_sample_index]);
  sum_cosinus -= convolve(sample, cosinus_values[remove_sample_index]);
}

boolean Convolver::is_valid() {
  return valid;
}

long Convolver::squared_intensity() { 
  if (!is_valid()) {
    return 0;
  }
  // remove some bits to prevent overflow
  long s = sum_sinus >> overflow_preventing_intensity_divisor_bits; 
  long c = sum_cosinus >> overflow_preventing_intensity_divisor_bits;
  return s * s + c * c;
}

void Convolver::replace_sample(Sample old_sample, Sample new_sample) {
  //pvar(old_sample);
  //pvar(new_sample);
  add_sample(new_sample);
  remove_sample(old_sample);
}

WaveState Convolver::wave_state() {
  return WaveState(
        squared_intensity(), 
        sum_sinus, 
        sum_cosinus, 
        wave_length_in_samples, 
        add_sample_index + number_of_samples_in_buffer);
}