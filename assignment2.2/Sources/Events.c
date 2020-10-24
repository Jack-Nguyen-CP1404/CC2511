/* ###################################################################
**     Filename    : Events.c
**     Project     : assignment2.2
**     Processor   : MK20DX128VLH5
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-10-18, 16:21, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include<stdio.h>

#ifdef __cplusplus
extern "C" {
#endif 

//extern volatile char buffer[100];
//extern volatile uint8 index;
//extern volatile bool complete_command;
/* User includes (#include below this line is not maintained by Processor Expert) */

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MK20DX128EX5]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  Inhr1_OnRxChar (module Events)
**
**     Component   :  Inhr1 [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
extern volatile char buffer[100];
extern volatile int index;
extern volatile bool command_complete;
extern volatile bool sendMode;
void Inhr1_OnRxChar(void)
{	//Group 1
	char c;
			Term1_ReadChar(&c);
			buffer[index] = c;
			if (sendMode == 0){
			index++;
			buffer[index] = '\0';
				command_complete = 1;
				index = 0;
			}else if(sendMode == 1){
				if(c == '\r'){
					index = 0;
					command_complete = 1;
				}
				else{
					index++;
				}
				Term1_SendChar(c);
			}
	}


/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

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
