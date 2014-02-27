#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <math.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <wiringPiI2C.h>
#define TIME_DELAY 35
#define LIGHT_SENSOR_ADDRESS 0x39
#define PI_I2C_BUS_NUMBER 1

int i2c;

void flipper(short var) {
    digitalWrite(7, var);

}

void startReading(void) {
    wiringPiI2CWriteReg8(i2c, 0x80, 0x03);
}
void readSensor(void) {
    //Must read 0x8C
    //gotta read i2c.readU16
    //reverse it useing revereseByteOrder
    int out = wiringPiI2CReadReg16(i2c, 0x8C);
    fprintf(stdout, "Value: %d\r", out);
    fflush(stdout);
    
   
}

int main(void) {
   unsigned int nextTime;
   short flip;

   if (wiringPiSetup () == -1)
    {
      fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
      fflush(stdout);
      return 1;
    }
   i2c = wiringPiI2CSetup (0x39);
   if (i2c == -1)
    {
      fprintf (stdout, "Unable to start I2C wiringPi: %s\n", strerror (errno)) ;
      fflush(stdout);
      return 1;
    }

    wiringPiI2CWriteReg8(i2c, 0x80, 0x03);
    

    nextTime = millis() + TIME_DELAY+400;
    int x = 0;
    for (;x<500;x++){
      //startReading();
      flip = !flip;
      flipper(flip);
      while (millis() < nextTime) {
      }
      readSensor();
      nextTime+=TIME_DELAY;
    }
}
