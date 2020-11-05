/*	Author: lab
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 * Demo Link: https://drive.google.com/drive/folders/1CgwR2gvNUYymDPUC98qPOQr6-UoJOLAX?usp=sharing
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{Start, allRed, allWhite, allGreen} state;

void Tick() {
    unsigned char button= ~PINA & 0x01;
    unsigned char led = 0x00;

    switch(state){
        case Start:
             if(button){
               state = allRed;
             }
             else{
               state = Start;
             }
        break;
        case allRed:
             if(button){
               state = allWhite;
             }
             else{
               state = allRed;
             }
        break;
        case allWhite:
             if(button){
               state = allGreen;
             }
             else{
               state = allWhite;
             }
        break;
        case allGreen:
          state = Start;
        break;

        default:
           state = Start;
        break;
    }
    switch(state){
        case Start:
             led = 0x00;
        break;
        case allRed:
             led = 0x24;
        break;
        case allWhite:
             led = 0x12;
        break;
        case allGreen:
             led = 0x09;
        break;
        default:
        break;
    }
   PORTB = led;
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
   
   
    
    state = Start;

    /* Insert your solution below */
    while (1) {
        Tick();

    }
    return 1;
}
