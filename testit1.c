#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <math.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdint.h>
//#include <~/laserpi.c>

char* A_to_B(const char* input)
{
        printf("RIGHT AT THE START?????");
        fflush(stdout);
        int ascii;           // used to store the ASCII number of a character
        printf("What, here?");
        fflush(stdout);
        int length = strlen(input);        //find the length of the user's input
        printf("We are about to segment");
        fflush(stdout);
        printf("segment here?");
        fflush(stdout);
        char* output[length*8];
        printf("Nope, segment later");
        fprintf(stdout, "We didn't segment yet\n");
        fflush(stdout);
        int x;
        for(x = 0; x < length; x++)          //repeat until user's input have all been read
        // x < length because the last character is "\0"
        {
                ascii = input[x];        //store a character in its ASCII number

                /* Refer to http://www.wikihow.com/Convert-from-Decimal-to-Binary for conversion method used
                 * in this program*/

                char *binary_reverse = malloc( sizeof(char) * 10);       //dynamic memory allocation
                char *binary = malloc( sizeof(char) * 10);

                int y = 0;    //counter used for arrays

                while(ascii != 1)    //continue until ascii == 1
                {
                        if(ascii % 2 == 0)    //if ascii is divisible by 2
                        {
                                binary_reverse[y] = '0';   //then put a zero
                        }
                        else if(ascii % 2 == 1)    //if it isnt divisible by 2
                        {
                                binary_reverse[y] = '1';   //then put a 1
                        }
                        ascii /= 2;    //find the quotient of ascii / 2
                        y++;    //add 1 to y for next loop
                }

                if(ascii == 1)    //when ascii is 1, we have to add 1 to the beginning
                {
                        binary_reverse[y] = '1';
                        y++;
                }

                if(y < 8)  //add zeros to the end of string if not 8 characters (1 byte)
                {
                        for(; y < 8; y++)  //add until binary_reverse[7] (8th element)
                        {
                                binary_reverse[y] = '0';
                        }
                }

                int z;
                for(z = 0; z < 8; z++)  //our array is reversed. put the numbers in the rigth order (last comes first)
                {
                        binary[z] = binary_reverse[7 - z];
                }
                printf("Maybe the binary output thingermagiger\n");
                fflush(stdout);
                output[x*8] = binary[0];
                output[x*8+1] = binary[1];
                output[x*8+2] = binary[2];
                output[x*8+3] = binary[3];
                output[x*8+4] = binary[4];
                output[x*8+5] = binary[5];
                output[x*8+6] = binary[6];
                output[x*8+7] = binary[7];
                printf("just to make sure");
                fflush(stdout);
                free(binary_reverse);     //free the memory created by dynamic mem. allocation
                free(binary);
                printf("IF IT'S THIS...");
                fflush(stdout);
        }
        int o = 0;
        for(o = 0; o<length; o++){
                fprintf(stdout, "%c ", output[o]);
                fprintf(stdout, "\n");
                fflush(stdout);
        }
        return output;

}



char* getBin(uint8_t c)
{
  printf("getbin c is %d \n",c);
  char binarr[9];
  int i;
  for(i=0;i<8;i++){
    binarr[i]= c%2;
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
  printf("this is the full string to send %d", fullString);
  return fullString;
}

char* changeToChar(uint8_t number) {
    
    char returnVal[9];
    char* things = getBin(number);

    /*int i = 0;
    while(i < 8) {
	returnVal[i] = (char) ((things[i] << (7-i)) >> 7 );

      /*  if (returnVal[7-i] == '0') {
	    returnVal[7-i] = "0";
	} else {
	    returnVal[7-i] = "1";
	}
	i++;
    }*/
    returnVal[8] = '\0';
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
      printf("returnString[%d] from toBinary is %d\n",8*j+i, returnString[8*j+i]);
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
  /*int i = 0;
  char sendlength = 0;
  char* encodeBin = toBinary(stringToSend);
  printf("encodeBin is: %c\n", encodeBin); 
    fflush(stdout);
  char checksum = checkSum(encodeBin);
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
  otherLength++;
  printf("stringLength is %c \n",stringLength);
  printf("checksumLength is %c \n",checkSumLength);
  printf("encodeBin is %c \n",encodeBin);
  printf("otherLength is %d \n",otherLength);
  char* con = concatenateStrings(stringLength, checkSumLength, 8, 9);
  char* conned = concatenateStrings(con, encodeBin, 17, otherLength);
  */

  char* encodedBody = A_to_B(stringToSend);
  int i = 0;
  int length = 0;
  while(encodedBody[i] != '\0') {
    length++;
  }  

  int checksum = checkSum(encodedBody);
  
  char* checksumStuff = getBin(checksum);
  char* bodyLength = getBin(length);

  char* con = concatenateStrings(bodyLength, checksumStuff, 8, 8);
  char* connected = concatenateStrings(con, encodedBody, 17, length);
   

  printf("%c\n",con);
  fflush(stdout);
  printf("%c\n",connected);
  fflush(stdout);

  return connected;
  
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
  printf("Encodedreply is %s \n", encodedReply);
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
    char message[] = "space";

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

