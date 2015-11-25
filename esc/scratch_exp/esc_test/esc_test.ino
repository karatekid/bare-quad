#include <Servo.h>

Servo servo;

int escPin = 9;
// Used as defaults for throttle min and max
int escMin = 1000;
int escMax = 2000;

void configureESCRange() {
    servo.writeMicroseconds(escMax);
    delay(2000 + 500);
    servo.writeMicroseconds(escMin);
    delay(1000 + 500);
}

void startupESC() {
    servo.writeMicroseconds(escMin);
    delay(2000 + 500);
}

void setup() {
    servo.attach(escPin);
    startupESC();
}

void loop() {
  // put your main code here, to run repeatedly:
  servo.writeMicroseconds(1500);
  delay(2000);
  servo.writeMicroseconds(escMin);
  delay(2000);
}
