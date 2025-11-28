/* 
 * File:   ADtest.c
 * Reads the left hand IR distance sensor connected to analogue input AN0(Pin2)      
 * If the value of the IR sensor is greater than setpoint_distance turn on LED3.
 Modify your code to:
• Include both IR obstacle sensors
• Move the motors which:
• stop when an obstacle is detected,
• reverse for 2s,
• turn left or right for a set amount of time (which needs to be determined by you through trial and error) so that the robot has turned 90 degrees,
• move forward for 2s
• turn 90 degrees
• move forward for 2s. (3 marks)
 */

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#pragma config OSC = HS     //High speed resonator
#pragma config WDT = OFF    //Watchdog timer off
#pragma config LVP = OFF    //Low voltage programmer disabled
#pragma config PWRT = ON    //Power up timer on
#define _XTAL_FREQ 10000000 // define clock frequency for __delay_10ms()
#define LED1 LATBbits.LATB2	//LED1
#define LED2 LATBbits.LATB3	//LED2
#define LED3 LATBbits.LATB4 //LED3
#define LED4 LATBbits.LATB5	//LED4
int setpoint_distance = 400;   //Distance set point
void setupADC(void);           //Configure A/D
unsigned int readADCL(void);    //Read ADC
unsigned int readADCR(void);


int main(void)
{
ADCON1=0b00001101;  //Set voltage reference and port A0 and A1 as analogue input
TRISA=0b11111111;   //Port A all inputs
TRISB=0b00000000;   //Port B all outputs
setupADC();         // Configure ADC
LATB=0;             //Turn Leds off
while(1){
    unsigned int left = readADCL();
    unsigned int right = readADCR();
    
    if(left >= setpoint_distance)  //If left hand sensor detects an object equal or greater than setpoint_distance
        LED1=LED2=1;               //turn on LED3
    else                              
        LED1=LED2=0;
    if(right >= setpoint_distance)  //If right hand sensor detects an object
        LED3=LED4=1;                       //equal or greater than setpoint_distance
    else                              //turn on LED3
        LED3=LED4=0;
 
 }
}
void setupADC(void){    // configure A/D
ADCON2bits.ADCS0=0;     // Fosc/32
ADCON2bits.ADCS1=1;     
ADCON2bits.ADCS2=0;     
ADCON2bits.ADFM=1;      // A/D result right justified
ADCON1=0b00001101;      // Set voltage reference and port A0 and A1 as A/D
ADCON0bits.ADON=1;      // Turn on ADC
}

unsigned int readADCL(void){	 //Read port AN0
ADCON0bits.CHS=0;
__delay_us(10);
ADCON0bits.GO=1;
while (ADCON0bits.GO);  //do nothing while conversion in progress
return ((ADRESH<<8)+ADRESL); //Combines high & low bytes into one 16 bit
}                           // value and returns Result (A/D value 0-1023)

unsigned int readADCR(void){	 //Read port AN1
ADCON0bits.CHS=1;  		//Channel 1 set
__delay_us(10);
ADCON0bits.GO=1;
while (ADCON0bits.GO);
return ((ADRESH<<8)+ADRESL);
}               


