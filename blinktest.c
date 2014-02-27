#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <math.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#define TIME_DELAY 35

void flipper(short var) {
    digitalWrite(7, var);
}

int main(void) {
   unsigned int nextTime;
   short flip;

   if (wiringPiSetup () == -1)
    {
      fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
      return 1 ;
    }

    nextTime = millis() + TIME_DELAY;
    int x = 0;
    for (;x<400;x++){
      while (millis() < nextTime) {
      }
      flip = !flip;
      flipper(flip);
      nextTime+=TIME_DELAY;
    }
}
