
// from example http://wiki.openmusiclabs.com/wiki/Example
#define FFT_N 256 // set to 256 point fft

#include <FFT.h> // include the library


void setup_timer2_frequency(){
  // copied from sound_generator.ino
  //http://www.instructables.com/id/Arduino-Timer-Interrupts/

  cli();//stop interrupts

  //set timer2 interrupt at 31250Hz
  TCCR2A = 0;// set entire TCCR1A register to 0
  TCCR2B = 0;// same for TCCR1B
  TCNT2  = 0;//initialize counter value to 0
  // set compare match register for 33333hz increments
  OCR2A = 60;// = 16000000 / (32768 * 8) - 1 (must be <256)
  // turn on CTC mode
  TCCR2A |= (1 << WGM12);
  // Set CS10 bits for 8 prescaler
  TCCR2B |= (1 << CS10);  
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE1A);
  sei();//allow interrupts
}

boolean record_sound = false; // interface
int record_sound_counter = 0; // private

const int microphone_pin = A0;

ISR(TIMER2_COMPA_vect){//timer2 interrupt 33333Hz
  if (record_sound) {
    ++record_sound_counter;
    if (record_sound_counter >= 512) {
      record_sound = false;
      record_sound_counter = 0;
    } else {
      int sensor_value = analogRead()
      fft_input[record_sound_counter] = 
    }
    
  }
}

void setup_microphone() {
  pinMode(microphone_pin, INPUT);
}

void setup() {
  setup_microphone();
  setup_timer2_frequency();
  
  
}

void loop() {
  
}
