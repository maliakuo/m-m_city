unsigned char val = 0;

void setup() { 
  Serial.begin(9600);
  pinMode(18, OUTPUT); // use one of the ~ pwm pins!
} 

void loop() {
  if (Serial.available()) {
    val = Serial.read();
    analogWrite(18, val);
  }
}