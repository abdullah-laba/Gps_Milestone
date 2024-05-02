#ifndef GPIO_H
#define GPIO_H
#include "tm4c123gh6pm.h"
#define GPIO_LOCK_KEY 0x4C4F434B
#define RedLED 0x02    // --> RED LED on pin1  0010
#define BlueLED 0x04   // --> BLUE LED on pin2  0100
#define GreenLED 0x08  // --> GREEN LED on pin3  1000
#define LEDs 0x0E
#define SwitchOne 0x01 // --> Switch one on pin0 0001
#define SwitchTwo 0x10 // --> Switch two on pin4 10000
#define SwitchOneTwo 0x11
void SwitchIniti(void);
void LEDIniti(void);
unsigned char SwitchOneRead(void);
unsigned char SwitchTwoRead(void);
void LED_on(unsigned char LED);
void LED_off(unsigned char LED);
#endif