

void setup() {
  Serial.begin(9600); 
  while (!Serial) {};
  setup_volume_recognition(A0);
  Serial.print("Lautstaerke der Schwingung: "); 
  Serial.print(get_frequency());
  Serial.println("Hz");
}

void loop() {
  long lautstaerke = get_volume_squared();
  Serial.println(lautstaerke); 
  //print_samples();
  delay(100);
}


/*************
 *  Program  *
 *************/

#include <math.h>

void setup_volume_recognition(int microphone_pin) {
  setup_check_values();
  setup_microphone_pin(microphone_pin);
  setup_samples();
  setup_waves();
  setup_timer2_frequency();
}

int microphone_pin;

// http://arduino.cc/en/Reference/AnalogRead
// It takes about 100 microseconds (0.0001 s) to read an analog input, so the maximum reading rate is about 10,000 times a second. 
//   5 * 5 * 5 * 5 * 2 * 5 = 6250
const int sample_frequency       = 8000; //Hz max 8000Hz
const int samples_per_wave_cycle = 20;  // determines the frequency
const int number_of_samples      = 300; // used to determine the volume

const int wave_frequency         = sample_frequency / samples_per_wave_cycle;  //Hz
int samples[number_of_samples];

long sum_sinus = 0;
long sum_cosinus = 0;

int sinus_wave[samples_per_wave_cycle];
int cosinus_wave[samples_per_wave_cycle];

// for interrupt sampling
int sample_index = 0;
volatile boolean recording_samples = false;

void print_samples() {
  Serial.print("[");
  for (int i = 0; i < number_of_samples; i ++) {
    Serial.print(samples[i]);
    Serial.print(", ");
    if ((i + 1) % 26 == 0) {
      Serial.print("\n");
    }
  }
  Serial.println("]");
}

void setup_timer2_frequency(){
  // copied from sound_generator.ino
  //http://www.instructables.com/id/Arduino-Timer-Interrupts/

  cli();//stop interrupts

  //set timer2 interrupt at sample_frequency
    TCCR2A = 0;// set entire TCCR2A register to 0
    TCCR2B = 0;// same for TCCR2B
    TCNT2  = 0;//initialize counter value to 0
    // set compare match register for 8khz increments
    OCR2A = 249;// = (16*10^6) / (8000*8) - 1 (must be <256)
    // turn on CTC mode
    TCCR2A |= (1 << WGM21);
    // Set CS21 bit for 8 prescaler
    TCCR2B |= (1 << CS21);   
    // enable timer compare interrupt
    TIMSK2 |= (1 << OCIE2A);  
  
  sei();//allow interrupts
}

ISR(TIMER2_COMPA_vect){//timer2 interrupt at sample_frequency
  if (recording_samples) {
    if (sample_index >= number_of_samples) {
      // stop sampling
      sample_index = 0;
      recording_samples = false;
    } else {
      // sampling
      samples[sample_index] = analogRead(microphone_pin);
      sample_index ++;
    }
  } 

}

void setup_samples() {
  for (int sample_number = 0; sample_number < number_of_samples; ++sample_number) {
    samples[sample_number] = 0;
  }
  recording_samples = false;
}

void setup_waves() {
  for (int i = 0; i < samples_per_wave_cycle; ++i) {
    sinus_wave[i]   = int(sin(i * PI * 2 / samples_per_wave_cycle) * 127);
    cosinus_wave[i] = int(cos(i * PI * 2 / samples_per_wave_cycle) * 127);
  }
}

int get_frequency() {
  return wave_frequency;
}

void record_samples() {
  while (recording_samples) {};
  recording_samples = true;
  while (recording_samples) {};
}

long compute_squared_volume() {
  // 8 bit sine_wave
  // 10 bit analogRead
  // 9 bit number_of_samples
  // == 27 bit sum_sinus
  // => shift by 12 bit to get 15 bit sum_sinus
  // => 30 bit sum_sinus squared
  // => 31 bit sum_sinus squared + sum_cosinus squared
  long sin_value = sum_sinus / 2048;
  long cos_value = sum_cosinus / 2048;
  return sin_value * sin_value + cos_value * cos_value;
}

void convolve_wave() {
  sum_sinus   = 0;
  sum_cosinus = 0;
  long sum_of_samples = 0;
  for (int sample_index = 0; sample_index < number_of_samples; sample_index++) {
    sum_of_samples += samples[sample_index];
  }
  int average_sample = sum_of_samples / number_of_samples;
  for (int sample_index = 0;
       sample_index < number_of_samples;
       sample_index++) 
  {
    int wave_index = sample_index % samples_per_wave_cycle;
    sum_sinus   += long(samples[sample_index] - average_sample) * long(sinus_wave[wave_index]);
    sum_cosinus += long(samples[sample_index] - average_sample) * long(cosinus_wave[wave_index]);
  }
}

long get_volume_squared() {
  record_samples();
  convolve_wave();
  return compute_squared_volume();
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
    if (sizeof(long) < 4) {
      Serial.println("datatype long should have 4 bytes at least!");
    }
  }
}



