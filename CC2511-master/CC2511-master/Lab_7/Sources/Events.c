/* ###################################################################
**     Filename    : Events.c
**     Project     : lab_8
**     Processor   : MK20DX128VLH5
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-09-10, 20:40, # CodeGen: 0
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

#ifdef __cplusplus
extern "C" {
#endif 
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

//These are variables required for receiving command from user
extern volatile char buffer[100];
extern volatile uint8 index;
extern volatile bool complete_command;

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

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

void Inhr1_OnRxChar(void)
{
  /* Write your code here ... */
	char c;
		if (ERR_OK == Inhr1_RecvChar(&c))
		{
			// A new character received and needs to be processed
			switch (c)
			{
			case '\r':
					// New line was received. We accept it if it has been entered.
							if (index > 0)
							{
								buffer[index] = '\0'; //insert a trailing null to terminate the latest string entered by user
								complete_command = true;

							}
							break;

			default:
				if(index < 99)
				{
					buffer[index] = c;
					index++;
					Term1_SendChar(c);
				}

			}
		}
}






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
