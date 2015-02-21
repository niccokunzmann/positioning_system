
#include "samples.hpp"

SampleBuffer::SampleBuffer(short _number_of_samples) {
  number_of_samples = _number_of_samples;
  current_sample_index = 0;
  if (number_of_samples > 0) {
    samples = (Sample *)calloc(number_of_samples, sizeof(Sample));
    valid = samples ? true : false;
  } else {
    samples = NULL;
    valid = false;
  }
}

SampleBuffer::~SampleBuffer() {
  valid = false;
  free(samples);
}

Sample SampleBuffer::replaced_by(Sample new_sample) {
  if (!valid) {
    return 0;
  }
  Sample old_sample = samples[current_sample_index];
  samples[current_sample_index] = new_sample;
  ++current_sample_index;
  current_sample_index %= number_of_samples;
  return old_sample;
}

long SampleBuffer::sum() {
  if (!valid) {
    return 0;
  }
  long sum_of_all_samples = 0;
  for (int i = 0; i < number_of_samples; ++i) {
    sum_of_all_samples += samples[i];
  }
  return sum_of_all_samples;
}

Sample SampleBuffer::average() {
  if (!valid) {
    return 0;
  }
  return sum() / number_of_samples;
}

boolean SampleBuffer::is_valid() {
  return valid;
}

Sample SampleBuffer::normalize(Sample sample) {
  if (!valid) {
    return 0;
  }
  return sample - sum() / number_of_samples;
}

short SampleBuffer::size() {
  return number_of_samples;
}