#include <math.h>
#include "GPIODriver.h"
#include "UARTInitialization.h"


double TotalDistance, DistanceIncrease;
double StartingLongitude, StartingLatitude;
double CurrentLongitude, CurrentLatitude;
double PreviousLongitude, PreviousLatitude;


int main(void)
{

	LEDIniti();
	SwitchIniti();
	while (1)
	{
		/*in the second milestone, this loop will be utilized to calculate the total distance
		and use the current, previous and starting coordinates to calculate the increase in distance
		as well as saving the needed coordinates when the system is powered off.
		it will also utilize systimer to make a proper delay to match the required output
		and the program flow in general will be in this loop as this loop should be working as long as the device
		is turned on.*/

		TotalDistance = 110; // this will be used to initialize the total distance to 110 just for the sake of testing the LEDs

		if (TotalDistance >= 100)
		{
			LED_on(LEDs); // this test will turn all leds on. 
		}
	}
}
