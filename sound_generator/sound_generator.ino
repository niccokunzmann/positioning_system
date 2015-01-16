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
  OCR2A = 60;// = 16000000 / (32768 * 8) - 1 (must be <256)
  // turn on CTC mode
  TCCR2A |= (1 << WGM12);
  // Set CS10 bits for 8 prescaler
  TCCR2B |= (1 << CS10);  
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE1A);
  sei();//allow interrupts
}

const int low_frequency_pin = 9;
const int middle_frequency_pin = 9;
const int high_frequency_pin = 9;

//const int sample_frequency = 256;
//const int high_frequency = 5; // how many times it
//const int middle_frequency = 4; // how many times it
//const int low_frequency = 3; // how many times it fits into sample_frequency

word frequency_counter = 0;

void setup_speaker() {
  pinMode(low_frequency_pin, OUTPUT);
  pinMode(middle_frequency_pin, OUTPUT);
  pinMode(high_frequency_pin, OUTPUT);
}

ISR(TIMER2_COMPA_vect){//timer2 interrupt 33333Hz toggles sound pins
  switch (frequency_counter) {
    case 0:
      digitalWrite(low_frequency_pin, LOW);
      break;
    case 43:
      digitalWrite(low_frequency_pin, HIGH);
      break;
    case 85:
      digitalWrite(low_frequency_pin, LOW);
      break;
    case 128:
      digitalWrite(low_frequency_pin, HIGH);
      break;
    case 171:
      digitalWrite(low_frequency_pin, LOW);
      break;
    case 213:
      digitalWrite(low_frequency_pin, HIGH);
      break;
    case 256:
      digitalWrite(low_frequency_pin, LOW);
      break;
    case 299:
      digitalWrite(low_frequency_pin, HIGH);
      break;
    case 341:
      digitalWrite(low_frequency_pin, LOW);
      break;
    case 384:
      digitalWrite(low_frequency_pin, HIGH);
      break;
    case 427:
      digitalWrite(low_frequency_pin, LOW);
      break;
    case 469:
      digitalWrite(low_frequency_pin, HIGH);
      break;
    case 512:
      digitalWrite(low_frequency_pin, LOW);
      digitalWrite(middle_frequency_pin, LOW);
      break;
    case 544:
      digitalWrite(middle_frequency_pin, HIGH);
      break;
    case 576:
      digitalWrite(middle_frequency_pin, LOW);
      break;
    case 608:
      digitalWrite(middle_frequency_pin, HIGH);
      break;
    case 640:
      digitalWrite(middle_frequency_pin, LOW);
      break;
    case 672:
      digitalWrite(middle_frequency_pin, HIGH);
      break;
    case 704:
      digitalWrite(middle_frequency_pin, LOW);
      break;
    case 736:
      digitalWrite(middle_frequency_pin, HIGH);
      break;
    case 768:
      digitalWrite(middle_frequency_pin, LOW);
      break;
    case 800:
      digitalWrite(middle_frequency_pin, HIGH);
      break;
    case 832:
      digitalWrite(middle_frequency_pin, LOW);
      break;
    case 864:
      digitalWrite(middle_frequency_pin, HIGH);
      break;
    case 896:
      digitalWrite(middle_frequency_pin, LOW);
      break;
    case 928:
      digitalWrite(middle_frequency_pin, HIGH);
      break;
    case 960:
      digitalWrite(middle_frequency_pin, LOW);
      break;
    case 992:
      digitalWrite(middle_frequency_pin, HIGH);
      break;
    case 1024:
      digitalWrite(high_frequency_pin, LOW);
      digitalWrite(middle_frequency_pin, LOW);
      break;
    case 1050:
      digitalWrite(high_frequency_pin, HIGH);
      break;
    case 1075:
      digitalWrite(high_frequency_pin, LOW);
      break;
    case 1101:
      digitalWrite(high_frequency_pin, HIGH);
      break;
    case 1126:
      digitalWrite(high_frequency_pin, LOW);
      break;
    case 1152:
      digitalWrite(high_frequency_pin, HIGH);
      break;
    case 1178:
      digitalWrite(high_frequency_pin, LOW);
      break;
    case 1203:
      digitalWrite(high_frequency_pin, HIGH);
      break;
    case 1229:
      digitalWrite(high_frequency_pin, LOW);
      break;
    case 1254:
      digitalWrite(high_frequency_pin, HIGH);
      break;
    case 1280:
      digitalWrite(high_frequency_pin, LOW);
      break;
    case 1306:
      digitalWrite(high_frequency_pin, HIGH);
      break;
    case 1331:
      digitalWrite(high_frequency_pin, LOW);
      break;
    case 1357:
      digitalWrite(high_frequency_pin, HIGH);
      break;
    case 1382:
      digitalWrite(high_frequency_pin, LOW);
      break;
    case 1408:
      digitalWrite(high_frequency_pin, HIGH);
      break;
    case 1434:
      digitalWrite(high_frequency_pin, LOW);
      break;
    case 1459:
      digitalWrite(high_frequency_pin, HIGH);
      break;
    case 1485:
      digitalWrite(high_frequency_pin, LOW);
      break;
    case 1510:
      digitalWrite(high_frequency_pin, HIGH);
      break;
    case 1536:
      digitalWrite(high_frequency_pin, LOW);
      break;
  }
  ++frequency_counter;
  frequency_counter%= 1792;
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
