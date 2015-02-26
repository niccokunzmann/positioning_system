
#ifndef test_location_function_hpp
#define test_location_function_hpp

#include "positioning_system.h"

double position_to_offset(          
          double x, double y, 
          SpeakerPosition P,
          PositioningSystemConfiguration *configuration
          );

void add_samples_for_position(
          double x, double y, Location *location, 
          PositioningSystemConfiguration *configuration
          );

#endif