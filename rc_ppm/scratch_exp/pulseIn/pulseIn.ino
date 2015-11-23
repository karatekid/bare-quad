int pin = 2;
int pins[] = {10,11,12,13};
int num_pins = 4;
unsigned long duration;

void setup()
{
  for(int i = 0; i < num_pins; ++i) {
    pinMode(pins[i], INPUT);
  }
  Serial.begin(9600);
  Serial.println("RH\tLV\tRV\tLH");
}

void loop()
{
  bool first = true;
  for(int i = 0; i< num_pins; ++i) {
    if(!first) {
      Serial.print('\t');
    }
    Serial.print(pulseIn(pins[i], HIGH));  
    first = false;
  }
  Serial.print('\n');
}
