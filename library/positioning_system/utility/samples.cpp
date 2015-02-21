
#include "samples.hpp"

SampleBuffer::SampleBuffer(short _number_of_samples) {
  number_of_samples = _number_of_samples;
  current_sample_index = 0;
  sum_of_all_samples = 0;
  if (number_of_samples > 0) {
    samples = (Sample *)calloc(number_of_samples, sizeof(Sample));
    Serial.print("allocated ");
    Serial.println(number_of_samples);
    valid = samples ? true : false;
  } else {
    samples = NULL;
    valid = false;
  }
}

SampleBuffer::~SampleBuffer() {
  valid = false;
  free(samples);
  Serial.print("freed ");
  Serial.println(number_of_samples);
}

Sample SampleBuffer::replaced_by(Sample new_sample) {
  if (!valid) {
    return 0;
  }
  Sample old_sample = samples[current_sample_index];
  sum_of_all_samples -= old_sample;
  sum_of_all_samples += new_sample;
  samples[current_sample_index] = new_sample;
  ++current_sample_index;
  current_sample_index %= number_of_samples;
  return old_sample;
}

long SampleBuffer::sum() {
  if (!valid) {
    return 0;
  }
  return sum_of_all_samples;
}

Sample SampleBuffer::average() {
  if (!valid) {
    return 0;
  }
  return sum_of_all_samples / number_of_samples;
}

boolean SampleBuffer::is_valid() {
  return valid;
}

Sample SampleBuffer::normalize(Sample sample) {
  if (!valid) {
    return 0;
  }
  return sample - sum_of_all_samples / number_of_samples;
}

short SampleBuffer::size() {
  return number_of_samples;
}