/* File:   flashled.c
 * Updated on 27 November 2025, 22:50
 * Run on MPLABX v6.20 (XC8 compiler)
 * Tool: PiCkit3
 * Turns LEDs 1-4 (RB2 pin 23) on for 1 sec off for 1 sec
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
#define LED2 LATBbits.LATB3	//LED2
#define LED3 LATBbits.LATB4	//LED3
#define LED4 LATBbits.LATB5	//LED4

void wait10ms(int del);     //generates a delay in multiples of 10ms

int main(void)
{
 TRISB=0b11000000;     	    //configure Port B, RB0 to RB5 as outputs
 LATB=0;                    //turn all LEDs off
 while(1){
   for(int i=0; i<3; i++){
        LED1=LED2=LED3=LED4 = 1;    //turn LED1 on
        wait10ms(50);               //wait 1/2 a second
        LED1=LED2=LED3=LED4 = 0;    //turn LED1 off
        wait10ms(50);               //wait 1/2 a second
     }
     while(1);                      // stop blinking so much
     }
 }

void wait10ms(int del){	 //delay function
    unsigned char c;
    for(c=0;c<del;c++)
        __delay_ms(10);
    return;
}
