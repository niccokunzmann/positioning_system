
#include <_hpa.h>



void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  HPA::xreal x;
  x = 2;
  Serial.print("Square root of ");
  Serial.print(x._2String());
  Serial.print(" is ");
  Serial.print(sqrt(x)._2String());
  Serial.print(" .");
  
  Serial.end();
  
}

void loop () {
  
};