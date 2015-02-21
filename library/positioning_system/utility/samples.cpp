
#include "samples.hpp"

SampleBuffer::SampleBuffer(short _number_of_samples) {
  number_of_samples = _number_of_samples;
  current_sample_index = 0;
  sum_of_all_samples = 0;
  samples = (NormalizedSample *)calloc(number_of_samples, sizeof(Sample));
  valid = samples ? true : false;
}

SampleBuffer::~SampleBuffer() {
  valid = false;
  free(samples);
}

NormalizedSample SampleBuffer::replaced_by(NormalizedSample new_sample) {
  if (!valid) {
    return 0;
  }
  NormalizedSample old_sample = samples[current_sample_index];
  sum_of_all_samples -= old_sample;
  sum_of_all_samples += new_sample;
  samples[current_sample_index] = new_sample;
  return old_sample;
}

long SampleBuffer::sum() {
  if (!valid) {
    return 0;
  }
  return sum_of_all_samples;
}

NormalizedSample SampleBuffer::average() {
  if (!valid) {
    return 0;
  }
  return sum_of_all_samples / number_of_samples;
}

boolean SampleBuffer::is_valid() {
  return valid;
}

NormalizedSample normalize(Sample sample) {
  if (!valid) {
    return 0;
  }
  return sample - sum_of_all_samples / number_of_samples;
}