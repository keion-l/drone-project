// Based off BMP180 datasheet and sparkfuns library https://github.com/sparkfun/BMP180_Breakout_Arduino_Library/blob/master/src/SFE_BMP180.h
// Code structuring is also based off the MMA8452Q code as well for consistency
#ifndef Class_BMP180_h
#define Class_BMP180_h

#include <Arduino.h>
#include <Wire.h>

enum BMP180_Register 
{
  BMP180_ADDR = 0x77,
  REG_CONTROL = 0xF4,
  REG_RESULT = 0xF6,
  TEMPERATURE = 0x2E,
  PRESSURE_OSS_0 = 20x34,
  PRESSURE_OSS_1 = 0x74,
  PRESSURE_OSS_2 = 0xB4,
  PRESSURE_OSS_3 = 0xF4
};

////////////////////////////////
// BMP180 Class Declaration //
////////////////////////////////
class BMP180
{
  public:
    BMP180(byte addr = BMP180_DEFAULT_ADDRESS); // Constructor


    bool begin(TwoWire &wirePort = Wire, uint8_t deviceAddress = BMP180_DEFAULT_ADDRESS);

    char startTemperature(void);
    char getTemperature(double &T);

    char startPressure(char oversampling);
    char getPressure(double &P, double &T);

    double getSealevel(double P, double A);
    double getAltitude(double P, double P0);

    char getError(void);
    

  private:
    TwoWire *_i2cPort = NULL; //The generic connection to user's chosen I2C hardware
    uint8_t _deviceAddress;   //Keeps track of I2C address. setI2CAddress changes this.
    char readInt(char address, int16_t &value);
    char readUInt(char address, uint16_t &value);

    char readBytes(unsigned char *values, char length);
    char writeBytes(unsigned char *values, char length);
          
    int16_t AC1,AC2,AC3,VB1,VB2,MB,MC,MD;
    uint16_t AC4,AC5,AC6; 
    double c5,c6,mc,md,x0,x1,x2,y0,y1,y2,p0,p1,p2;
    char _error;
};

#endif