/* ###################################################################
**     Filename    : main.c
**     Project     : lab_8.1
**     Processor   : MK20DX128VLH5
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-09-15, 16:23, # CodeGen: 0
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
#include "RED_PWM.h"
#include "PwmLdd1.h"
#include "TU1.h"
#include "BLUE_PWM.h"
#include "PwmLdd2.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
void delay()
{
int i;
for(i = 0; i < 1000000; i++){}

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

  // Calibrate the ADC before the first use
  Term1_SendStr("Program starting...\r\n)");
  AD1_Calibrate(TRUE);
  Term1_SendStr("Calibration finished...\r\n)");
  uint16 adc_result;
  float PWM;
  RED_PWM_SetRatio16(0);
  BLUE_PWM_SetRatio16(0);
  for(;;)
  {
	  //	  Do ADC measurement
	  AD1_Measure(TRUE);
	  AD1_GetValue16(&adc_result);
	  Term1_SendFloatNum(adc_result);
	  Term1_SendStr("\r\n");
	  delay();

//	  Convert ADC value to a PWM ratio that can set the LED light to be fully when light sensor is exposed.
	  PWM = -((float)64700/(64700-3400)) * (adc_result - 3500) + 64700;
//	  RED_PWM_SetRatio16(PWM);
	  if (PWM <0)
	  {
		  PWM = 0;

	  }
	  RED_PWM_SetRatio16(PWM);

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
