
#ifndef positioning_hpp
#define positioning_hpp

#include "units.hpp"

// The result is called P.
// What is the position of P within A, B and C 
// given the Positions of A, B and C and
//       the differences in the distances
//       BP - CP and BP - AP
MicrophonePosition position(
               const Meters BP_minus_CP, const Meters BP_minus_AP, 
               const SpeakerPosition A, 
               const SpeakerPosition B, 
               const SpeakerPosition C);

// this is a special case of the above function with 
// C = (0, 0)
// B = (0, b)
// A = (a, 0)
// as a perpendicular triangle
// where teh angle at C has 90°
void position(const Meters BP_minus_CP, const Meters BP_minus_AP, 
              const Meters a, const Meters b,
              Meters *x, Meters* y);


#endif