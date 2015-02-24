
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
// Time in seconds
typedef double Seconds;
typedef Seconds Time;
// for speed of sound
typedef double MetersPerSecond;
typedef double Meters;
// temperature
typedef double DegreesCelsius;
typedef double DegreesFahrenheit;
typedef double Kelvin;

typedef struct MicrophonePosition {
  Meters x;
  Meters y;
} MicrophonePosition;

typedef MicrophonePosition SpeakerPosition;


#endif