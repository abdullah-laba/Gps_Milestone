#include "tm4c123gh6pm.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "UARTInitialization.h"

#define PI 3.14159265359

char GPS_logName []="$GPRMC,";
char GPS [80];
char GPS_formated[12][20];
char * token ;
float currentLong , currentLat ;
const double EARTH_RADIUS = 6371000;
const double long_final,lat_final ;

float ToDegree (float angle){
int degree = (int)angle/ 100;
float minutes = angle - (float)degree*100;
return(degree+ (minutes/60));
}

float ToRad (float angle){
	return angle * PI/180 ;
}

void GPS_read(){
	
	char recievedChar;
	char flag = 1 ;

	do{
		int i=0;
		flag =1;
		while(i<7){
	
	if (UART_GetChar() != GPS_logName[i]){
		flag =0 ;
		break;}
	
	i++;
		}
	}while(flag==0);
	
	
	strcpy(GPS,"");
	do{
		char fillGPScounter =0;
		recievedChar = UART_GetChar();
		GPS[fillGPScounter++] = recievedChar;
	}while(recievedChar!='*');
}


void GPS_format(){
	char noOfTokenStrings=0;
	token = strtok(GPS,",");
	do{
	strcpy(GPS_formated[noOfTokenStrings],token);
		token = strtok(NULL,",");
		noOfTokenStrings++;
		
	}while(token!=NULL);
	if(strcmp(GPS_formated[1],"A")==0){
		
			if(strcmp(GPS_formated[3],"N")==0)
				currentLat=atof(GPS_formated[2]);
				else
					currentLat= -atof(GPS_formated[2]);
				
			if(strcmp(GPS_formated[5],"E")==0)
				currentLong=atof(GPS_formated[4]);
				else
					currentLong= -atof(GPS_formated[4]);
	}
}

	

// Function to calculate distance between two coordinates using Haversine formula
float GPS_getDistance(prevLong, prevLat, currentLong, currentLat) {
    // Convert coordinates from degrees to radians
    float prevLongRad = ToRad(prevLong);
    float prevLatRad = ToRad(prevLat);
    float currentLongRad = ToRad(currentLong);
    float currentLatRad = ToRad(currentLat);
    
    // Calculate differences in longitude and latitude
    float longDiffRad = currentLongRad - prevLongRad;
    float latDiffRad = currentLatRad - prevLatRad;
    
    // Apply Haversine formula
    float a = pow(sin(latDiffRad / 2), 2) + cos(prevLatRad) * cos(currentLatRad) * pow(sin(longDiffRad / 2), 2);
    float c = 2 * atan2(sqrt(a), sqrt(1 - a));
    float distance0= EARTH_RADIUS * c;
    
    return distance0;
}

