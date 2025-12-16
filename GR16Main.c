#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#pragma config OSC = HS
#pragma config WDT = OFF
#pragma config LVP = OFF
#pragma config PWRT = ON

#define _XTAL_FREQ 10000000 // define clock frequency for __delay_10ms()

#define LED1 LATBbits.LATB2	//LED1
#define LED2 LATBbits.LATB3	//LED2
#define LED3 LATBbits.LATB4	//LED3
#define LED4 LATBbits.LATB5	//LED4

#define A1 LATBbits.LATB0
#define A2 LATBbits.LATB1
#define B1 LATAbits.LATA4
#define B2 LATAbits.LATA5

#define IRBL PORTAbits.RA2
#define IRBR PORTAbits.RA3

int setpoint_distance = 400;   //Distance set point
void setupADC(void);           //Configure A/D
unsigned int readADCL(void);    //Read ADC
unsigned int readADCR(void);

void wait10ms(int del); // generated a delay in multiples of 10ms

void BreakLR(); // needed to add prototypes of functions
void Forward();
void Reverse();
void TurnL();
void TurnR();

int main(void)
{
	// Below is our "set up" statements

	ADCON1=0b00001101;			// Sets voltage reference and ports AN0 and AN1 as analogue
	TRISA=0b11001111;   //Port A all inputs except B1 & B2
    TRISB=0b11000000;   //Port B, RB0 to RB5 as outputs
    setupADC();         // Configure ADC
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
    
    for(int i=0; i<3; i++){
        LED1=LED2=LED3=LED4 = 1;    //turn LED1 on
        wait10ms(50);               //wait 1/2 a second
        LED1=LED2=LED3=LED4 = 0;    //turn LED1 off
        wait10ms(50);               //wait 1/2 a second
     }
    
    while(1){
    unsigned int left = readADCL();
    unsigned int right = readADCR();
    int T = 20; // wait time (Set 200 in lab & 30 in small room/dorm)
    int TurnT = 50; // Turning time (TurnT is proportional to the friction of the floor)
    int k = TurnT/4; //Corrects any overturn on smoother surfaces
    
    LED2=!IRBL; // Shows that IRB is working correctly
    LED3=!IRBR;
    LED1 = LED4 = 0;
    
    if(left >= setpoint_distance && right >= setpoint_distance){
        LED1 = LED4 = 1;
        Reverse();
        wait10ms(T);
        TurnR();
        wait10ms(k);
        Forward();
        wait10ms(T);
        
    }
    else if(left >= setpoint_distance){  //If left hand sensor detects object equal or greater than setpoint_distance
        LED1 = 1;
        Reverse();
        wait10ms(T);
        TurnR();
        wait10ms(TurnT);
        Forward();
        wait10ms(T);
        TurnL();
        wait10ms(k);
    }
    else if(right >= setpoint_distance){  //If right hand sensor detects an object equal or greater than setpoint_distance
        LED4 = 1;
        Reverse();
        wait10ms(T);
        TurnL();
        wait10ms(TurnT);
        Forward();
        wait10ms(T);
        TurnR();
        wait10ms(k);
	}
	if(!IRBL && !IRBR){
		Forward();
	}
	else if(IRBL && IRBR){
		BreakLR();
	}
	else if(IRBL && !IRBR){
		TurnR();
	}
    else if(!IRBL && IRBR){
		TurnL();
	}
 }
 
}

void wait10ms(int del){	 //delay function
    unsigned char c;
    for(c=0;c<del;c++)
        __delay_ms(10);
    return;
}

// Below are functions for IR distance sensors

void setupADC(void){    // configure A/D
ADCON2 = 0b10000010; // Fosc/32, A/D result right justified
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

// Below are functions for Motor controls

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
