

void setup() {
  Serial.begin(9600); 
  while (!Serial) {};
  setup_volume_recognition(A0);
  Serial.print("Lautstaerke der Schwingung: "); 
  Serial.print(get_frequency());
  Serial.println("Hz");
}

void loop() {
  int lautstaerke = get_volume_squared();
  Serial.println(lautstaerke); 
  delay(100);
}


/*************
 *  Program  *
 *************/

#include <math.h>

void setup_volume_recognition(int microphone_pin) {
  setup_microphone_pin(microphone_pin);
  setup_check_values();
  setup_samples();
  setup_waves();
  setup_timer2_frequency();
}

int microphone_pin;

// http://arduino.cc/en/Reference/AnalogRead
// It takes about 100 microseconds (0.0001 s) to read an analog input, so the maximum reading rate is about 10,000 times a second. 
//   5 * 5 * 5 * 5 * 2 * 5 = 6250
const int sample_frequency       = 6250; //Hz max 10000Hz
const int samples_per_wave_cycle = 10;  // determines the frequency
const int number_of_samples      = 300; // used to determine the volume

const int wave_frequency         = sample_frequency / samples_per_wave_cycle;  //Hz
int samples[number_of_samples];

volatile int sum_sinus = 0;
volatile int sum_cosinus = 0;

byte sinus_wave[samples_per_wave_cycle];
byte cosinus_wave[samples_per_wave_cycle];
int sample_index = 0;

void setup_timer2_frequency(){
  // copied from sound_generator.ino
  //http://www.instructables.com/id/Arduino-Timer-Interrupts/

  cli();//stop interrupts

  //set timer2 interrupt at sample_frequency
  TCCR2A = 0;// set entire TCCR1A register to 0
  TCCR2B = 0;// same for TCCR1B
  TCNT2  = 0;//initialize counter value to 0
  // set compare match register for sample_frequency increments
  OCR2A = 9;// = 16000000 / (sample_frequency * 256) - 1 (must be <256)
  // turn on CTC mode
  TCCR2A |= (1 << WGM12);
  // Set CS12 bits for 256 prescaler
  TCCR2B |= (1 << CS12);  
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE1A);
  sei();//allow interrupts
}

ISR(TIMER2_COMPA_vect){//timer2 interrupt at sample_frequency
  sample_index = (sample_index + 1) % number_of_samples;
  int wave_index = sample_index % samples_per_wave_cycle;
  int s_sin = sinus_wave[wave_index];
  int s_cos = cosinus_wave[wave_index];
  int last_sample = samples[sample_index];
  int sample = analogRead(microphone_pin);
  sum_sinus   += (sample - last_sample) * s_sin;
  sum_cosinus += (sample - last_sample) * s_cos;
  samples[sample_index] = sample;
}

void setup_samples() {
  for (int sample_number = 0; sample_number < number_of_samples; ++sample_number) {
    samples[sample_number] = 0;
  }
  sum_sinus = 0;
  sum_cosinus = 0;
}

void setup_waves() {
  for (int i = 0; i < samples_per_wave_cycle; ++i) {
    sinus_wave[i]   = byte(sin(i / samples_per_wave_cycle * PI * 2) * 127);
    cosinus_wave[i] = byte(cos(i / samples_per_wave_cycle * PI * 2) * 127);
  }
}

int get_frequency() {
  return wave_frequency;
}

int get_volume_squared() {
  return sum_sinus * sum_sinus + sum_cosinus * sum_cosinus;
}
 
void setup_microphone_pin(int _microphone_pin) {
  microphone_pin = _microphone_pin;
  pinMode(microphone_pin, INPUT);
}

void setup_check_values() {
  if (Serial) {
    if (sample_frequency / samples_per_wave_cycle * samples_per_wave_cycle != sample_frequency) {
      Serial.println("sample_frequency should be a multiple of samples_per_wave_cycle.");
    };
    if (number_of_samples / samples_per_wave_cycle * samples_per_wave_cycle != number_of_samples) {
      Serial.println("number_of_samples should be a multiple of samples_per_wave_cycle.");
    };
  }
}



