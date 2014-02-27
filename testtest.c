#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <math.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdint.h>
//#include <~/laserpi.c>

/*char* concatenateStrings(char* stringEncode, char* otherString, int encodeLength, int otherLength) {
  char fullString[encodeLength + otherLength-1];
  int i = 0;
  for(; i < encodeLength-1; i++) {
    fullString[i] = stringEncode[i];
  }

  for(i = encodeLength-1; i < otherLength+encodeLength-1; i++) {
    fullString[i] = otherString[i-encodeLength+1];
  }
  
  fullString[encodeLength+otherLength-1] = '\0';
  return fullString;
}*/

/*
void main(int argc, char* argv[]) {
char* encode(char* stringToSend) {
  // Encode first with 8 bits to show length after the next 8 bits and checksum
  int i = 0;
  uint8_t sendlength = 0;
  char* encodeBin = toBinary(stringToSend);
  printf("%c", encodeBin); 
    fflush(stdout);
  uint8_t checksum = (uint8_t) checkSum(encodeBin);
  while (stringToSend[i] != '\0') {
    sendlength++;
    i++;
  }
  char* stringLength = changeToChar(sendlength);
  char* checkSumLength = changeToChar(checksum); //change checksum to char
  i = 0;
  int otherLength = 0;
  while(stringLength[i] != '\0') {
    otherLength++;
    i++;
  }
  
  char* con = concatenateStrings(stringLength, checkSumLength, 9, 9);
  char* conned = concatenateStrings(con, encodeBin, 17, (int) otherLength);
  
  printf(con);
  fflush(stdout);
  printf(conned);
  fflush(stdout);

  return conned;
  
}

int checkSum(char* encodedString) {
  // if it's a 1, add position to checksum (start by 1)
  int sum = 0;
  int i = 0;
  while (encodedString[i] != '\0') {
    printf("encodedString[i] is %d",encodedString[i]);
      fflush(stdout);
    if (encodedString[i] == '1') {
	sum+=1;
    }
    i++;
  }
  return sum%256; 
}

void sendReply(char* encodedReply) {
  int flip;
  int y = 0;
  int clock = 60;
  int nextTime = millis() + clock;
  printf("encodedReplyp[%d] is %d \n", 0, encodedReply[0]);
  while (encodedReply[y] != '\0') {
    printf("Encodedreply[%d] is %c\n", y, encodedReply[y]);
    while (millis() < nextTime) {
      //do nothing
    }
    printf("THIS DOESN'T WORK WORK DAMMIT");
    fflush(stdout);
    if (encodedReply[y] == '0'){
      flip = 0;
    }else{
      flip = 1;
    }
    digitalWrite(7,flip);
    nextTime+=clock;
    y+=1;
  }
}

void sendAgain(char* encodedReply) {
  
}

int main(int argc,char* argv[]) {
    unsigned int nextTime;
    short flip;
    int length;
    int count=0;
    int* messageLength[8];
    char message[] = "1010101010101010101010111111111111111111010101010101010101022222";

    return 1;
    //pinMode(4, GPIO_CLOCK)
}*/

