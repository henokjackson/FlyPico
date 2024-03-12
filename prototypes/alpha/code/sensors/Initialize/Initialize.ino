#include <I2Cdev.h>
#include <Adafruit_BMP085.h>
#include <MPU6050.h>
#include <HMC5883L_Simple.h>
#include <Wire.h>

//Creating Module Control Objects
MPU6050 IMU;
Adafruit_BMP085 Barometer;
HMC5883L_Simple Magnetometer;


int CommunicationInitialize()
{
  Serial.println("[Info] : Initializing Serial Communication ...");
  Serial.begin(9600);
  Wire.begin();
  return 0;
}

int BarometerInitialize()
{
  Serial.println("[Info] : Initializing Barometer (BMP085) ...");
  if(!Barometer.begin())
  {
    Serial.println("[Error] : Unable To Connect to Barometer (BMP085)!");
    return -1;
  }
  else
  {
    Serial.println("[Success] : Barometer (BMP085) Connected.");
    return 0;
  }
}

int IMUInitialize()
{
  Serial.println("[Info] : Connecting to IMU (MPU6050) ...");
  IMU.initialize();
  if(!IMU.testConnection())
  {
    Serial.println("[Error] : Unable To Connect to IMU (MPU6050)!");
    return -1;
  }
  else
  {
    Serial.println("[Success] : IMU (MPU6050) Connected.");
    return 0;
  }
  IMU.setI2CBypassEnabled(true);
}

int MagnetometerInitialize()
{
  Serial.println("[Info] : Initializing Magnetometer (HMC5883L) ...");

  //Set Declination To Kochi - -1° 46' W
  Magnetometer.SetDeclination(-1, 46, 'W');
  Serial.println("[Info] : Setting Declination to  -1°, 46', W (Location : Kochi) ...");

  //Measure Continously
  Magnetometer.SetSamplingMode(COMPASS_CONTINUOUS);
  Serial.println("[Info] : Enabled Continous Sampling.");

  //Set Scale - 130 (Default)
  Magnetometer.SetScale(COMPASS_SCALE_190);
  Serial.println("[Info] : Setting Scale to 190x ...");

  //Set Orientation - X Axis Facing North , Mounted Horizontally.
  Magnetometer.SetOrientation(COMPASS_HORIZONTAL_X_NORTH);
  Serial.println("[Info] : Setting Horizontal Orientaion (X Axis to North) ...");

  return 0;
}

void Setup()
{
  Serial.println("Log");

  //Initialzing Serial Communication Channels
  CommunicationInitialize();

  //Initializing Barometer - BMP085
  BarometerInitialize();

  //Initializing IMU - MPU6050
  IMUInitialize();

  //Initializing Magnetometer - HMC5883L
  MagnetometerInitialize();
}
