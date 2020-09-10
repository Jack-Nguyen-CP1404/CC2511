/* ###################################################################
**     Filename    : main.c
**     Project     : lab_4
**     Processor   : MK20DX128VLH5
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-08-19, 00:06, # CodeGen: 0
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
#include "RED_LED.h"
#include "BitIoLdd1.h"
#include "GREEN_LED.h"
#include "BitIoLdd2.h"
#include "BLUE_LED.h"
#include "BitIoLdd3.h"
#include "AS1.h"
#include "ASerialLdd1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include <string.h>
#include "UART_PDD.h"
/* User includes (#include below this line is not maintained by Processor Expert) */

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
void send_string(const char *str)
  {

  	int i, len;
  	len = strlen(str); // returns the number of chars in str
  	byte err;
  	for (i= 0; i< len; i++) {
  		// send this character
  		do {
  			err = AS1_SendChar(str[i]);
  		} while (err != ERR_OK);
  	}
  }

int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */

  byte err;
   char c;

//   char d = 'a'; // transmit the letter a
//   char e = 'x'; // transmit the letter x
//   char f = 'g'; // transmit the letter g
//   char h = 'b'; // transmit the letter b


   for (;;){

	   do{
		   err = AS1_RecvChar(&c); // component name = AS1
	   } while(err != ERR_OK); // the received byte is in the variable c

	   //Turn red LED on
	   if (c == 'r' || c == 'R')
	   {
		   // 	  RED_LED_ClrVal(); //Turn Red LED on
		   send_string("Program is starting\n\r");
		   send_string("Red LED is on\n\r"); // Transmit a string
		   RED_LED_NegVal();
	   }
	   //Turn green LED on
	   else if (c == 'g' || c == 'G')
	   {
		   GREEN_LED_NegVal();
		   send_string("Green LED is on\n\r");
	   }
	   //Turn Blue LED on
	   else if (c == 'b' || c == 'B')
	   {
		   BLUE_LED_NegVal();
		   send_string("Blue LED is on\n\r");
	   }
	   //   Turn all LED off
	   else {
		   send_string("Invalid input\n\r");

	   }

   }


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
