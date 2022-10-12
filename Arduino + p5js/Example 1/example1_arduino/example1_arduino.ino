
#define NUM_VALUES 5
#define OUTPUT_PIN 11

int incomingValues[NUM_VALUES];
const int DELAY_MS = 100;
int inputVal; 

void setup() {
  Serial.begin(9600);
  pinMode(OUTPUT_PIN, OUTPUT);
}

void loop() {
  // Check to see if there is any incoming serial data
  if (Serial.available() > 0) {
    // read string until the endo of the line
    String rcvdSerialData = Serial.readStringUntil('\n');
    if (rcvdSerialData.startsWith("on")) {
      inputVal = 255;
    } else if (rcvdSerialData.startsWith("off")) {
      inputVal = 0;
    } else {
      split(rcvdSerialData, incomingValues, NUM_VALUES);
      for (int j = 0; j < NUM_VALUES; j++) {
        analogWrite(OUTPUT_PIN, incomingValues[j]);
        delay(DELAY_MS);
      }
    }
  }
  Serial.println(inputVal);
  analogWrite(OUTPUT_PIN, inputVal);
}



void split(String inputString, int returnData[], int numOfValues)
{
  int index = 0;
  int lastPos = 0;

  for (int i = 0; i < inputString.length(); i++)
  {
    if (inputString.charAt(i) == ',' && index < numOfValues)
    {
      String tempStr = inputString.substring(lastPos, i);
      Serial.println(tempStr);
      returnData[index] = tempStr.toInt();
      index++;
      lastPos = i + 1;
    }
  }
}

//This code would be used if receiving message is formated using start and end markers
//For simple messages this method is irrelevant, but once you want to send complex data, different types of variables, etc.
//it becomes essential to add markers

//void loop() {
//    recvWithStartEndMarkers();
//    if (newData == true) {
//        strcpy(tempChars, receivedChars);
//        parseData();
//        newData = false;
//    }
//}
//
//// Code from https://forum.arduino.cc/t/serial-input-basics-updated/382007
//
//void recvWithStartEndMarkers() {
//    static boolean recvInProgress = false;
//    static byte ndx = 0;
//    char endMarker = '>';
//    char startMarker = '<';
//    char rc;
//
//    while (Serial.available() > 0 && newData == false) {
//        rc = Serial.read();
//
//        if (recvInProgress == true) {
//            if (rc != endMarker) {
//                receivedChars[ndx] = rc;
//                ndx++;
//                if (ndx >= numChars) {
//                    ndx = numChars - 1;
//                }
//            }
//            else {
//                receivedChars[ndx] = '\0'; // terminate the string
//                recvInProgress = false;
//                ndx = 0;
//                newData = true;
//            }
//        }
//
//        else if (rc == startMarker) {
//            recvInProgress = true;
//        }
//    }
//}
//
//void parseData() {      // split the data into its parts
//    char * strtokIndx;
//
//    strtokIndx = strtok(tempChars,","); // get the first part - the string
//    int one = atoi(strtokIndx);// convert this part to an integer
//    digitalWrite(OUTPUT_PIN, one);
//    delay(100);
//    strtokIndx = strtok(NULL, ",");
//    int two = atoi(strtokIndx);
//    digitalWrite(OUTPUT_PIN, two);
//    delay(100);
//    strtokIndx = strtok(NULL, ",");
//    int three= atoi(strtokIndx);
//    digitalWrite(OUTPUT_PIN, three);
//    delay(100);
//    strtokIndx = strtok(NULL, ",");
//    int four= atoi(strtokIndx);
//    digitalWrite(OUTPUT_PIN, four);
//    delay(100);
//    strtokIndx = strtok(NULL, ",");
//    int five= atoi(strtokIndx);
//    digitalWrite(OUTPUT_PIN, five);
//    delay(100);
//}
