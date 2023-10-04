#include "utils.h"

////////////// Global variables for addresses
//int GPIOC_PDOR_ADDRESS = 0x400FF080 + 0x00;		// PTC Data Output Register address
//int GPIOC_PDIR_ADDRESS =  0x400FF080 + 0x10;		// PTC Data Input Register address

//int GPIOD_PDOR_ADDRESS = 0x400FF0C0;		// PTD Data Output Register address
//int GPIOD_PDIR_ADDRESS = 0x400FF0C0 + 0x10;		// PTD Data Input Register address

void delay(int x){
		int i =1;
    int val = x * 5250000;

    while(i<val){
			i = i+1;
    }
}

void delay_ms(int x){
		int i =1;
    int val = x * 5250;

    while(i<val){
			i = i+1;
    }
}

void delay_us(int x){
		int i =1;
    int val = x * 6;

    while(i<val){
			i = i+1;
    }
}

void store(int value, int addr)
{
	int* ptr;
	ptr = (int*) addr;
	*ptr = value;
}

int load(int addr)
{
	int value;
	int* ptr;
	ptr = (int*) addr;
	value = *ptr;
	return value;
}
