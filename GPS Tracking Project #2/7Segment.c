#include "GPIODriver.h"
#include "tm4c123gh6pm.h"
#include "UARTInitialization.h"

unsigned int seg1,seg2,seg3 ; 
unsigned char segemntarray[10] = {0x3F, 0x6, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x6F };


void sevensegment (unsigned int index){
	GPIO_PORTD_DATA_R |=(~segemntarray[index]);
}


void split_digit (float totalDistance){
	int d = (int)totalDistance;
	
	seg1 = d %10 ; //right digit
	d = d/10 ;
	seg2 = d %10 ;
	d = d/10 ;
	seg3 = d %10 ;
}

void display(int gnd, char value){
	GPIO_PORTD_DATA_R = 0x00;
	GPIO_PORTC_DATA_R = gnd;
	sevensegment(value);
}

}
 void splittime(){
 
	unsigned int counter = 0;
	if(counter==0){
		display(1,seg3);
		counter++;
		delay(5);	
	} 
	if(counter==1){
		display(2,seg2);
		counter++;
		delay(5);
	}
	if(counter==2){
		display(4,seg1);
		counter = 0;
		delay(5);
	}
 }
