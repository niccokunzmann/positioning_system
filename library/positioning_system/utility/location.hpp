
#ifndef location_hpp
#define location_hpp

#include "configuration.hpp"

class Location {
  public:
    Location(PositioningSystemConfiguration configuration);
    ~Location();
    
    compute_new_coordinates();
    x();
    y();
    
    analogRead(int input_pin);
    
    begin();
    end();
    
    pause();
    resume();
    
  private: 
    PositioningSystemConfiguration configuration;
}



#endif