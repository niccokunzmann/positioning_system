
#ifndef positioning_hpp
#define positioning_hpp

void position(const double dt1, const double dt2, 
              const double a, const double b,
              double *x, double* y);

typedef struct MicrophonePosition {
  double x;
  double y;
} MicrophonePosition;

typedef MicrophonePosition SpeakerPosition;

MicrophonePosition position(
               const double dt1, const double dt2, 
               const SpeakerPosition A, 
               const SpeakerPosition B, 
               const SpeakerPosition C);

#endif