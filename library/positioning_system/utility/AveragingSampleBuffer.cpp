
#include "samples.hpp"

AveragingSampleBuffer::AveragingSampleBuffer(short number_of_samples) : SampleBuffer(number_of_samples) {
  sum_of_all_samples = 0;
}

Sample AveragingSampleBuffer::replaced_by(Sample new_sample) {
  // call to super class 
  // http://www.linuxquestions.org/questions/programming-9/c-call-super-class-virtual-method-from-replacement-method-4175460209/
  sum_of_all_samples += new_sample;
  Sample removed_sample = SampleBuffer::replaced_by(new_sample);
  sum_of_all_samples -= removed_sample;
  return removed_sample;
}

long AveragingSampleBuffer::sum() {
  if (!valid) {
    return 0;
  }
  return sum_of_all_samples;
}

Sample AveragingSampleBuffer::average() {
  if (!valid) {
    return 0;
  }
  return sum_of_all_samples / size();
}


Sample AveragingSampleBuffer::normalize(Sample sample) {
  if (!valid) {
    return 0;
  }
  return sample - average();
}