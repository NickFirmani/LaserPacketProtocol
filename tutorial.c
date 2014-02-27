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
	flipper(1);
}
