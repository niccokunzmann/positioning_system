
// from example http://wiki.openmusiclabs.com/wiki/Example
#define FFT_N 256 // set to 256 point fft

#include <FFT.h> // include the library

#include <math.h>

void setup_timer2_frequency(){
  // copied from sound_generator.ino
  //http://www.instructables.com/id/Arduino-Timer-Interrupts/

  cli();//stop interrupts

  //set timer2 interrupt at 31250Hz
  TCCR2A = 0;// set entire TCCR1A register to 0
  TCCR2B = 0;// same for TCCR1B
  TCNT2  = 0;//initialize counter value to 0
  // set compare match register for 33333hz/4 increments
  OCR2A = /*60*/ 243;// = 16000000 / (32768 * 8) - 1 (must be <256)
  // turn on CTC mode
  TCCR2A |= (1 << WGM12);
  // Set CS10 bits for 8 prescaler
  TCCR2B |= (1 << CS10);  
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE1A);
  sei();//allow interrupts
}

boolean record_sound = false; // interface
int record_sound_counter = 0; // privat
boolean recording_sound = false;

const int microphone_pin = A0;

ISR(TIMER2_COMPA_vect){//timer2 interrupt 33333Hz
  record_sound_counter += 2;
  if (record_sound_counter >= 512) {
    record_sound_counter = 0;
    if (recording_sound) {
      // finish recording
      recording_sound = false;
      record_sound = false;
    } else if (record_sound) {
      recording_sound = true;
    }
  }
  if (recording_sound) {
    int sensor_value = analogRead(microphone_pin);
    sensor_value-= 0x0200; // form into a signed int
    //sensor_value <<= 6; // form into a 16b signed int
    fft_input[record_sound_counter] = sensor_value;
    fft_input[record_sound_counter + 1] = 0; 
  }
}

void setup_microphone() {
  pinMode(microphone_pin, INPUT);
  //analogWrite(microphone_pin, HIGH);
}

double high_amplitude = 0.0;
double middle_amplitude = 0.0;
double low_amplitude = 0.0;

double high_phase = 0.0;
double middle_phase = 0.0;
double low_phase = 0.0;

const int low_position = 22;
const int middle_position = 30;
const int high_position = 37;

void run_positioning() {
  record_sound = true;
  //Serial.println("aaa");
  while (record_sound) { // wait for ISR to record 256 samples
    Serial.print("");
  } 
  int sum = 0;
  for(int i = 0; i < 254; i+= 1) {
    sum += fft_input[i * 2];
  }
  sum /= 256;
  for(int i = 0; i < 254; i+= 1) {
    fft_input[i * 2] -= sum;
  }
  if (true) {
    Serial.print("[");
    for(int i = 0; i < 254; i+= 1) {
      Serial.print(fft_input[i * 2]);
      Serial.print(", ");
    }
    Serial.print(fft_input[254]);
    Serial.println("]");
  }
  //Serial.println("xxxx");
  fft_window();
  fft_reorder();
  fft_run();
  /*  from fft_read_me.txt
      fft_input[0] & fft_input[1] = bin0 magnitudes (0hz -> Fs/N)
      fft_input[2] & fft_input[3] = bin1 magnitudes (Fs/N -> 2Fs/N)
  */
  int low_sin_magnitude = fft_input[low_position * 2 - 2];
  int low_cos_magnitude = fft_input[low_position * 2 - 1];
  int middle_sin_magnitude = fft_input[middle_position * 2 - 2];
  int middle_cos_magnitude = fft_input[middle_position * 2 - 1];
  int high_sin_magnitude = fft_input[high_position * 2 - 2];
  int high_cos_magnitude = fft_input[high_position * 2 - 1];
  low_amplitude = sqrt(low_sin_magnitude * low_sin_magnitude + low_cos_magnitude * low_cos_magnitude) / 256.0;
  middle_amplitude = sqrt(middle_sin_magnitude * middle_sin_magnitude + middle_cos_magnitude * middle_cos_magnitude) / 256.0;
  high_amplitude = sqrt(high_sin_magnitude * high_sin_magnitude + high_cos_magnitude * high_cos_magnitude) / 256.0;
  
  low_phase = atan2(low_cos_magnitude, low_sin_magnitude);
  middle_phase = atan2(middle_cos_magnitude, middle_sin_magnitude);
  high_phase = atan2(high_cos_magnitude, high_sin_magnitude);
}




void setup() {
  setup_microphone();
  setup_timer2_frequency();
  Serial.begin(9600); 
  while (!Serial) {};
  Serial.println("Positioning Running"); 
}

void loop() {
  run_positioning();
  if (true) {
    int v_high = high_phase * 180 / PI / 5;
    int v_low = low_phase * 180 / PI / 3;
    int v_middle = middle_phase * 180 / PI / 4;
    
    Serial.print(v_low - v_middle);
    Serial.print(" low middle ");
//    Serial.print(low_amplitude * 100);
    Serial.print("\t");
  
    Serial.print(v_high - v_middle);
    Serial.print(" middle high ");
//    Serial.print((middle_amplitude * 100));
    Serial.print("\t");
  
    Serial.print(v_high - v_low);
    Serial.print(" low-high ");
//    Serial.print(high_amplitude * 100);
    Serial.println("\t");
  }
  
  delay(300);
}
