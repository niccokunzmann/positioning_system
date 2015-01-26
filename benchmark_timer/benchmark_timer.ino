
void setup_timer2_frequency(){
  // copied from sound_generator.ino
  //http://www.instructables.com/id/Arduino-Timer-Interrupts/

  cli();//stop interrupts

  if (false) {
    //set timer2 interrupt at sample_frequency
    TCCR2A = 0;// set entire TCCR1A register to 0
    TCCR2B = 0;// same for TCCR1B
    TCNT2  = 0;//initialize counter value to 0
    // set compare match register for sample_frequency increments
    OCR2A = 4;// = 16000000 / (sample_frequency * 256) - 1 (must be <256)
    // turn on CTC mode
    TCCR2A |= (1 << WGM12);
    // Set CS12 bits for 256 prescaler
    TCCR2B |= (1 << CS12);  
    // enable timer compare interrupt
    TIMSK2 |= (1 << OCIE1A);
  }
  
  if (true) {
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
  }
  sei();//allow interrupts
}

volatile int value;
volatile int counter;

volatile boolean interrupt_reading;

ISR(TIMER2_COMPA_vect){//timer2 interrupt at sample_frequency
  if (interrupt_reading) {
    value = analogRead(A0);
  }
  counter ++;
}


void setup () {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  interrupt_reading = false;
  setup_timer2_frequency();
}

void loop() {
  interrupt_reading = !interrupt_reading;
  int x;
  counter = 0;
  delay(1000);
  x = counter;
  Serial.print("Interrupts per second: ");
  Serial.print(x);
  if (interrupt_reading) {
    Serial.print(" with analogRead(A0) ");
    Serial.print(value);
  }
  Serial.println();
}
