/* ###################################################################
**     Filename    : main.c
**     Project     : lab_9_RX
**     Processor   : MK20DX128VLH5
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-09-22, 16:51, # CodeGen: 0
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
#include "Term1.h"
#include "Inhr1.h"
#include "ASerialLdd1.h"
#include "AD1.h"
#include "AdcLdd1.h"
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
void delay1()
{
int i;
for(i = 0; i < 1000000; i++){}

}
/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */


	uint16 adc_previous, adc_current;
	word time;
	int adc_diff;

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  Term1_SendStr("Program starting...\r\n");
  //Calibrate the ADC before the first use
  AD1_Calibrate(TRUE);
  Term1_SendStr("Calibration finished.\r\n\r\n");

  //Read a light value
  AD1_Measure(TRUE);
  AD1_GetValue16(&adc_previous);

  for(;;)
  {

	  //Read second light value
	  AD1_Measure(TRUE);
	  AD1_GetValue16(&adc_current);

	  adc_diff = adc_current - adc_previous;
	  adc_previous = adc_current;

	  if(adc_diff < - 50000 )
	  {
		  // We have now detected a rising edge because more light means a smaller (4000) number compared to less light (6000)
		  FC321_Reset();

		  do
		  {

			  //Read a new light value in order to detect a falling edge
			  AD1_Measure(TRUE);
			  AD1_GetValue16(&adc_current);
			  //			  delay1();
			  delay1();
			  adc_diff = adc_current - adc_previous;
			  adc_previous = adc_current;

		  } while(adc_diff < 50000);

		  // we have detected a falling edge

		  FC321_GetTimeMS(&time);
		  Term1_SendStr("Pulse Width: ");
		  Term1_SendNum(time);
		  Term1_SendStr("ms \r\n");

	  }
	  delay(100);

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
