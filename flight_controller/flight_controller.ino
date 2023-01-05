
/*
  Library for the MMA8452Q
  By: Jim Lindblom and Andrea DeVore
  SparkFun Electronics

  Do you like this library? Help support SparkFun. Buy a board!
  https://www.sparkfun.com/products/14587

  This sketch uses the SparkFun_MMA8452Q library to initialize
  the accelerometer and stream calcuated x, y, z, acceleration
  values from it (in g units).

  Hardware hookup:
  Arduino --------------- MMA8452Q Breakout
    3.3V  ---------------     3.3V
    GND   ---------------     GND
  SDA (A4) --\/330 Ohm\/--    SDA
  SCL (A5) --\/330 Ohm\/--    SCL

  The MMA8452Q is a 3.3V max sensor, so you'll need to do some
  level-shifting between the Arduino and the breakout. Series
  resistors on the SDA and SCL lines should do the trick.

  License: This code is public domain, but if you see me
  (or any other SparkFun employee) at the local, and you've
  found our code helpful, please buy us a round (Beerware
  license).

  Distributed as is; no warrenty given.
*/

#include <Wire.h>                 // Must include Wire library for I2C
#include "Class_MMA8452Q.h"    // Click here to get the library: http://librarymanager/All#SparkFun_MMA8452Q
#include "Class_BMP180.h" 


MMA8452Q accel;          // create instance of the MMA8452 class
BMP180 barom;            //create instance of barom

// light set up

int LED_UP = 13;
int LED_DOWN = 8;
int LED_LEFT = 2;
int LED_RIGHT = 7;
int LED_FLAT = 12;

int LED_ARR [] = {
  LED_UP,
  LED_DOWN,
  LED_LEFT,
  LED_RIGHT,
  LED_FLAT
};

double baseline;  

void setup() {
  Serial.begin(9600);
  Serial.println("MMA8452Q Basic Reading Code!");
  Serial.println("BMP180 Reading height");

  pinMode(LED_UP, OUTPUT);
  pinMode(LED_DOWN, OUTPUT);

  pinMode(LED_RIGHT, OUTPUT);
  pinMode(LED_LEFT, OUTPUT);

  pinMode(LED_FLAT, OUTPUT);


  Wire.begin();

  // if (accel.begin() == false) {
  //   Serial.println("MMA8452Q not Connected. Please check connections and read the hookup guide.");
  //   while (1);
  // }

  if (barom.begin() == false) {
    Serial.println("Barometer not Connected. Please check connections and read the hookup guide.");
    while (1);
  }

  baseline = getPressure();

}

void loop() {

  // if (accel.available()) {      // Wait for new data from accelerometer
  //   // Acceleration of x, y, and z directions in g units

  //   if (accel.isUp()) {
  //     Serial.print("Tilted Up");
  //     digitalWrite(LED_UP, HIGH);
  //   } else {
  //       digitalWrite(LED_UP, LOW);
  //   }

  //   if (accel.isDown()) {
  //     Serial.print("Tilted Down");
  //     digitalWrite(LED_DOWN, HIGH);
  //   } else {
  //     digitalWrite(LED_DOWN, LOW);
  //   }

  //   if (accel.isLeft()) {
  //     Serial.print("Tilted Left");
  //     digitalWrite(LED_LEFT, HIGH);
  //   } else {
  //     digitalWrite(LED_LEFT, LOW);
  //   }


  //   if (accel.isRight()) {
  //     Serial.print("Tilted Right");
      
  //     digitalWrite(LED_RIGHT, HIGH);
  //   } else {
  //     digitalWrite(LED_RIGHT, LOW);
  //   }

  //   if (accel.isFlat()) {
  //     Serial.print("Flat");
  //     digitalWrite(LED_FLAT, HIGH);
  //   } else {
  //     digitalWrite(LED_FLAT, LOW);
  //   }

    
  // }

  double a,P;

  P = getPressure();
  a = barom.getAltitude(P,baseline);

  Serial.print(" Temp: ");
  Serial.print(barom.getAltitude(P,baseline));

  Serial.println();
}

double getPressure()
{
  char status;
  double T,P,p0,a;

  status = barom.startTemperature();
  if (status != 0)
  {

    delay(status);

    status = barom.getTemperature(T);
    if (status != 0)
    {
      status = barom.startPressure(3);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);

        // Retrieve the completed pressure measurement:
        // Note that the measurement is stored in the variable P.
        // Use '&P' to provide the address of P.
        // Note also that the function requires the previous temperature measurement (T).
        // (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
        // Function returns 1 if successful, 0 if failure.

        status = barom.getPressure(P,T);

        if (status != 0)
        {
          return(P);
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");
}

