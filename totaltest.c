
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <math.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdint.h>
#include <curl/curl.h>

int* concatenateStrings(int* stringEncode, int* otherString, int encodeLength, int otherLength) {
  int fullString[encodeLength + otherLength];
  int i = 0;
  for(; i < encodeLength; i++) {
    fullString[i] = stringEncode[i];
  }

  for(i = encodeLength; i < otherLength+encodeLength; i++) {
    fullString[i] = otherString[i-encodeLength];
  }

  return fullString;
}


void sendReply(int* encodedReply, int length) {
  int flip;
  int i = 0;
  int clock = 20;
  int nextTime = millis() + clock;
  printf("Encodedreply is %s \n", encodedReply);
  while (i < length) {
    while (millis() < nextTime) {
      //do nothing
    }
    if ( encodedReply[i] == 0){
      flip = 0;
    }else{
      flip = 1;
    }
    digitalWrite(7,flip);
    nextTime+=clock;
  }
  //sendToFlask(encodedReply,  length);
}

int* getBinary (char* ascii) {
  int length = 0;
  while(ascii[length] != '\0') {
     length++;
  }

  int stuff[8*length];
  for(int i =0; i< length; i++) {
    int c = ascii[i];
    for(int x = 7; x >= 0; x--) {
      stuff[x*8+i] = c & 1;
      c = c >> 1;
    }
  }
  return stuff;
}


void* encode(int* stringToSend) {
  // Encode first with 8 bits to show length after the next 8 bits and checksum

  char* encodedBody = getBinary(stringToSend);
  int i = 0;
  int length = 0;
  while(encodedBody[i] != '\0') {
    length++;
  }

  int checksum = 8;

  int* checksumStuff = getBin(checksum);
  int* bodyLength = getBin(length);

  char* con = concatenateStrings(bodyLength, checksumStuff, 8, 8);
  char* connected = concatenateStrings(con, encodedBody, 17, length);

  sendReply(connected, length);

}

int getBin(int number) {
    int stuff[8];
    int c = number; 
    for(int i = 0; i<8; i++) {
   	stuff[i] = c & 1;
	c = c << 1;
    }
   return stuff;
}

void read_callback(char ptr, size_t size, size_t nmemb, void *userdata) {
    char* streaming = (char*) userdata;
    encode(streaming);
}

int sendToFlask(int* message, int length) {

 CURL *curl;
 CURLcode res;
 char* code;
 curl_global_init(CURL_GLOBAL_ALL);
if(curl) {
 curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:5000:pi");
 curl_easy_setopt(curl, CURLOPT_POSTFIELDS,message);
   res = curl_easy_perform(curl);
   if(res != CURLE_OK)
             curl_easy_strerror(res);

   curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION, read_callback);
   curl_easy_setopt(curl,CURLOPT_WRITEDATA, &code);

   curl_easy_cleanup(curl);
 }
 curl_global_cleanup();
}

int* decode() {
    unsigned int nextTime = millis() + 50;
    int x = 0;
    int* messageLength[8];
    int* checksum[8];
    int count=0;
    int clock = 100;
    //interrupts(0);
    //wiringPiSetupSys();

   short flip;

   if (wiringPiSetup() == -1)
    {
      fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
      return 1 ;
    }

    nextTime = millis() + TIME_DELAY;
    for (;x<400;x++){
      while (millis() < nextTime) {
      }
      flip = !flip;
      flipper(flip);
      nextTime+=TIME_DELAY;
    }
}
pinMode(2, INPUT);
pullUpDnControl(0,PUD_UP);
    while(1) {
	//wait
     pinMode(0, OUTPUT);
    digitalWrite(0,1);
    pinMode(0, INPUT);
    delay(0.02);
        printf("%d\n", digitalRead(0));
   //     printf("%d analog \n", analogRead(2));
//	if (digitalRead(0) == 0) {
//	    printf("ghfjdkslhgkjds\n");
//	    break;
//	}
    } 
    //interrupts(1);
    //interrupts(0);  
    //assume each laser signal takes 100 ms to go through
    wiringPiSetupSys();
    void digitalWrite(7,1);
    delay(2);

    while(count < 8) {
        nextTime = millis() + clock; 
        messageLength[count] = digitalRead(0);
        printf("%d\n", messageLength[count]);
	while(millis() < nextTime) {
            //pause for do nothing to wait for next signal
        }
        count++;
    }   
    //interrupts(1);
        
    // Calculate length
    int sum = 0;
    while (count > 0) {
        if (messageLength[count-1] == 1) {
            sum += pow(2, count-1);
        }
        count--;
    }   
        
    int bodyMessAndCheck[sum];
    
    //interrupts(0);
    nextTime = millis() + 45;
    while(millis() < nextTime) {
        // pause for 45 millis to calculate length
    }  
    int i;
    for(i = 0; i < 8; i++) {
        nextTime = millis() + clock;
    wiringPiSetupSys();
    digitalWrite(7,1);
    delay(2);

        messageLength[i] = digitalRead(0);
        while (millis() < nextTime) {
            //pausing
        }
    }       
    //interrupts(1);
        
    int checksum = 0;
    for(count=8; count > 0; count--) {
        if (messageLength[count-1] == 1) {
            checksum += pow(2, count-1);
        }
        count--;
    }   
    //interrupts(0);
        
    while(millis() < nextTime) {
        // pause for 45 millis to calculate chksum
    }
        
    //read rest of message
    wiringPiSetupSys();
    digitalWrite(7,1);
    delay(2);
    for(i = 0; i < sum; i++) {
        nextTime = millis() + clock;
        wiringPiSetupSys();
        digitalWrite(7,1);
        delay(2);

	bodyMessAndCheck[i] = digitalRead(0);
        while(millis() < nextTime) {
            //pausing fo rnext sign again
        }
    } 
    //interrupts(1);
    sendToFlask(bodyMessAndCheck, sum);      
  
}

void seeOne(){





return;
}


int main(int argc,char* argv[]) {
    
    unsigned int nextTime;
    short flip;
    int length;
    //int message[] = {0,1,0,1,0,1,0,1};
    seeOne();

    //interrupts

    if (wiringPiSetup() == -1)
    {return 1;
    }    
    	
    int* toSend = decode();
    //sendReply(1, 1);
    //sendReply(message, 8);
    
    printf("Not this again!");
    //sendReply(encodedM, sizeOfEncoded);
    printf("Space X watcgh me");
    //sendReply(encodedM2);
    
    digitalWrite(7,0);
    
    return 1;
    //pinMode(4, GPIO_CLOCK)
}
