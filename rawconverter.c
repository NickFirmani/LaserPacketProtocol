#include <stdio.h>
#include <math.h>
#include <string.h>
void A_to_B(const char*);   //function for converting ASCII to Binary
void B_to_A(const char*);   //function for converting Binary to ASCII

int main(int argc, char **argv[]){
	char hi[] = "Hello world";
	A_to_B(hi);
}

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

void B_to_A(const char* input)
{
	int length = strlen(input);     //get length of string
	
	int binary[8];    //array used to store 1 byte of binary number (1 character)
	int asciiNum = 0;      //the ascii number after conversion from binary
	char ascii;      //the ascii character itself
	
	int z = 0;   //counter used
	
	int x;
	for(x = 0; x < length / 8; x++)     //reading in bytes. total characters = length / 8
	{
		int a;
		for(a = 0; a < 8; a++)      //store info into binary[0] through binary[7]
		{
			binary[a] = (int) input[z] - 48;      //z never resets
			z++;
		}
		
		int power[8];    //will set powers of 2 in an array
		int counter = 7;        //power starts at 2^0, ends at 2^7
		int x;
		for(x = 0; x < 8; x++)
		{
			power[x] = counter;      //power[] = {7, 6, 5, ..... 1, 0}
			counter--;    //decrement counter each time
		}
		
		int y;
		for(y = 0; y < 8; y++)    //will compute asciiNum
		{
			double a = binary[y];    //store the element from binary[] as "a"
			double b = power[y];    //store the lement from power[] as "b"
			
			asciiNum += a* pow(2, b);   //asciiNum = sum of a * 2^power where 0 <= power <= 7, power is int
		}
		
		ascii = asciiNum;   //assign the asciiNum value to ascii, to change it into an actual character
		asciiNum = 0;    //reset asciiNum for next loop
		
	}
}
