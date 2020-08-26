/* ###################################################################
**     Filename    : main.c
**     Project     : lab5
**     Processor   : MK20DX128VLH5
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-08-26, 11:58, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "In.h"
#include "BitIoLdd1.h"
#include "BLUE_LED.h"
#include "BitIoLdd2.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "RED_PWM.h"
#include "PwmLdd1.h"
#include "TU1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */

void part_1()
{
	  byte err;
	  char c;

	  for(;;)
	  {

		  if (In_GetVal()) //the input pin has been high
			  BLUE_LED_ClrVal(); //turn BLUE LED on
		  else
			  BLUE_LED_SetVal(); //otherwise turn BLUE LED off

		  do{
		  		   err = AS1_RecvChar(&c); // component name = AS1
		  	   } while(err != ERR_OK); // the received byte is in the variable c
		  if (c== ' ')
		  {
			PORTC_PCR0 ^= 0b11; // set PTC0 pullup of resistor to be active

		  }

	//	  check if a space character is received from the keyboard over a serial port
	//	  if that the case ....set PTC0 pullup resistor to be active
	//	  PORTC_PCR0 = 0b11;
	  }

	}


/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
	byte err;
	char c;
	int ratio;
	for (;;){

		do{
			err = AS1_RecvChar(&c); // component name = AS1
		} while(err != ERR_OK); // the received byte is in the variable c

		//Adjust LED brightness

		if (c == 'r' )
			ratio += 10; // Increase brightness
		else if (c== 'R')
			ratio -= 10; // Decrease brightness
		if (ratio > 255)
					ratio =255;
				else if (ratio < 0)
					ratio = 0;
		RED_PWM_SetRatio8(ratio);



//			send_string("Program is starting\n\r");
//			send_string("Red LED is on\n\r"); // Transmit a string
//			RED_LED_NegVal();
		}

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */




  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
