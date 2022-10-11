
#define NUM_VALUES 5
#define OUTPUT_PIN A0

int incomingValues[NUM_VALUES];
const int DELAY_MS = 500;

void setup() {
  Serial.begin(9600);
  pinMode(OUTPUT_PIN, OUTPUT);
}

void loop() {

  // Check to see if there is any incoming serial data
  if (Serial.available() > 0) {
    // read string until the end of the line

    //write to LED
  }
  delay(DELAY_MS);

}
