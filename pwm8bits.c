/* PWM pin 13,mark space ratio is 8 bit (255) and the PWM frequency
 * is 610 Hz    PWM Period = (PR2+1)x4 x 1/Osc x TMR2 Prescaler
 * e.g (255+1)x4 x1/10Mhz x 16 =1.638ms or 610Hz.PR2 changes frequency.
 * The 8 bit markspace ratio is stored in CCPR1L
 */

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#pragma config OSC = HS
#pragma config WDT = OFF
#pragma config LVP = OFF
#pragma config PWRT = ON
#define A1 LATBbits.LATB0
#define A2 LATBbits.LATB1
#define B1 LATBbits.LATA4
#define B2 LATBbits.LATA5

void wait10ms(int del); // generated a delay in multiples of 10ms

void BreakLR(); // needed to add prototypes of functions
void Forward();
void Reverse();
void TurnL();
void TurnR();
void Twirl();

int main(void)
{
	// Below is our "set up" statements

	ADCON1 =0b00001101;			// Sets voltage reference and ports AN0 and AN1 as analogue
	TRISB = 0b11000000; 		// Set A1 and A2 as Outputs
	TRISA = 0b11001111;			// Set IR components as Inputs and B1&2 as Outputs
	LATB = 0; 					// Clear all Port B Outputs
	LATA = 0;					//Clear all Port A Outputs
 	int markspace=127;         //mark space value for PWM (50% mark space ratio)
 	TRISCbits.RC2=0;          //set CCP1(pin13) to an output pin
	TRISCbits.RC1=0;		//set CCP2(pin12) to an output pin
 	PR2 = 0b11111111 ;        //set period of PWM
	T2CON = 0b00000111 ;   //Timer 2(TMR2) on, Prescaler = 16
	CCP1CON = (0x0c);        //0x0c enables PWM module CCP1
	CCP2CON = (0x0c);		// 0x0c enables PWM module CCP2
 	CCPR1L = markspace;  //Load duty cycle into CCP1CON, PWM begins
	CCPR2L = markspace;  	//Load duty cycle into CCP2CON, PWM begins

	// our "main" code is what follows bellow

	Forward();
    wait10ms(100);
    BreakLR();
    wait10ms(100);  // idk why but it only worked when i types it in not copy and paste
    Reverse();
    wait10ms(100);
    BreakLR();
	
 	while(1);                //Do nothing forever
}

void wait10ms(int del){ // delay function
	unsigned char c;
	for (c = 0; c < del; c++)
	{
		_delay_ms(10);
	}
	return;
}

// Below are functions for Moter controls

void BreakLR()
{
	A1 = 1;
	A2 = 1;
	B1 = 1;
	B2 = 1;
}

void Forward()
{
	A1 = 0;
	A2 = 1;
	B1 = 0;
	B2 = 1;
}
	
void Reverse()
{
	A1 = 1;
	A2 = 0;
	B1 = 1;
	B2 = 0;
}

void TurnR()
{
	A1 = 0;
	A2 = 0;
	B1 = 0;
	B2 = 1;
}

void TurnL()
{
	A1 = 0;
	A2 = 1;
	B1 = 0;
	B2 = 0;
}

void Twirl()
{
	A1 = 0;
	A2 = 1;
	B1 = 0;
	B2 = 0;
}
