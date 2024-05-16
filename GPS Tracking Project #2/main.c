#include "tm4c123gh6pm.h"
#include "UARTInitialization.h"
#include "GPIODriver.h"
#include "GPS.c"
#include "7Segment.c"


// Global variables to store previous coordinates
float prevLong = 0.0;
float prevLat = 0.0;
//set delay 
unsigned long ms = 1000 ;       // depending on the update rate of the GPS
// Global variable to store total distance
float totalDistance = 0.0;

int main() {
    // Initialize UART for GPS communication
    UART_Init();

    // Initialize GPIO for LED and Switch
    LEDIniti();
	
    // Initialize Port C for conduct Ground on PC2-0
	PortC_Init();
	
    // Initialize Port D for 7 Segment on PD6-0
    PortD_Init();
	
    // Read initial GPS data to initialize previous coordinates
    GPS_read();                    //store data in char GPS [80];
    GPS_format();                 //get currentLat,currentLong
    prevLong = currentLong;
    prevLat = currentLat;
		

    while ( totalDistance <= 100) {
        // Read GPS data
        GPS_read();
        GPS_format();
		
		char buffer[50];

        // Calculate distance from previous location to current location and accumulate
        float distance = GPS_getDistance(prevLong, prevLat, currentLong, currentLat);
        totalDistance += distance;
		
		split_digit (totalDistance);  //display distance on 3 sevensegment
		splittime();

        // Update previous coordinates for the next iteration
        prevLong = currentLong;
        prevLat = currentLat;

        // Check if distance is less than 100m
        if (totalDistance <= 100) {
            // Turn on red LED
            LED_on(RedLED);
        } else {
            // Turn off red LED
            LED_off(RedLED);
        }
		
		sprintf(buffer, "%f,%f\n", currentLat, currentLong);

		for(short i=0;i<strlen(buffer);i++)
		{
			UART_SNDChar(buffer[i]);
		}
		delay(ms);
    }

	char DATA = '\n'; 
	UART_SNDChar(DATA);

    return 0;
	
}



