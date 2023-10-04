#include "utils.h"
//#include <stdio.h>

void delay(int x){
    //change to calculated value
		int i=0;
    int val = x* (21000000/4);

    for( i = 0; i < val; i++){
       // printf("stalling\n");
    }
}
