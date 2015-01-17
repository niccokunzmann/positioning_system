/*

Timer interrupt scaling
  http://www.instructables.com/id/Arduino-Timer-Interrupts/

"Die Schallgeschwindigkeit in trockener Luft von 20 °C ist 343 m/s.[1] Das entspricht 1235 km/h." - https://de.wikipedia.org/wiki/Schallgeschwindigkeit

Bei 0.335m Abstand macht das 1024Hz fuer die maximale Frequenz.

Wenn wir die Frequenz 512Hz verwenden, dann können wir noch 768Hz und 640 Hz verwenden, da diese sich gut finden lassen.

kgV(512Hz, 640Hz) = 2560Hz ist die minimale samplefrequenz 
ggT(512Hz, 640Hz) = 128Hz ist die Periode der fft.
To collect 256 samples in 128Hz we need a frequency of 32768Hz = 32kHz

Example fft use http://wiki.openmusiclabs.com/wiki/Example

Bei 31250Hz Sampling rate ist 

122Hz die Minimale Frequenz
977Hz die Maximale Frequenz (1/32 der Sampling Frequenz)

*/



void setup_timer2_frequency(){
  //http://www.instructables.com/id/Arduino-Timer-Interrupts/

  cli();//stop interrupts

  //set timer2 interrupt at 31250Hz
  TCCR2A = 0;// set entire TCCR1A register to 0
  TCCR2B = 0;// same for TCCR1B
  TCNT2  = 0;//initialize counter value to 0
  // set compare match register for 33333hz increments
  OCR2A = 243 /*60*/;// = 16000000 / (32768 * 8) - 1 (must be <256)
  // turn on CTC mode
  TCCR2A |= (1 << WGM12);
  // Set CS10 bits for 8 prescaler
  TCCR2B |= (1 << CS10);  
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE1A);
  sei();//allow interrupts
}


//const int sample_frequency = 256;
//const int high_frequency = 5; // how many times it
//const int middle_frequency = 4; // how many times it
//const int low_frequency = 3; // how many times it fits into sample_frequency

word frequency_counter = 0;

void setup_speaker() {
  pinMode( 8, OUTPUT);
  pinMode( 9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

ISR(TIMER2_COMPA_vect){//timer2 interrupt 33333Hz toggles sound pins
  byte value = (frequency_counter & 0b01111100) >> 2;
  byte sign = value & 1;
  value >>= 1;
  if (sign) {
    value = ~value;
  }
  if (value & 0b1000) {
    digitalWrite(11, HIGH);
  } else {
    digitalWrite(11, LOW);
  }
  if (value & 0b0100) {
    digitalWrite(10, HIGH);
  } else {
    digitalWrite(10, LOW);
  }
  if (value & 0b0010) {
    digitalWrite(9, HIGH);
  } else {
    digitalWrite(9, LOW);
  }
  if (value & 0b0001) {
    digitalWrite(8, HIGH);
  } else {
    digitalWrite(8, LOW);
  }
  ++frequency_counter;
  frequency_counter%= 256;
}

void setup() {
  setup_speaker();
  setup_timer2_frequency();
  Serial.begin(9600); 
  while (!Serial) {};
  Serial.println("Sound generation"); 
}

void loop() {
  Serial.println(frequency_counter);
}
