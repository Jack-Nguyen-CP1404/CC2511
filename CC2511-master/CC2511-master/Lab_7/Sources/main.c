/* ###################################################################
**     Filename    : main.c
**     Project     : lab_8
**     Processor   : MK20DX128VLH5
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-09-10, 20:40, # CodeGen: 0
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
#include "TU1.h"
#include "RED_PWM.h"
#include "PwmLdd1.h"
#include "GREEN_PWM.h"
#include "PwmLdd2.h"
#include "BLUE_PWM.h"
#include "PwmLdd3.h"
#include "Term1.h"
#include "Inhr1.h"
#include "ASerialLdd1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
/* User includes (#include below this line is not maintained by Processor Expert) */

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
//These are variables required for receiving command from user

volatile char buffer[100];
volatile uint8 index = 0;
volatile bool complete_command = false;


void draw_GUI()
{
	  // Set position to the first row first coloumn
	  Term1_MoveTo(1,1);
	  //Set foreground colour to cyan and background to black
	  Term1_SetColor(clYellow,clBlack);
	  //  Send string to the first line
	  Term1_SendStr("CC2511 Lab 7 ");

	  // Set position to the third row
	  Term1_MoveTo(1,3);
	  //Set foreground colour to cyan and background to black
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr("+--[ PWM Status ]--+");
	  Term1_MoveTo(23,3);
	  Term1_SetColor(clBlack,clBlack);
	  Term1_MoveTo(24,3);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr("+----------------[ How to use ]---------------+");

	  // Set position to 4th row
	  Term1_MoveTo(1,4);
	  //Set foreground colour to cyan and background to black
	  Term1_SetColor(clBlack,clBlack);
	  Term1_SendStr("                                                                      ");
	  Term1_MoveTo(1,4);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(20,4);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(24,4);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(70,4);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");

	  // Set position to 5th row

	  Term1_MoveTo(1,5);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(3,5);
	  Term1_SetColor(clWhite, clBlack);
	  Term1_SendStr("  Red:                        Type the following commands:            ");
	  Term1_MoveTo(20,5);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(24,5);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(70,5);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");

	  // Set position to 6th row

	  Term1_MoveTo(1,6);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(3,6);
	  Term1_SetColor(clWhite, clBlack);
	  Term1_SendStr("  Green:              > green  n   Set the Green PWM ratio to n       ");
	  Term1_MoveTo(20,6);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(24,6);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(70,6);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");

	  // Set position to 7th row

	  Term1_MoveTo(1,7);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(3,7);
	  Term1_SetColor(clWhite, clBlack);
	  Term1_SendStr("  Blue:               > blue  n   Set the Blue PWM ratio to n        ");
	  Term1_MoveTo(20,7);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(24,7);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(70,7);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");

	  // Set position to 8th row

	  Term1_MoveTo(1,8);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(3,8);
	  Term1_SetColor(clWhite, clBlack);
	  Term1_SendStr("                      > red  n  Set the Red PWM ratio to n           ");
	  Term1_MoveTo(20,8);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(24,8);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(70,8);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");


	  // Set position to 9th row

	  Term1_MoveTo(1,9);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(3,9);
	  Term1_SetColor(clWhite, clBlack);
	  Term1_SendStr("                      > off      Turn all LEDs off                           ");
	  Term1_MoveTo(20,9);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(24,9);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(70,9);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");


	  // Set position to 10th row
	  Term1_MoveTo(1,10);
	  //Set foreground colour to cyan and background to black
	  Term1_SetColor(clBlack,clBlack);
	  Term1_SendStr("                                                                      ");
	  Term1_MoveTo(1,10);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(20,10);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(24,10);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(70,10);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");

	  // Set position to the 11th row
	   Term1_MoveTo(1,11);
	   //Set foreground colour to cyan and background to black
	   Term1_SetColor(clBlack,clCyan);
	   Term1_SendStr("                    ");
	   Term1_MoveTo(23,11);
	   Term1_SetColor(clBlack,clBlack);
	   Term1_MoveTo(24,11);
	   Term1_SetColor(clBlack,clCyan);
	   Term1_SendStr("                                               ");

	   Term1_MoveTo(1,14);
	   //Set foreground colour to cyan and background to black
	   Term1_SetColor(clWhite,clBlack);
	   //  Send string to the first line
	   Term1_SendStr("Command prompt:");

	   Term1_MoveTo(1,15);
	     //Set foreground colour to cyan and background to black
	     Term1_SetColor(clWhite,clBlack);
	     //  Send string to the first line
	     Term1_SendStr("> ");
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
	draw_GUI();
	BLUE_PWM_SetRatio8(0);
	GREEN_PWM_SetRatio8(255);
	RED_PWM_SetRatio8(255);
	int16 val;
	for(;;)
	{
		while (!complete_command)
		{
			__asm ("wfi");
			//		Processing the received char and complete commmand
		}
		if(complete_command)
		{

			if (sscanf((char *)buffer, "red %hu", &val) > 0) {
				// command was PWM
				RED_PWM_SetRatio8(val);
				complete_command = true;
				// Update value for PWM
				Term1_MoveTo(12,5);
				Term1_SendStr("      ");
				Term1_MoveTo(14,5);
				Term1_SendNum(val);
			}
			else if (sscanf((char *) buffer, "green %hu", &val) > 0) {
				// command was PWM
				GREEN_PWM_SetRatio8(val);
				complete_command = true;

				// Update value for PWM
				Term1_MoveTo(14,6);
				Term1_SendStr("      ");
				Term1_MoveTo(14,6);
				Term1_SendNum(val);

			}
			else if (sscanf((char *)buffer, "blue %hu", &val) > 0) {
				// command was PWM
				BLUE_PWM_SetRatio8(val);
				complete_command = true;

				// Update value for PWM
				Term1_MoveTo(14,7);
				Term1_SendStr("   ");
				Term1_MoveTo(14,7);
				Term1_SendNum(val);
			}
			else if (strcmp((char *) buffer, "\f"))
			{
				draw_GUI();
				complete_command = true;
			}
			else if (0 == strcmp((char *) buffer, "off"))
			 {
				// buffer contains stop
				RED_PWM_SetRatio8(0);
				GREEN_PWM_SetRatio8(0);
				BLUE_PWM_SetRatio8(0);
				val = 0;

			}
			complete_command = false;
			index = 0;
			// Clear the command prompt
			Term1_MoveTo(1,15);
			Term1_SendStr(">                    ");
			Term1_MoveTo(3,15);

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
