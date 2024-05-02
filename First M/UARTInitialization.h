#ifndef UART_INI_H
#define UART_INI_H
#include"tm4c123gh6pm.h"
#include"Std_Types.h"
void UARTIniti(void); // to initialize
void UARTWrite(uint8); // to write
uint8 UARTRead(void); // to read
uint8 UARTDataCheck(void); // check data
#endif