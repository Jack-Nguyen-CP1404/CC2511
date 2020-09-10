/* ###################################################################
**     Filename    : main.c
**     Project     : assignment_1
**     Processor   : MK20DX128VLH5
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-09-06, 20:16, # CodeGen: 0
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
#include "SW_BITIO.h"
#include "BitIoLdd1.h"
#include "LED1.h"
#include "BitIoLdd2.h"
#include "LED2.h"
#include "BitIoLdd3.h"
#include "LED3.h"
#include "BitIoLdd4.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

#include "stdio.h"
#include "stdlib.h"


/* User includes (#include below this line is not maintained by Processor Expert) */

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
  int number;
  for (;;)
  {
  if (SW_BITIO_GetVal())
  {
	  LED1_SetVal();
	  LED2_SetVal();
	  LED3_SetVal();
	  number = rand() % 7;
	  //001
	  if (number == 1)
	  {
		  LED1_ClrVal();
		  LED2_ClrVal();
	  }
	  //01
	  else if (number == 2)
	  {
		  LED1_ClrVal();
		  LED3_ClrVal();
	  }
	  //011
	  else if (number == 3)
	  {
		  LED1_ClrVal();
	  }
	  //100
	  else if (number == 4)
	  	  {
	  		  LED2_ClrVal();
	  		  LED3_ClrVal();
	  	  }
	  //101
	  else if (number == 5)
	  	  {
	  		  LED2_ClrVal();
	  	  }
	  //110
	  else if (number == 6)
	  	  {
	  		  LED3_ClrVal();
	  	  }
	  else if (number == 0)
	  	  {
	  		  LED1_ClrVal();
	  		  LED3_ClrVal();
	  		  LED2_ClrVal();
	  	  }
  }
  }
//  {
//	  for (;;)
//	  {
//		  for (counter = 0; counter < 7000000; counter++)
//		  {
//
//			  if (counter == 6000000)
//			  {
//				  LED1_SetVal();
//				  LED2_SetVal();
//				  LED3_ClrVal();
//			  }
//			  else if (counter == 5000000)
//			  {
//				  LED1_SetVal();
//				  LED3_SetVal();
//				  LED2_ClrVal();
//			  }
//			  else if (counter == 4000000)
//			  {
//				  LED1_SetVal();
//				  LED2_ClrVal();
//				  LED3_ClrVal();
//			  }
//			  else if (counter == 3000000)
//			  {
//				  LED1_ClrVal();
//				  LED2_SetVal();
//				  LED3_SetVal();
//			  }
//			  else if (counter == 2000000)
//			  {
//				  LED1_ClrVal();
//				  LED2_SetVal();
//				  LED3_ClrVal();
//			  }
//			  else if (counter == 1000000)
//			  {
//				  LED1_ClrVal();
//				  LED3_SetVal();
//				  LED2_ClrVal();
//			  }
//			  else if (counter == 0000000)
//			  {
//				  LED1_ClrVal();
//				  LED2_ClrVal();
//				  LED3_ClrVal();
//			  }
//		  }
//	  }
//  }

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
