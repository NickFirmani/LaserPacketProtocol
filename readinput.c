#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <math.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdint.h>
#include <curl/curl.h>


/*
ser <- hardware.pin1;
laser.configure(DIGITAL_OUT);
status <- hardware.pin9;
status.configure(DIGITAL_OUT);

led <- hardware.pin5;
b <- blob();
*/



decode() {
  int nextTime = millis() + 50;
  int x = 0;
  int* messageLength[8];
  int count=0;
  int clock = 100;

  unsigned int nextTime;
  short flip;

  if (wiringPiSetup () == -1)
   {fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
   return 1 ;
   }

  nextTime = millis() + TIME_DELAY;
  int x = 0;
  for (;x<400;x++){
    while (millis() < nextTime) {
    }
    flip = !flip;
    flipper(flip);
    nextTime += TIME_DELAY;
  }
}









function openled() {
    led.configure(DIGITAL_OUT);
    led.write(1);
    led.configure(ANALOG_IN);
    imp.sleep(0.00001); //call led.read for val SAMPLE RATE?!;;;
    local val = led.read();
    if (val > 0) {
        return 0;
        status.write(1);
    } else {
        return 1;
    }
}

function scan() {
    local eightbits = 0;
    for (local k = 8; k > 0; k -= 1) {
        eightbits += math.pow(10, k) * openled();
    }
    b.writen('f', eightbits);
    eightbits = 0;
    if (b.len() > 2048) {
        agent.send("receiveLZR", b);
    }
}

function waitforone() {
    while (openled() != 1) {}
    server.log("STATUS");
    status.write(1);
    scan();
}

//-------------------------------------------///------------------///-----------
//THIS FUNCTION SENDS OUT A GODDANG LAZOR
function sendString(stringtosend) {
    foreach(val in stringtosend) {
        local correct = val.tointeger() - 48;
        laser.write(correct);
        local tStart = hardware.micros();
        while (hardware.micros() - tStart < 15000){} //
    }
    laser.write(0);
    //waitforone();
}
agent.on("sendLZR", sendString);
