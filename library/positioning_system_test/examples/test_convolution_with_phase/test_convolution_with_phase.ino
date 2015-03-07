
#include "positioning_system_test.h"
#line 4


test(fmod) {
  skip(); 
  return;
  assertEqual(fmod(-2, 4), 2);
  assertEqual(fmod(-1, 4), 3);
  assertEqual(fmod( 0, 4), 0);
  assertEqual(fmod( 1, 4), 1);
  assertEqual(fmod( 2, 4), 2); 
}
  
TEST_CONVOLUTION(3, 0, 112)
TEST_CONVOLUTION(3, 0, 111)
TEST_CONVOLUTION(3, 0, 110)

TEST_CONVOLUTION(4, 0, 112)
TEST_CONVOLUTION(4, 0, 111)
TEST_CONVOLUTION(4, 0, 110)
TEST_CONVOLUTION(4, 0, 113)

TEST_CONVOLUTION(4, 50, 110)
TEST_CONVOLUTION(4, 50, 111)
TEST_CONVOLUTION(4, 50, 112)
TEST_CONVOLUTION(4, 50, 113)
TEST_CONVOLUTION(4, 110, 110)
TEST_CONVOLUTION(4, 110, 111)
TEST_CONVOLUTION(4, 110, 112)
TEST_CONVOLUTION(4, 110, 113)
TEST_CONVOLUTION(4, 170, 110)
TEST_CONVOLUTION(4, 170, 111)
TEST_CONVOLUTION(4, 170, 112)
TEST_CONVOLUTION(4, 170, 113)
TEST_CONVOLUTION(4, 220, 110)
TEST_CONVOLUTION(4, 220, 111)
TEST_CONVOLUTION(4, 220, 112)
TEST_CONVOLUTION(4, 220, 113)
TEST_CONVOLUTION(4, 280, 110)
TEST_CONVOLUTION(4, 280, 111)
TEST_CONVOLUTION(4, 280, 112)
TEST_CONVOLUTION(4, 280, 113)
TEST_CONVOLUTION(4, 340, 110)
TEST_CONVOLUTION(4, 340, 111)
TEST_CONVOLUTION(4, 340, 112)
TEST_CONVOLUTION(4, 340, 113)
/*

//TEST_CONVOLUTION(3, 10, 12)
//TEST_CONVOLUTION(3, 10, 13)
//TEST_CONVOLUTION(3, 30, 12)
//TEST_CONVOLUTION(3, 30, 11)
//TEST_CONVOLUTION(3, 50, 12)
//TEST_CONVOLUTION(3, 50, 13)
//TEST_CONVOLUTION(3, 160, 12)
//TEST_CONVOLUTION(3, 160, 11)
/*
TEST_CONVOLUTION(3, 1, 33)
TEST_CONVOLUTION(3, 1, 31)
TEST_CONVOLUTION(3, 1, 32)
TEST_CONVOLUTION(4, 1, 44)
TEST_CONVOLUTION(4, 1, 45)
TEST_CONVOLUTION(4, 1, 46)
TEST_CONVOLUTION(4, 1, 47)
TEST_CONVOLUTION(5, 1, 55)
TEST_CONVOLUTION(6, 1, 66)
TEST_CONVOLUTION(7, 1, 77)
TEST_CONVOLUTION(8, 1, 88)
TEST_CONVOLUTION(9, 1, 97)
TEST_CONVOLUTION(10, 1, 22)
TEST_CONVOLUTION(11, 1, 87)
TEST_CONVOLUTION(12, 1, 67)
TEST_CONVOLUTION(13, 1, 100)
/*
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
//TEST_CONVOLUTION(330, 2)
TEST_CONVOLUTION(100, 2)
//TEST_CONVOLUTION(1000, 2)
*/

test(default_wave_state_has_phase_0) {
  assertEqual(WaveState().phase_in_samples(), 0.0);
}

void setup() {
  TEST_APPROXIMATION_EPSILON = 0.01;
  Serial.begin(9600);
}

void loop() {
  Test::run();
}