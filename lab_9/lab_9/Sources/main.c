/* ###################################################################
**     Filename    : main.c
**     Project     : lab_9_TX
**     Processor   : MK20DX128VLH5
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-09-22, 16:15, # CodeGen: 0
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
#include "FC321.h"
#include "RealTimeLdd1.h"
#include "TU1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */

void delay(word delay_ms)
{
	word time;
	FC321_Reset();
	do
	{
		__asm("wfi"); // the micro-controller would be in low power mode

		FC321_GetTimeMS(&time);
	}while(time < delay_ms);
}
/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  word time;
//  Turn LEDs off
  RED_LED_SetVal();
  GREEN_LED_SetVal();
  BLUE_LED_SetVal();

  for(;;)
  {
	  for (int i = 0; i < 5; i++) // Send 500ms pulses of white light
	  {
//		  Turn on LEDs
		  BLUE_LED_ClrVal();
		  GREEN_LED_ClrVal();
		  RED_LED_ClrVal();
//		  reset timer
		delay(500);
		  //  Turn LEDs off
		  RED_LED_SetVal();
		  GREEN_LED_SetVal();
		  BLUE_LED_SetVal();
		delay(500);
	  }


	 	  for (int i = 0; i < 5; i++) // Send 500ms pulses of white light
	 	  {
	 //		  Turn on LEDs
	 		  BLUE_LED_ClrVal();
	 		  GREEN_LED_ClrVal();
	 		  RED_LED_ClrVal();
	 //		  reset timer
	 		delay(100);
	 		  //  Turn LEDs off
	 		  RED_LED_SetVal();
	 		  GREEN_LED_SetVal();
	 		  BLUE_LED_SetVal();
	 		delay(900);
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
