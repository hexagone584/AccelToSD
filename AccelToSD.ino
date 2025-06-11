#include <SD.h>
#include <Adafruit_MPU6050.h>

File myFile;
Adafruit_MPU6050 mpu;
String fileName = "Jackie.txt";

void setup() {
  Serial.begin(9600);  //sets up the baud(?) rate to 9600

  //checks if everything seems right
  while (!Serial);
  if (!SD.begin()) {
    Serial.println("Something about SD isn't right");
    while (true);
  }
  if (!mpu.begin()) {
    Serial.println("Something about Accelerometer isn't right");
    while (true);
  }

  //writes the header
  myFile = SD.open(fileName, FILE_WRITE);
  myFile.print("Acceleration (m/s^2):\tX\tY\tZ\t Gyro (rad/s):\tX\tY\tZ\tTemp (degC):\n");
  myFile.close();
}

void loop() {
  myFile = SD.open(fileName, FILE_WRITE);
  sensors_event_t accel, gyro, temp;
  mpu.getEvent(&accel, &gyro, &temp);

  myFile.print("\t\t\t");
  myFile.print(accel.acceleration.x);
  myFile.print("\t ");
  myFile.print(accel.acceleration.y);
  myFile.print("\t ");
  myFile.print(accel.acceleration.z);
  myFile.print("\t\t\t ");

  myFile.print(gyro.gyro.x);
  myFile.print("\t ");
  myFile.print(gyro.gyro.y);
  myFile.print("\t ");
  myFile.print(gyro.gyro.z);
  myFile.print("\t ");
  myFile.println(temp.temperature);

  myFile.close();
  Serial.println("printing!");
  delay(500);

  //I did something wacky
}
