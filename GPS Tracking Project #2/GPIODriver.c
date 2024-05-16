#include "GPIODriver.h"

void LEDIniti(void)
{
	SYSCTL_RCGCGPIO_R |= 0x20;
	while ((SYSCTL_PRGPIO_R & 0x20) == 0)
	{
	}								   // check that the portF is activated
	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY; // unlocking ports
	GPIO_PORTF_CR_R |= LEDs;		   // to allow changes to be done to theLEDS
	GPIO_PORTF_DIR_R |= LEDs;		   //  set 1, 2 and 3 LEDS as outputs
	GPIO_PORTF_AFSEL_R &= (~LEDs);	   // set AFSELto zeroes as we arent using alternate functions
	GPIO_PORTF_DEN_R |= LEDs;		   // digital set
	GPIO_PORTF_DATA_R &= (~LEDs);	   // data
	GPIO_PORTF_AMSEL_R &= (~LEDs);	   // set to zeroes as there are no analog data
	GPIO_PORTF_PCTL_R &= (~LEDs);	   // set to zeroes due to no alternate functions
}
void SwitchIniti(void)
{
	SYSCTL_RCGCGPIO_R |= 0x20; // 0b00100000 activating portF
	while ((SYSCTL_PRGPIO_R & 0x20) == 0)
	{
	}									   // check that the portF is activated
	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;	   // unlocking PORTS
	GPIO_PORTF_CR_R |= SwitchOneTwo;	   // to allow changes to be done to the switches
	GPIO_PORTF_DIR_R &= (~SwitchOneTwo);   // to set PF0 and PF4 as inputs
	GPIO_PORTF_PUR_R &= (~SwitchOneTwo);   // switches are pulldown so we can use positive logic later
	GPIO_PORTF_AFSEL_R &= (~SwitchOneTwo); // this is optional because AFSEL is by default set to zeroes
	GPIO_PORTF_DEN_R |= SwitchOneTwo;	   // to make the switches accept digital data
	GPIO_PORTF_DATA_R |= SwitchOneTwo;	   // initializing the data of switches (1 BECAUSE SWITCHES ARE PULL down logic)
	GPIO_PORTF_AMSEL_R &= (~SwitchOneTwo); // we set it to zeroes as we will not use analog data
	GPIO_PORTF_PCTL_R &= (~SwitchOneTwo);  //   set to zero because we arent using any alternate functions
}

void PortC_Init(void){
		
	SYSCTL_RCGCGPIO_R |= 0x00000004;  //ACTIVE CLK PORT C 
	while((SYSCTL_PRGPIO_R & 0x00000004) == 0){};
	GPIO_PORTC_CR_R =| 0x07; // allow changes to PC2-0 
	GPIO_PORTC_DIR_R &= ~0x07; // PC2-0 in
	GPIO_PORTC_AFSEL_R &= ~0x07; 
	GPIO_PORTF_PCTL_R &= 0x00000000;  
	GPIO_PORTF_AMSEL_R &= 0x07; 
	GPIO_PORTC_DEN_R |= 0x07; // digital PC2-0
}

void PortD_Init(void){
	
	SYSCTL_RCGCGPIO_R |= 0x00000008;  //ACTIVE CLK PORT D
	while((SYSCTL_PRGPIO_R & 0x00000008) == 0){};
	GPIO_PORTD_LOCK_R = GPIO_LOCK_KEY;	   // unlocking PORTS
	GPIO_PORTD_CR_R =| 0x7F; // allow changes to PD6-0 
	GPIO_PORTD_DIR_R &= ~0x7F; // PD6-0 in
	GPIO_PORTD_AFSEL_R &= ~0x7F; 
	GPIO_PORTD_PCTL_R &= 0x00000000;  
	GPIO_PORTD_AMSEL_R &= 0x7F; 
	GPIO_PORTD_DEN_R |= 0x7F; // digital PD6-0
}


void LED_on(unsigned char LED)
{ // turn on LED
	GPIO_PORTF_DATA_R |= LED;
}

void LED_off(unsigned char LED)
{ // turn off LED
	GPIO_PORTF_DATA_R &= (~LED);
}
unsigned char SwitchOneRead(void)
{ // check if switch one is pressed or not
	return GPIO_PORTF_DATA_R & 0x01;
}
unsigned char SwitchTwoRead(void)
{ // check if switch two is pressed or not
	return GPIO_PORTF_DATA_R & 0x10;
}