
#include "samples.hpp"
#include "math.h"

double half_life_sample_to_multiplier(double half_life_samples) {
  return pow(0.5, 1. / half_life_samples);
}

ExponentialAverage::ExponentialAverage(double _multiplier, double start) {
  multiplier = _multiplier;
  current_average = start / (1 - multiplier);
}
    
void ExponentialAverage::add_sample(Sample sample) {
  current_average *= multiplier;
  current_average += sample; 
}

const Sample ExponentialAverage::average() {
  return round(current_average * (1 - multiplier));
}

const Sample ExponentialAverage::normalize(Sample sample) {
  return sample - average();
}

