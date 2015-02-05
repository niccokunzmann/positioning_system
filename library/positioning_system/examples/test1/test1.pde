


#include <fix_arduino_macros.h>
#include <_hpa.h>
#include <hpaconf.h>
#include <xpre.h>

#include <positioning_system.h>

#include "positioning_system.h"


void setup() {

  Serial.begin(9600);
  while (!Serial);
  
  test_positioning_system_1();

}

void loop() {
  
}
