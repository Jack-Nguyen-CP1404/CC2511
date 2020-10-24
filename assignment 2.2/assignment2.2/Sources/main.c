/* ###################################################################
**     Filename    : main.c
**     Project     : assignment2.2
**     Processor   : MK20DX128VLH5
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-10-18, 16:21, # CodeGen: 0
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
#include "PWM1.h"
#include "PwmLdd1.h"
#include "TU1.h"
#include "PWM4.h"
#include "PwmLdd2.h"
#include "PWM2.h"
#include "PwmLdd3.h"
#include "TU2.h"
#include "PWM3.h"
#include "PwmLdd4.h"
#include "Term1.h"
#include "Inhr1.h"
#include "ASerialLdd1.h"
#include "Direction1.h"
#include "BitIoLdd1.h"
#include "Direction2.h"
#include "BitIoLdd2.h"
#include "Direction3.h"
#include "BitIoLdd3.h"
#include "Mode0.h"
#include "BitIoLdd4.h"
#include "Mode1.h"
#include "BitIoLdd5.h"
#include "Mode2.h"
#include "BitIoLdd6.h"
#include "nENBL.h"
#include "BitIoLdd7.h"
#include "nSleep.h"
#include "BitIoLdd8.h"
#include "nReset.h"
#include "BitIoLdd9.h"
#include "nHome.h"
#include "BitIoLdd10.h"
#include "nFault.h"
#include "BitIoLdd11.h"
#include "Decay.h"
#include "BitIoLdd12.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include<stdio.h>
/* User includes (#include below this line is not maintained by Processor Expert) */

//These are variables required for receiving command from user
volatile char buffer [100];
volatile uint8 index = 0;
volatile bool complete_command = false;

void draw_GUI()
{
	 //Draw the GUI for user i.e, the instructions on how to control the motors
	  Term1_MoveTo(1,1);
	  Term1_SendStr("CC2511 Assignment 2 Group 1");
	  Term1_MoveTo(1,2);
	  Term1_SendStr("How to control the machine");
	  Term1_MoveTo(1,3);
	  Term1_SendStr("Positive X Direction:  D");
	  Term1_MoveTo(1,4);
	  Term1_SendStr("Negative X Direction:  A");
	  Term1_MoveTo(1,5);
	  Term1_SendStr("Positive Y Direction:  W");
	  Term1_MoveTo(1,6);
	  Term1_SendStr("Negative Y Direction:  S");
	  Term1_MoveTo(1,7);
	  Term1_SendStr("Emergency Stop:  Spacebar");
	  Term1_MoveTo(1,8);
	  Term1_SendStr("Rase Height of Spindle:   Q");
	  Term1_MoveTo(1,9);
	  Term1_SendStr("Lower Height of Spindle:  E");
	  Term1_MoveTo(1,11);
	  Term1_SendStr("Change the step size MODE of the motors:  M");
	  Term1_MoveTo(1,12);
	  Term1_SendStr("Automatic Control Toggle:  C");	//at the moment i cant think of a way to get custom modes working an automatic control, so pherhaps keep it constant for automatic
	  //not all the entries in the GUI are alligned yet, but that will be easy to fix
	  //Command Prompt Code
	  Term1_MoveTo(1,13);
	  Term1_SendStr("Set Custom Spindle RPM:    R");		//if you guys can think of a better button for this, by all means change it
	  Term1_MoveTo(1,20);
	  Term1_SendStr("Command Prompt:");
	  Term1_MoveTo(1,21);	//these are very low down in the GUI only temporarily
	  Term1_SendStr("> ");
	  //End command Prompt Code
}


/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
	int16 val;
	const int MOTOR_ON1 = 32768;	//these two values is because of the difference in FTMs
	const int MOTOR_ON2 = 16384;
	const int MOTOR_OFF = 0;

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */

  draw_GUI();

  //Turn off all motors from the beginning
   PWM1_SetRatio16(0);	//X
   PWM2_SetRatio16(0);	//Y
   PWM3_SetRatio16(0);	//Z
   PWM4_SetRatio16(0);	//Spindle motor

   for(;;)
   {
  	 while (!complete_command)
  	 {
  		 __asm ("wfi");
  	 }
  	 //Processing the received char and complete command
  	 if(complete_command)
  	 {
  //		 When user type in following command it will turn or move stepper motor 1,2,3 on as desired

  		 if (0 == strcmp((char *)buffer, "motor1 on"))
  		 {
  			 //Turn on stepper motor 1
  			 PWM1_SetRatio16(MOTOR_ON1);
  			 if (0 == strcmp((char *)buffer, "motor1 move left"))
  				 Direction1_ClrVal();
  			 else if (0 == strcmp((char *)buffer, "motor1 move right"))
  				 Direction1_SetVal();
  			 else if (0 == strcmp((char *)buffer, "motor1 off"))
  				 PWM1_SetRatio16(MOTOR_OFF);
  		 }
  		 else if (0 == strcmp((char *)buffer, "motor2 on"))
  		 {
  			 PWM2_SetRatio16(MOTOR_ON2);
  			 if (0 == strcmp((char *)buffer, "motor2 move forward"))
  				 Direction2_ClrVal();
  			 else if (0 == strcmp((char *)buffer, "motor2 move backward"))
  				 Direction2_SetVal(); //To move opposite direction may be use getval I am not too sure here
  			 else if (0 == strcmp((char *)buffer, "motor2 off"))
  				 PWM2_SetRatio16(MOTOR_OFF);
  		 }
  		 else if (0 == strcmp((char *)buffer, "motor3 on"))
  		 {
  			 PWM3_SetRatio16(MOTOR_ON2);
  			 if (0 == strcmp((char *)buffer, "motor3 move up"))
  				 Direction3_ClrVal();
  			 else if (0 == strcmp((char *)buffer, "motor3 move down"))
  				 Direction3_SetVal();
  			 else if (0 == strcmp((char *)buffer, "motor3 off"))
  				 PWM3_SetRatio16(MOTOR_OFF);
  		 }
  		 //Change speed of DC motor as desired
  		 else if (sscanf((char *) buffer, "DC %hu", &val) > 0)
  			 PWM4_SetRatio16(val);
  		 else if (0 == strcmp((char *) buffer, "off"))
  		 {
  			 // buffer contains stop
  			 PWM1_SetRatio16(MOTOR_OFF);
  			 PWM2_SetRatio16(MOTOR_OFF);
  			 PWM3_SetRatio16(MOTOR_OFF);
  			 PWM4_SetRatio16(MOTOR_OFF);
  			 val = 0;

  		 }
  		complete_command = false;
  		index = 0;
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
