
#define NUM_VALUES 2
#define OUTPUT_PIN A0

int incomingValues[NUM_VALUES];
const int DELAY_MS = 10;

void setup() {
  Serial.begin(9600);
  pinMode(OUTPUT_PIN, OUTPUT);
}

void loop() {

  // Check to see if there is any incoming serial data
  if(Serial.available() > 0){
    // read string until the end of the line
    String rcvdSerialData = Serial.readStringUntil('\n'); 
    analogWrite(OUTPUT_PIN, rcvdSerialData.toInt());
    }   
    delay(DELAY_MS);

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
