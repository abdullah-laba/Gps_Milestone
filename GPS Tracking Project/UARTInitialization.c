#include "UARTInitialization.h"

void UARTIniti(void)
{
	SYSCTL_RCGCGPIO_R |= 0x01; // activation of portA
	SYSCTL_RCGCUART_R |= 0x01; // activation of clock
	while ((SYSCTL_PRGPIO_R & (0x01)) == 0){}	   // check that the portA is activated
	GPIO_PORTE_LOCK_R = GPIO_LOCK_KEY; // unlocking ports
	GPIO_PORTE_CR_R |= 0x03;		   // to allow changes to be done to bits 0 and 1
	GPIO_PORTE_AMSEL_R &= ~0x03;	   // set to zeroes as we wont deal with analog data

	GPIO_PORTE_AFSEL_R |= 0x03; // enabling alternate functions
	GPIO_PORTE_PCTL_R &= ~0xFF; // clearing the functions in the first two pins
	GPIO_PORTE_PCTL_R |= 0x11;	// choosing the alternate function to be UART
	GPIO_PORTE_DEN_R |= 0x03;	// make the switches accept digital data
	UART7_CTL_R &= ~UART_CTL_UARTEN; // disable uart

	// we need a boud rate of 9600 so we will substitute in the formula
	// IBRD = 16 MHZ/16*boud rate and the boud rate is 9600 and to get FBRD=0.1667*64+0.5
	UART7_IBRD_R |= 0x68; // setting integer BR to 104 after calculations
	UART7_FBRD_R |= 0x0B; // setting fractional BR to 11 after calculations
	UART7_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN); // enabling FIFO and making data length equal to 8 bits
	// to update BR LCRH must recieve config
	UART7_CTL_R = (UART_CTL_TXE | UART_CTL_RXE | UART_CTL_UARTEN); // enable Tx, Rx and UART
}
uint8 UARTRead(void) // to read
{
	while (UARTDataCheck() == 0)
		;
	return ((uint8)(UART7_DR_R & (0xFF)));
}
void UARTWrite(uint8 data) // to write
{
	while ((UART7_FR_R & (0x01 << 5)) != 0)
		;
	UART7_DR_R = data;
}
uint8 UARTDataCheck(void) // to check data
{
	if ((UART7_FR_R & (0x01 << 4)) == 0)
		return 1; // returns 1 if not empty
	else
		return 0; // returns 0 if empty
}


