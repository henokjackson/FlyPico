#include <I2Cdev.h>
#include <Adafruit_BMP085.h>
#include <MPU6050.h>
#include <HMC5883L_Simple.h>

//Creating Module Control Objects
MPU6050 IMU;
Adafruit_BMP085 Barometer;
HMC5883L_Simple Magnetometer;

//IMU Variables
int16_t aX, aY, aZ;
int16_t gX, gY, gZ;

enum InitResult
{
  Failed,
  Success
};

InitResult comm_Init()
{
  Serial.println("[Info] : Initializing Serial Communication ...");
  Serial.begin(9600);
  Wire.begin();
}

InitResult barometer_Init()
{
  Serial.println("[Info] : Initializing Barometer (BMP085) ...");
  if(!Barometer.begin())
  {
    Serial.println("[Error] : Unable To Connect to Barometer (BMP085)!");
    Serial.println("[Info] : Exiting...");
    return InitResult.Failed;
  }
  else
  {
    Serial.println("[Success] : Barometer (BMP085) Connected.");
    return InitResult.Success;
  }
}

InitResult IMU_Init()
{
  Serial.println("[Info] : Connecting to IMU (MPU6050) ...");
  IMU.initialize();
  if(!IMU.testConnection())
  {
    Serial.println("[Error] : Unable To Connect to IMU (MPU6050)!");
    Serial.println("[Info] : Failed...");
    return InitResult.Failed;
  }
  else
  {
    Serial.println("[Success] : IMU (MPU6050) Connected.");
    return InitResult.Success;
  }
  IMU.setI2CBypassEnabled(true);
}

InitResult magnetometer_init()
{
  try
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
  }
  catch(Exception ex)
  {
    return InirResult.Failed;
  }
}

void setup()
{
  Serial.println("Log : ");

  //Initialzing Serial Communication Channels
  comm_Init();

  //Initializing Barometer - BMP085
  barometer_Init();

  //Initializing IMU - MPU6050
  IMU_Init();

  //Initializing Magnetometer - HMC5883L
  magnetometer_Init();


void loop()
{
  
}
