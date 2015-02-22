
#include "positioning_system_test.h"
#line 4

int peakvar = 1;
#define nothing  p.add_intensities(0,0,0);
#define peak     p.add_intensities(peakvar++,0,0);
#define window_end(i) assertTrue(p.reached_end_of_window()); \
                      assertEqual(p.offset_of_base_frequency(), i); \
                      p.reset_window();
#define no_window_end assertFalse(p.reached_end_of_window());


test(example_3_1_1) {
  // expected distance between peaks: 3
  // signal width: 2 results in 3 peak width
  // latency: 1
  PeakDetectionInAWindow p = PeakDetectionInAWindow(3, 2, 1);
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

test(example_6_1_2) {
  // expected distance between peaks: 6
  // peak width: 1
  // latency: 2
  PeakDetectionInAWindow p = PeakDetectionInAWindow(6, 2, 2);
                            // w1 w2 w3 // windows
  nothing  no_window_end    // xx
  nothing  no_window_end    // ok 
  nothing  no_window_end    // ok 
  nothing  no_window_end    // ok 
  peak     no_window_end    // OK  
  nothing  no_window_end    // ok xx
  nothing  no_window_end    // ok ok
  nothing     window_end(5) // ok ok
  peak     no_window_end    //    OK
  nothing  no_window_end    //    ok xx
  nothing  no_window_end    //    ok ok
  nothing  no_window_end    //    ok ok
  nothing     window_end(4) //    ok ok
  nothing  no_window_end    //       ok 
  nothing  no_window_end    //       ok 
  nothing  no_window_end    //       ok 
  peak        window_end(8) //       OK
  peak     no_window_end    //          xx
  peak     no_window_end    //          OK
  nothing  no_window_end    //          ok 
  nothing  no_window_end    //          ok 
  nothing  no_window_end    //          ok 
  nothing  no_window_end    //          ok 
  nothing  no_window_end    //          ok 
  nothing     window_end(2) //          ok 
}

test(recent_maximum_values_are_forgotten) {
  PeakDetectionInAWindow p = PeakDetectionInAWindow(3, 2, 1);
  nothing
  nothing
  p.add_intensities(3,0,0);
  nothing  window_end(3)
  nothing
  nothing
  p.add_intensities(1,0,0);
  window_end(4)
}

test(maxima_in_three_windows) {
  PeakDetectionInAWindow p = PeakDetectionInAWindow(3, 2, 1);
  p.add_intensities(1,3,4);
  p.add_intensities(1,4,3); // 2
  p.add_intensities(2,3,3); // 1
  p.add_intensities(1,3,5); // 3
  assertTrue(p.reached_end_of_window());
  assertEqual(p.offset_of_base_frequency(), 3);
  assertEqual(p.offset_of_second_frequency(), 2);
  assertEqual(p.offset_of_third_frequency(), 4);
  p.reset_window();
  p.add_intensities(2,3,3); // 2
  p.add_intensities(0,0,1);        assertFalse(p.reached_end_of_window());
  p.add_intensities(3,1,4); // 1 3
  assertTrue(p.reached_end_of_window());
  assertEqual(p.offset_of_base_frequency(), 4);
  assertEqual(p.offset_of_second_frequency(), 2);
  assertEqual(p.offset_of_third_frequency(), 4);
  p.reset_window();
  p.add_intensities(8,3,3); // 3
  p.add_intensities(3,1,2); // 1
  p.add_intensities(0,0,1);        assertFalse(p.reached_end_of_window());
  p.add_intensities(0,4,1); // 2
  assertTrue(p.reached_end_of_window());
  assertEqual(p.offset_of_base_frequency(), 2);
  assertEqual(p.offset_of_second_frequency(), 4);
  assertEqual(p.offset_of_third_frequency(), 1);
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  Test::run();
}



