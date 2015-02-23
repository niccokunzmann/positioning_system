
#ifndef units_hpp
#define units_hpp

// a sample is a value you get from analogRead
typedef short Sample; 
// intensity is the intensity value of a sinal
typedef long Intensity;
// NumberOfSamples
typedef short NumberOfSamples;
// SignalPosition is an offset in samples
// it is used like NumberOfSamples except that the signal can be placed between samples
typedef double SignalPosition;

// the rate in Hz used for sampling
typedef short SamplingRate;
// Time
typedef double Time;


#endif