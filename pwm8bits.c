/* File:   pwm8bits.c
 * Author: Craig Bacon
 * Created on 30 October 2014, 14:11
 * PWM pin 13,mark space ratio is 8 bit (255) and the PWM frequency
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

int main(void)
{
 int markspace=127;         //mark space value for PWM (50% mark space ratio)
 TRISCbits.RC2=0;          //set CCP1(pin13) to an output pin
 PR2 = 0b11111111 ;        //set period of PWM
T2CON = 0b00000111 ;   //Timer 2(TMR2) on, Prescaler = 16
CCP1CON = (0x0c);        //0x0c enables PWM module CCP1
 CCPR1L = markspace;  //Load duty cycle into CCP1CON, PWM begins
 	while(1);                //Do nothing forever
}
