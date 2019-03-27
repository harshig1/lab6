// Lab6.c
// Runs on LM4F120 or TM4C123
// Use SysTick interrupts to implement a 3-key digital piano
// MOOC lab 13 or EE319K lab6 starter
// Program written by: put your names here
// Date Created: 3/6/17 
// Last Modified: 3/5/18 
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********


#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "Sound.h"
#include "Piano.h"
#include "TExaS.h"
#include "DAC.h"
uint32_t previous;
uint32_t input;

// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts


void LED_Init(void){
volatile int delay;
SYSCTL_RCGCGPIO_R |= 0x20;
delay = 0; 
GPIO_PORTF_DIR_R |= 0x02;
GPIO_PORTF_DEN_R |= 0x02;
}



//code for testing dac
 /*int main(void){       
  unsigned long Data; // 0 to 15 DAC output
  //PLL_Init();         // like Program 4.6 in the book, 80 MHz
  DAC_Init();
  for(;;) {
    DAC_Out(Data);
    Data = 0x0F&(Data+1); // 0,1,2...,14,15,0,1,2,...
  }
}*/


//main code
  int main(void){   

  TExaS_Init(SW_PIN_PE3210,DAC_PIN_PB3210,ScopeOn);    // bus clock at 80 MHz
  Piano_Init();
  Sound_Init();
	LED_Init();
  // other initialization
  EnableInterrupts();
  while(1){ 
		input = Piano_In();
		if(input != previous){
			if(input == 0){
			Sound_Play(0);
			}
			else if(input == 1){
			Sound_Play(2841); //period for note a
			}
			else if (input == 2){
			Sound_Play(2531); //period for note b
			} 
			else if (input == 4){
			Sound_Play(3189); //period for note g
			}	 
	}
		previous = input;
	}	
}

