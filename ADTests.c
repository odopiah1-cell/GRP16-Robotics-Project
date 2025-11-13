/* 
 * File:   ADtest.c
 * Author: Craig Bacon                               Created on 31 August 2017
 * Reads the left hand IR distance sensor connected to analogue input AN0(Pin2)      
 * If the value of the IR sensor is greater than setpoint_distance turn on LED3.
 */
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#pragma config OSC = HS     //High speed resonator
#pragma config WDT = OFF    //Watchdog timer off
#pragma config LVP = OFF    //Low voltage programmer disabled
#pragma config PWRT = ON    //Power up timer on
#define LED3 LATBbits.LATB4    //Define LED3
int setpoint_distance = 400;   //Distance set point
void setupADC(void);           //Configure A/D
unsigned int readADC(void);    //Read ADC

int main(void)
{
ADCON1=0b00001110;  //Set voltage reference and port A0 as analogue input
TRISA=0b11111111;   //Port A all inputs
TRISB=0b00000000;   //Port B all outputs
setupADC();         // Configure ADC
LATB=0;             //Turn Leds off
while(1){
    if(readADC() >= setpoint_distance)  //If left hand sensor detects an object
        LED3=1;                       //equal or greater than setpoint_distance
    else                              //turn on LED3
        LED3=0;
 }
}
void setupADC(void){    //configure A/D
ADCON2bits.ADCS0=0;     // Fosc/32
ADCON2bits.ADCS1=1;     
ADCON2bits.ADCS2=0;
ADCON2bits.ADFM=1;      //A/D result right justified
ADCON1=0b00001110;      //Set voltage reference and port A0 as A/D
ADCON0bits.ADON=1;      //Turn on ADC
}
unsigned int readADC(void){	 //Read port AN0
ADCON0bits.CHS0=0;          //0000,channel 0 is set,
ADCON0bits.CHS1=0;  		//use binary number to select ADC channel
ADCON0bits.CHS2=0;  		//e.g. 1001 channel 9 set
ADCON0bits.CHS3=0;  		//Channel 0 set
ADCON0bits.GO=1;
while (ADCON0bits.GO);  //do nothing while conversion in progress
return ((ADRESH<<8)+ADRESL); //Combines high & low bytes into one 16 bit
}                           // value and returns Result (A/D value 0-1023)
