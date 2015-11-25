int pins[] = {A8,A9,A10,A11};
unsigned long rc_values[] = {0, 0, 0, 0};
unsigned long rc_last_time[] = {0, 0, 0, 0};
bool rc_reading[] = {false, false, false, false};
int num_pins = 4;
byte read_val = 0;

// Interrupt handler
ISR(PCINT2_vect) { // Pin change for A8 --> A11
    for(int i = 0; i < num_pins; ++i) {
        bool high = digitalRead(pins[i]);
        if(!rc_reading[i] && high) {
            rc_reading[i] = true;
            rc_last_time[i] = micros();
        } else if(rc_reading[i] && !high) {
            rc_reading[i] = false;
            rc_values[i] = micros() - rc_last_time[i];  // TODO: impl. wraparound
        }
    }
    byte val = PORTK;
    read_val = val;
}

void pciSetup() {
    byte pin = A8;
    // Clear any outstanding interrupt
    PCIFR |= bit(digitalPinToPCICRbit(pin));
    // Enable interrupt for the group
    PCICR |= bit(digitalPinToPCICRbit(pin));
    // Enable pin
    *digitalPinToPCMSK(pin) |= 0x0F; //bit(digitalPinToPCMSKbit(pin));
}

void setup()
{
  for(int i = 0; i < num_pins; ++i) {
    pinMode(pins[i], INPUT);
  }
  pciSetup();
  Serial.begin(9600);
}

void loop()
{
  delay(100);
  bool first = true;
  for(int i = 0; i < num_pins; ++i) {
    if(!first) {
      Serial.print('\t');
    }
    Serial.print(rc_values[i]);  
    first = false;
  }
  Serial.print('\n');
}
