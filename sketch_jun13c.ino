#include <Servo.h>

Servo myServo;
int servoPin = 4;
int pulse = 1500;

void setup() {
  // put your setup code here, to run once:
  pinMode(servoPin, OUTPUT);
  Serial.begin(9600); 
  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(servoPin, HIGH);
  delayMicroseconds(pulse);
  digitalWrite(servoPin, LOW);
  delay(2000);
}
