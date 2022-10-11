
#define INPUT_PIN A0
#define BUTTON_PIN 13
const int MAX_ANALOG_INPUT = 1023;
const int DELAY_MS = 5;
int MAX_COUNT = 3;

int prevValue = -1;
int lastButtonState;
int currentButtonState;
int state = 0;
float sizeFrac;
int clickCount = 0;


void setup() {
  Serial.begin(9600); // set baud rate to 9600
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  currentButtonState = digitalRead(BUTTON_PIN);
}

void loop() {

  // Get the new analog value
  int currentVal = analogRead(INPUT_PIN);
  float prevSizeFrac = sizeFrac;

  // If the analog value has changed, assign it to sizeFrac
  if (prevValue != currentVal) {
    sizeFrac = currentVal / (float) MAX_ANALOG_INPUT;
  }

  // Get button state
  currentButtonState = digitalRead(BUTTON_PIN); // read new state
  int prevState = state;

  //check the button state and increase clicks counter
  if (lastButtonState == LOW && currentButtonState != lastButtonState) {
     state =  clickCount;
     clickCount++;
    if(state >= MAX_COUNT){
      clickCount = 0;
    }
    
  }
  
 //send data to web browser over serial
  if (prevSizeFrac != sizeFrac || prevState != state) {
    Serial.print(sizeFrac, 4); // 4 decimal point precision
    Serial.print(",");
    Serial.println(state);
  }

  prevValue = currentVal;
  lastButtonState = currentButtonState;


}
