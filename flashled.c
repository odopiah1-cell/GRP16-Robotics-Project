/* File:   flashled.c
 * Author: Craig Bacon
 * Created on 30 August 2017, 15:25
 * Turns LED1 (RB2 pin 23) on for 1 sec off for 1 sec
 */
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#pragma config OSC = HS    //High speed resonator
#pragma config WDT = OFF   //Watchdog timer off
#pragma config LVP = OFF   //Low voltage programming disabled
#pragma config PWRT = ON   //Power up timer on
#define _XTAL_FREQ 10000000 // define clock frequency for __delay_10ms() 
#define LED1 LATBbits.LATB2	//LED1

void wait10ms(int del);     //generates a delay in multiples of 10ms

int main(void)
{
 TRISB=0b11000000;     	    //configure Port B, RB0 to RB5 as outputs
 LATB=0;                    //turn all LEDs off
 while(1){
    LED1=1;                 //turn LED1 on
    wait10ms(100);          //wait 1 second
    LED1=0;                 //turn LED1 off
    wait10ms(100);          //wait 1 second
    }
 }

void wait10ms(int del){	 //delay function
    unsigned char c;
    for(c=0;c<del;c++)
        __delay_ms(10);
    return;
}
