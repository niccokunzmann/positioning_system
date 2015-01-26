

void setup() {
  pinMode(A0, INPUT);
  Serial.begin(9600); 
}

void loop() {
  //tone(8, 100, 2000);
  int READS = 10000;
  int s = 0;
  int time = -millis();
  for (int i = 0; i < READS; i++) {
    s += analogRead(A0);
  }
  time += millis(); 
  Serial.print("time for ");
  Serial.print(READS);
  Serial.print(" reads: ");
  Serial.print(time);
  Serial.print("ms. Reads/second: ");
  Serial.print((double)READS * 1000 / time);
  Serial.print(" sum: ");
  Serial.println(s);
}
