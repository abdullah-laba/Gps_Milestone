#include "tm4c123gh6pm.h"
#include "bit_utilies.h"


void UART_Init(){
SET_BIT(SYSCTL_RCGCUART_R,0);
while(GET_BIT(SYSCTL_PRUART_R,0) == 0 );
SET_BIT(SYSCTL_RCGCGPIO_R,0);
while(GET_BIT(SYSCTL_PRGPIO_R,0) == 0 );

CLR (UART0_CTL_R, UART_CTL_UARTEN);
	UART0_IBRD_R=104;
	UART0_FBRD_R=11;

	SET (UART0_LCRH_R,UART_LCRH_WLEN_8);
	SET (UART0_LCRH_R,UART_LCRH_FEN);

	SET (UART0_CTL_R,UART_CTL_UARTEN);
	SET (UART0_CTL_R, UART_CTL_TXE);
	SET (UART0_CTL_R, UART_CTL_RXE);

	SET(GPIO_PORTA_AFSEL_R, 0x3) ;

	CLR(GPIO_PORTA_PCTL_R , 0x000000FF);
	SET(GPIO_PORTA_PCTL_R , GPIO_PCTL_PA0_U0RX);
	SET(GPIO_PORTA_PCTL_R , GPIO_PCTL_PA1_U0TX);
	SET(GPIO_PORTA_DEN_R , 0x3);

}


///////////int port A

char UART_IsCharAvail(){
	return((UART0_FR_R&UART_FR_RXFE)==UART_FR_RXFE);
}

char UART_GetChar(){
	while((UART0_FR_R & UART_FR_RXFE) != 0);
	return (char) GET_REG(UART0_DR_R);
}
////////////////////////////___Send to PC_____//////////////////////////////////////////////////

void UART_SNDChar(char DATA){
	while((UART0_FR_R & UART_FR_TXFF) !=0){
		UART0_DR_R = DATA;
	}
}
////////////////////////////___Set Timer_____//////////////////////////////////////////////////
void delay_ms() {
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R = 16000 - 1;	///Assuming a clock frequency of 16 MHz
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_CTRL_R = 0x05;
	while((NVIC_ST_CTRL_R & 0x00010000) == 0);
}

void delay( long ms) {
	while(ms-- > 0) delay_ms();
}


