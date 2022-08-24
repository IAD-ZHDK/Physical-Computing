// Basic demo for accelerometer/gyro readings from Adafruit LSM6DS33
#define LEDpin 10

#include <Adafruit_LSM6DS33.h>

int delayCounter = 0;
int LEDtoggle = 0;

Adafruit_LSM6DS33 lsm6ds33;
void setup(void) {
  Serial.begin(115200);

  while (!Serial) {
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
  }
  Serial.println("Adafruit LSM6DS33 test!");

  if (!lsm6ds33.begin_I2C()) {
    // if (!lsm6ds33.begin_SPI(LSM_CS)) {
    // if (!lsm6ds33.begin_SPI(LSM_CS, LSM_SCK, LSM_MISO, LSM_MOSI)) {
    Serial.println("Failed to find LSM6DS33 chip");
    while (1) {
      delay(10);
    }
  }

  Serial.println("LSM6DS33 Found!");
  pinMode(LEDpin, OUTPUT);
  // lsm6ds33.configInt1(false, false, true); // accelerometer DRDY on INT1
  // lsm6ds33.configInt2(false, true, false); // gyro DRDY on INT2
}

void loop() {
  //  /* Get a new normalized sensor event */
  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;
  lsm6ds33.getEvent(&accel, &gyro, &temp);

  // Serial.print("\t\tTemperature ");
  // Serial.print(temp.temperature);
  // Serial.println(" deg C");

    int delayDuration = map(accel.acceleration.z, -11.0, 11.0, 50, 2000);
    delayDuration = constrain(delayDuration, 50, 2000); 

    delayCounter++; 

    if (delayCounter >= delayDuration) {
      LEDtoggle = 1 - LEDtoggle;
      delayCounter = 0;
    }

    digitalWrite(LEDpin, LEDtoggle);
   
    //delay(delayDuration);
   // digitalWrite(LEDpin, LOW);
    //delay(delayDuration);
    
  delay(10);
  /* Display the results (acceleration is measured in m/s^2) */

    Serial.print("\t\tAccel X: ");
    Serial.print(accel.acceleration.x);
    Serial.print(" \tY: ");
    Serial.print(accel.acceleration.y);
    Serial.print(" \tZ: ");
    Serial.print(accel.acceleration.z);
    Serial.println(" m/s^2 ");
 
  //delay(100);
}
