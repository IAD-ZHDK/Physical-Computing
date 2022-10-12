
#define INPUT_PIN A0
const int MAX_ANALOG_INPUT = 1023;
const int DELAY_MS = 5;

int prevValue = -1;
int state = 0;
float sizeFrac;

void setup() {
  Serial.begin(9600); // set baud rate to 9600
}

void loop() {

  // Get the new analog value
  int currentVal = analogRead(INPUT_PIN);
  float prevSizeFrac = sizeFrac;

  // If the analog value has changed, assign it to sizeFrac
  if (prevValue != currentVal) {
    sizeFrac = currentVal / (float) MAX_ANALOG_INPUT;
  }
  
  if (prevSizeFrac != sizeFrac ) {
    Serial.print(sizeFrac, 4); // 4 decimal point precision
  }

  prevValue = currentVal;
}
