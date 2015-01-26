





void setup() {
  tone(8, 400);
  pinMode(9, OUTPUT);
  //analogWrite(9, 100);
}

void loop() {
  int d = 100;
  digitalWrite(9, HIGH);
  delay(d);
  digitalWrite(9, LOW);
  delay(d);
}
