
#define OUTPUT_PIN 13
#define MAX_VALUES 5; //maximum amount of values received

const byte numChars = 32; 
char receivedChars[numChars];
char tempChars[numChars];        // temporary array for use when parsing

// variables to hold the parsed data
boolean newData = false;

//============

void setup() {
    Serial.begin(9600);
    pinMode(OUTPUT_PIN, OUTPUT);
    
}

//============

void loop() {
    recvWithStartEndMarkers();
    if (newData == true) {
        strcpy(tempChars, receivedChars);
            // this temporary copy is necessary to protect the original data
            //   because strtok() used in parseData() replaces the commas with \0
        parseData();
        newData = false;
    }
}


// Function for splitting incoming array values

//void split(String inputString, int returnData[], int numOfValues)
//{
//  int index = 0;
//  int lastPos = 0;
//
//  for (int i = 0; i < inputString.length(); i++)
//  {
//    if (inputString.charAt(i) == ',' && index < numOfValues)
//    {
//      String tempStr = inputString.substring(lastPos, i);
//      Serial.println(tempStr);
//      returnData[index] = tempStr.toInt();
//      index++;
//      lastPos = i + 1;
//    }
//  }

//============
// Code from https://forum.arduino.cc/t/serial-input-basics-updated/382007

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char endMarker = '>';
    char startMarker = '<';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();
   
        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

//============

void parseData() {      // split the data into its parts
    char * strtokIndx;

//
//    strtokIndx = strtok(tempChars,",");      // get the first part - the string
//    strcpy(myString, strtokIndx); // copy it to messageFromPC
//    Serial.println(myString); //print String
 
//    myInteger = atoi(strtokIndx);     // convert this part to an integer
//    Serial.println(myInteger); //print Integer

//    myFloat = atof(strtokIndx);     // convert this part to a float
//    Serial.println(myFloat); //print Float

    strtokIndx = strtok(tempChars,",");
    int q = atoi(strtokIndx);
    
    if (q == 0 || q == 1) {
      digitalWrite(OUTPUT_PIN, q);
    }
    
    strtokIndx = strtok(NULL, ",");
    int w = atoi(strtokIndx);

    strtokIndx = strtok(NULL, ",");
    int e= atoi(strtokIndx);

    strtokIndx = strtok(NULL, ",");
    int r= atoi(strtokIndx);

    strtokIndx = strtok(NULL, ",");
    int t= atoi(strtokIndx);


    Serial.println(q);
    Serial.println(w);
    Serial.println(e);
    Serial.println(r);
    Serial.println(t);
    
     
}

//Uncomment this if you just want to receive one value


//void recvWithEndMarker() {
//    static byte ndx = 0;
//    char endMarker = '\n';
//    char rc;
//    
//    if (Serial.available() > 0) {
//        rc = Serial.read();
//
//        if (rc != endMarker) {
//            receivedChars[ndx] = rc;
//            ndx++;
//            if (ndx >= numChars) {
//                ndx = numChars - 1;
//            }
//        }
//        else {
//            receivedChars[ndx] = '\0'; // terminate the string
//            ndx = 0;
//            newData = true;
//        }
//    }
//}
//
//void showNewNumber() {
//    if (newData == true) {
//        dataNumber = 0;             // new for this version
//        dataNumber = atoi(receivedChars);   // new for this version
//        Serial.print("Data as Number ... ");    // new for this version
//        Serial.println(dataNumber);     // new for this version
//        newData = false;
//    }
//}
