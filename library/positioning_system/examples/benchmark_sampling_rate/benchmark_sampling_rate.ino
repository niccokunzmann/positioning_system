
#include "positioning_system.h"

int sampling_frequency = 2287;

void setup() {
  pinMode(A0, INPUT);
  Serial.begin(9600); 
}

void loop() {
  PositioningSystemConfiguration configuration;
  configuration.sampling_frequency_in_hertz = sampling_frequency;
  configuration.frequency_1_in_hertz = sampling_frequency / 4;
  configuration.frequency_2_in_hertz = sampling_frequency / 3;
  configuration.frequency_3_in_hertz = sampling_frequency / 5;
  Location location = Location(&configuration);
  if (!location.is_valid()) {
    Serial.println("invalid location");
    return;
  }
  int READS = 10000;
  int time = -millis();
  for (int i = 0; i < READS; i++) {
    location.add_sample(analogRead(A0));
  }
  time += millis(); 
  Serial.print("time for ");
  Serial.print(READS);
  Serial.print(" reads: ");
  Serial.print(time);
  Serial.print("ms. maximum sample frequency: ");
  int new_sampling_frequency = (double)READS * 1000 / time;
  Serial.println(new_sampling_frequency); // 2257 reads / second
  location.compute_new_coordinates();
  sampling_frequency+= new_sampling_frequency;
  sampling_frequency/= 2;
}