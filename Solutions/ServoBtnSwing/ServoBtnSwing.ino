/* Sweep
  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 8 Nov 2013
  by Scott Fitzgerald
  https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/

#include <Servo.h>
#define btnPin 7

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int btnStateOld = 0;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(btnPin, INPUT_PULLUP);
}

void loop() {
  int btnState = digitalRead(btnPin);

  //  if (btnState == LOW && btnStateOld == HIGH) {
  //    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
  //      // in steps of 1 degree
  //      myservo.write(pos);              // tell servo to go to position in variable 'pos'
  //      delay(2);                       // waits 15 ms for the servo to reach the position
  //    }
  //  } else if (btnState == HIGH && btnStateOld == LOW) {
  //    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
  //      myservo.write(pos);              // tell servo to go to position in variable 'pos'
  //      delay(2);                       // waits 15 ms for the servo to reach the position
  //    }
  //  }

  if (btnState == LOW) {
    if (pos <= 180) {
      pos++;
      myservo.write(pos);
    }
  } else {
    if (pos >= 0) {
      pos--;
      myservo.write(pos);
    }
  }
  
  delay(2);
  //btnStateOld = btnState;
}
