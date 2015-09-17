#include <config.h>
#include <logger.h>
#include <logstuff.h>

Logger *l;
void setup() {
  // put your setup code here, to run once:
  l = Logger::getLogger();
  pinMode(13, OUTPUT);
}

void stuff() {
  digitalWrite(13, LOW);
  delay(1000);
  digitalWrite(13, HIGH);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  l->functionTime(INFO, SS_MAIN, stuff());
  l->print(DEBUG, SS_MAIN, "Hello");
}
