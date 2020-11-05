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

enum States{Start,begin,increment_press,increment_hold,increment_release,max,decrement_press,decrement_hold,decrement_release,min,reset}state;

void Tick() {
    unsigned char button_increment = ~PINA & 0x01;
    unsigned char button_decrement = ~PINA & 0x02;
    static unsigned char cntavail;

    switch(state){
        case Start:
           cntavail = 7;
           state = begin;
        break;
        case begin:
           if((button_increment) && (!button_decrement) && (cntavail<9)){
             state = increment_press;
           }
           else if((!button_increment) && (button_decrement) && (cntavail>0)){
             state = decrement_press;
           }
           else if((button_increment && button_decrement)){
             state = reset;
           }
           else{
             state = begin;
           }
        break;

        case increment_press:
	   if((!button_increment)){
             state = increment_release;
           }
           else {
             state = increment_hold;
           }
           
        break;

        case increment_hold:
	  if((button_increment)){
             state = increment_hold;
           }
           else {
             state = increment_release;
           }
           
        break;

        case increment_release:
           if(cntavail == 9){
             state = max;
           }
           else {
             state = begin;
           }
           
        break;

        case max:
             state = begin;
        break;

         case decrement_press:
	   if((!button_decrement)){
             state = decrement_release;
           }
           else {
             state = decrement_hold;
           }
           
        break;

        case decrement_hold:
	   if((button_decrement)){
             state = decrement_hold;
           }
           else {
             state = decrement_release;
           }
           
        break;

        case decrement_release:
           if(cntavail == 0){
             state = min;
           }
           else {
             state = begin;
           }
           
        break;

        case min:
             state = begin;
        break;

        case reset:
           if((!button_increment && !button_decrement)){
             state = begin;
           }
           else{
             state = reset;
           }
        break;

        default:
           state = Start;
        break;
    }
    switch(state){
        case Start:
           cntavail = 7;
        break;
        case begin:
        break;
        case increment_press:
           cntavail = cntavail +1;
        break;
        case increment_hold:
        break;
        case increment_release:
        break;
        case decrement_press:
           cntavail = cntavail -1;
        break;
        case decrement_hold:
        break;
        case decrement_release:
        break;
        case max:
        break;
        case min:
        break;
        case reset:
           cntavail =0;
        break;
        default:
        break;
    }
   PORTC = cntavail;
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
   
   
    
    state = Start;

    /* Insert your solution below */
    while (1) {
        Tick();

    }
    return 1;
}
