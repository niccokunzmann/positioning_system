
#ifndef test_convolution_functions_hpp
#define test_convolution_functions_hpp

void assertConvolutes(int wave_length_in_samples, double given_phase_in_samples, short buffer_size);

#define TEST_CONVOLUTION(WAVE_LENGTH, PHASE, BUFFER_SIZE) \
  test(test##_##WAVE_LENGTH##_##PHASE##_##BUFFER_SIZE) { \
    assertConvolutes(WAVE_LENGTH, PHASE / 100., BUFFER_SIZE); \
  }



#endif
