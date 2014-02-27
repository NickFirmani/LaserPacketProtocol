#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <math.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdint.h>
//#include <~/laserpi.c>


char* getBin(uint8_t c)
{
  printf("getbin c is %u \n",c);
  char binarr[9];
  int i;
  for(i=0;i<8;i++){
    binarr[i]=(char) c%2;
    c=c/2;
    printf("binarr[i] is %d \n",binarr[i]);
  }
  binarr[8] = '\0';
  return binarr;
}

char* decode(char* binstring) {
   
}

char* concatenateStrings(char* stringEncode, char* otherString, int encodeLength, int otherLength) {
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
}

char* changeToChar(uint8_t number) {
    char returnVal[9];
    char* things = getBin(number);
    printf("things in general is %d\n", things);
    // Does this work?
    /*int i = 0;
    while(i < 8) {
	returnVal[i] = (char) ((things[i] << (7-i)) >> 7 );

        if (returnVal[7-i] == '0') {
	    returnVal[7-i] = "0";
	} else {
	    returnVal[7-i] = "1";
	}
	i++;
    }
    returnVal[8] = '\0';*/
    return things;
}

char* toBinary(char* strings) {
  int i = 0;
  int length = 0;
  int binlength = 0;
  while (strings[i] != '\0') {
    length++;
    binlength+=8;
    i++;
  }
  printf("binlength at toBinary is %d \n",binlength);
  i = 0;
  int j = 0;
  char returnString[binlength];
  while (j < length) {
    while ( i < 8) {
      returnString[8*j+i] = (char) (strings[j] >> i) & 1;
      //printf("returnString[8*j+i] from toBinary is %d\n", returnString[8*j+i]);
      i++;
    }
    j++;
    i=0;
  }
  returnString[binlength-1] = '\0';
  return returnString;
}

char* encode(char* stringToSend) {
  // Encode first with 8 bits to show length after the next 8 bits and checksum
  int i = 0;
  uint8_t sendlength = 0;
  char* encodeBin = toBinary(stringToSend);
  printf("encodeBin is: %c\n", encodeBin); 
    fflush(stdout);
  uint8_t checksum = (uint8_t) checkSum(encodeBin);
  while (stringToSend[i] != '\0') {
    sendlength++;
    i++;
  }
  char* stringLength = getBin(sendlength);
  char* checkSumLength = (char*) getBin(checksum); //change checksum to char
  i = 0;
  int otherLength = 0;
  while(stringLength[i] != '\0') {
    otherLength++;
    i++;
  }
  otherLength++;
  printf("stringLength is %c \n",stringLength);
  printf("checksumLength is %c \n",checkSumLength);
  printf("encodeBin is %c \n",encodeBin);
  printf("otherLength is %d \n",otherLength);
  char* con = concatenateStrings(stringLength, checkSumLength, 9, 9);
  char* conned = concatenateStrings(con, encodeBin, 17, otherLength);
  
  printf("%c\n",con);
  fflush(stdout);
  printf("%c\n",conned);
  fflush(stdout);

  return conned;
  
}

int checkSum(char* encodedString) {
  // if it's a 1, add position to checksum (start by 1)
  int sum = 0;
  int i = 0;
  while (encodedString[i] != '\0') {
    printf("encodedString[i] is %d\n",encodedString[i]);
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
  int clock = 1000;
  int nextTime = millis() + clock;
  printf("Encodedreply is %d \n", encodedReply);
    fflush(stdout);
  while (encodedReply[y] != '\0') {
    printf("encodedReply[%d] is %c \n",y,encodedReply[y]);
    while (millis() < nextTime) {
      //do nothing
    }
    if ( encodedReply[y] == 0){
      flip = 0;
    }else{
      flip = 1;
    }
    digitalWrite(7,flip);
    nextTime+=clock;
    y++;
  }
  printf("y is %d \n",y);
    fflush(stdout);
}

void sendAgain(char* encodedReply) {
  
}

int main(int argc,char* argv[]) {
    unsigned int nextTime;
    short flip;
    int length;
    int count=0;
    int* messageLength[8];
    char message[] = "1";

   if (wiringPiSetup() == -1)
    {
      fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno));
      return 1;
    }

    char* encodedM = encode(message);
    sendReply(encodedM);
    
    /*while(node->next != NULL) {
	free(node->address);
	addrList = node->next;
    }*/
    /* nextTime = millis() + 50;
    int x = 0;
        

    //assume each laser signal takes 100 ms to go through
    while(count < 8) {
        nextTime = millis() + 100;
	int[count] = digitalRead(7);
	while(millis() < nextTime) {
	    //pause for do nothing to wait for next signal
	}
	count++;
    }

    // Calculate length
    int sum = 0;
    while (count > 0) {
	if (messageLength[count-1] == 1) {
	    sum += pow(2, count);
	}
	count--;
    }

    int[sum-1] message;

    nextTime = millis() + 50;
    while(millis() < nextTime) {
	// pause for 50 millis to calculate length
    }  
    
    for(int i = 0; i < sum; i++) {
	nextTime = millis() + 100;
	message[i] = digitalRead(7);
	while (millis() < nextTime) {
	    //pausing
	}
    }
    */

    digitalWrite(7,0);
    
    return 1;
    //pinMode(4, GPIO_CLOCK)
}
