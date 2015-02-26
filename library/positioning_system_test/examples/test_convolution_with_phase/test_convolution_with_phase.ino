
#include "positioning_system_test.h"
#include "math.h"

void assertConvolutes(int wave_length_in_samples, double phase_in_samples) {
  int samples = wave_length_in_samples * 50;
  Convolver convolver = Convolver(wave_length_in_samples, samples);
  for (int i = 0; i < samples; ++i) {
    convolver.add_sample(round(511 * sin(2 * M_PI * (i + phase_in_samples) / wave_length_in_samples)));
  }
  WaveState wave_state = convolver.wave_state();
  assertEqual(wave_state.squared_intensity, convolver.squared_intensity());
  double phase_between_samples = fmod(phase_in_samples + 0.5, 1) - 0.5;
  pvar(wave_state.phase_between_samples());
  pvar(phase_between_samples);
  double difference = abs(wave_state.phase_between_samples() - phase_between_samples);
  assertLess(difference, 0.01);
}

#define TEST_CONVOLUTION(WAVE_LENGTH, PHASE) test(test##_##WAVE_LENGTH##_##PHASE) { assertConvolutes(WAVE_LENGTH, PHASE / 100.); }

TEST_CONVOLUTION(3, 0)
TEST_CONVOLUTION(4, 0)
TEST_CONVOLUTION(5, 0)
TEST_CONVOLUTION(6, 0)
TEST_CONVOLUTION(7, 0)
TEST_CONVOLUTION(7, 3)
TEST_CONVOLUTION(7, 10)
TEST_CONVOLUTION(7, 20)
TEST_CONVOLUTION(7, 30)
TEST_CONVOLUTION(7, 40)
TEST_CONVOLUTION(7, 50)
TEST_CONVOLUTION(7, 60)
TEST_CONVOLUTION(7, 70)
TEST_CONVOLUTION(7, 80)
TEST_CONVOLUTION(7, 90)

TEST_CONVOLUTION(30, 90)
TEST_CONVOLUTION(29, 90)
TEST_CONVOLUTION(330, 2)
TEST_CONVOLUTION(100, 2)
TEST_CONVOLUTION(1000, 2)

void setup() {
  TEST_APPROXIMATION_EPSILON = 0.5;
  Serial.begin(9600);
}

void loop() {
  Test::run();
}
