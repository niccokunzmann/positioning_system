
#include "positioning_system_test.h"
#line 4

/*
test(offset_of_frequencies_at_start) {
  PeakDetectionInAWindow p = PeakDetectionInAWindow(3, 1, 1);
  p.add_intensities(0,0,1); // padding for varying distances
  for (int i = 0; i < 5; ++i) {
    println2("iteration:", i);
    p.add_intensities(0,0,1);
    p.add_intensities(0,1,0);
    p.add_intensities(1,0,0);
    assertEqual(p.offset_of_base_frequency(), 3);
    assertTrue(p.reached_end_of_window());
    p.reset_window();
  }
}

test(when_to_reset_window) {
  PeakDetectionInAWindow p = PeakDetectionInAWindow(3, 1, 1);
  p.add_intensities(0,0,0);
  for(int i = 0; i < 4; ++i) {
    assertFalse(p.reached_end_of_window());
    p.add_intensities(0,0,0);
    assertFalse(p.reached_end_of_window());
    p.add_intensities(0,0,0);
    assertFalse(p.reached_end_of_window());
    p.add_intensities(0,0,0);
    assertTrue(p.reached_end_of_window());
    p.reset_window();
  }
}*/

int peakvar = 1;
#define nothing  p.add_intensities(0,0,0);
#define peak     p.add_intensities(peakvar++,0,0);
#define window_end(i) assertTrue(p.reached_end_of_window()); \
                      assertEqual(p.offset_of_base_frequency(), i); \
                      p.reset_window();
#define no_window_end assertFalse(p.reached_end_of_window());


test(messed_up_start) {
  PeakDetectionInAWindow p = PeakDetectionInAWindow(3, 1, 1);
                            // w1 w2 w3 w4 // windows
  nothing  no_window_end    // xx
  peak     no_window_end    // OK 
  nothing  no_window_end    // ok xx 
  nothing     window_end(2) // ok ok 
  nothing  no_window_end    //    ok 
  peak        window_end(4) //    OK 
  peak     no_window_end    //       xx
  peak     no_window_end    //       OK
  nothing  no_window_end    //       ok xx
  nothing     window_end(2) //       ok ok
  peak     no_window_end    //          OK
  nothing     window_end(3) //          ok
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  Test::run();
}



