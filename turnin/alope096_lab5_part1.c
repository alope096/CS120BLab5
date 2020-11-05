/*	Author: lab
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    
    DDRC = 0xFF; PORTC = 0x00;

    unsigned char fuelSensor = 0x00;
    unsigned char lowFuelSensor = 0x00;
    unsigned char ledOutput = 0x00;
   
    /* Insert your solution below */
    while (1) {
        fuelSensor = ~PINA & 0x0F;
        lowFuelSensor = 0x00;
        ledOutput = 0x00;
        
        if((fuelSensor == 0x01) || (fuelSensor == 0x02)){
            ledOutput = 0x20;
        }
        else if((fuelSensor == 0x03) || (fuelSensor == 0x04)){
            ledOutput = 0x30;
        }
        else if((fuelSensor == 0x05) || (fuelSensor == 0x06)){
            ledOutput = 0x38;
        }
        else if((fuelSensor == 0x07) || (fuelSensor == 0x08) || (fuelSensor == 0x09)){
            ledOutput = 0x3C;
        }
        else if((fuelSensor == 0x0A) || (fuelSensor == 0x0B) || (fuelSensor == 0x0C)){
            ledOutput = 0x3E;
        }
        else if((fuelSensor == 0x0D) || (fuelSensor == 0x0E) || (fuelSensor == 0x0F)){
            ledOutput = 0x3F;
        }
        else {
            ledOutput = 0x00;
        }

        if(fuelSensor <= 4){
           lowFuelSensor = 0x40;
        }
        else{
           lowFuelSensor = 0x00;
        }
       
        ledOutput = ledOutput | lowFuelSensor;
        PORTC = ledOutput;
    }
    return 1;
}
