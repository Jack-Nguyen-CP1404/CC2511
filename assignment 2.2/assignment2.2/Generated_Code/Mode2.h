/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : Mode2.h
**     Project     : assignment2.2
**     Processor   : MK20DX128VLH5
**     Component   : BitIO
**     Version     : Component 02.086, Driver 01.00, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-10-18, 19:48, # CodeGen: 8
**     Abstract    :
**         This component "BitIO" implements an one-bit input/output.
**         It uses one bit/pin of a port.
**         Methods of this component are mostly implemented as a macros
**         (if supported by target language and compiler).
**     Settings    :
**          Component name                                 : Mode2
**          Pin for I/O                                    : PTD3/SPI0_SIN/UART2_TX
**          Pin signal                                     : 
**          BitIO_LDD                                      : BitIO_LDD
**          Direction                                      : Input/Output
**          Initialization                                 : 
**            Init. direction                              : Output
**            Init. value                                  : 1
**          Safe mode                                      : yes
**          Optimization for                               : speed
**     Contents    :
**         SetDir - void Mode2_SetDir(bool Dir);
**         GetVal - bool Mode2_GetVal(void);
**         PutVal - void Mode2_PutVal(bool Val);
**         ClrVal - void Mode2_ClrVal(void);
**         SetVal - void Mode2_SetVal(void);
**
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file Mode2.h
** @version 01.00
** @brief
**         This component "BitIO" implements an one-bit input/output.
**         It uses one bit/pin of a port.
**         Methods of this component are mostly implemented as a macros
**         (if supported by target language and compiler).
*/         
/*!
**  @addtogroup Mode2_module Mode2 module documentation
**  @{
*/         

#ifndef __Mode2_H
#define __Mode2_H

/* MODULE Mode2. */

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited beans */
#include "BitIoLdd6.h"

#include "Cpu.h"

#ifdef __cplusplus
extern "C" {
#endif 




/*
** ===================================================================
**     Method      :  Mode2_SetDir (component BitIO)
**     Description :
**         This method sets direction of the component.
**     Parameters  :
**         NAME       - DESCRIPTION
**         Dir        - Direction to set (FALSE or TRUE)
**                      FALSE = Input, TRUE = Output
**     Returns     : Nothing
** ===================================================================
*/
#define Mode2_SetDir(Dir) (BitIoLdd6_SetDir(BitIoLdd6_DeviceData, (Dir)))

/*
** ===================================================================
**     Method      :  Mode2_GetVal (component BitIO)
**     Description :
**         This method returns an input value.
**           a) direction = Input  : reads the input value from the
**                                   pin and returns it
**           b) direction = Output : returns the last written value
**     Parameters  : None
**     Returns     :
**         ---             - Input value. Possible values:
**                           FALSE - logical "0" (Low level)
**                           TRUE - logical "1" (High level)

** ===================================================================
*/
#define Mode2_GetVal() (BitIoLdd6_GetVal(BitIoLdd6_DeviceData))

/*
** ===================================================================
**     Method      :  Mode2_PutVal (component BitIO)
**     Description :
**         This method writes the new output value.
**           a) direction = Input  : sets the new output value;
**                                   this operation will be shown on
**                                   output after the direction has
**                                   been switched to output
**                                   (SetDir(TRUE);)
**           b) direction = Output : directly writes the value to the
**                                   appropriate pin
**     Parameters  :
**         NAME       - DESCRIPTION
**         Val             - Output value. Possible values:
**                           FALSE - logical "0" (Low level)
**                           TRUE - logical "1" (High level)
**     Returns     : Nothing
** ===================================================================
*/
#define Mode2_PutVal(Val) (BitIoLdd6_PutVal(BitIoLdd6_DeviceData, (Val)))

/*
** ===================================================================
**     Method      :  Mode2_ClrVal (component BitIO)
**     Description :
**         This method clears (sets to zero) the output value.
**           a) direction = Input  : sets the output value to "0";
**                                   this operation will be shown on
**                                   output after the direction has
**                                   been switched to output
**                                   (SetDir(TRUE);)
**           b) direction = Output : directly writes "0" to the
**                                   appropriate pin
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#define Mode2_ClrVal() (BitIoLdd6_ClrVal(BitIoLdd6_DeviceData))

/*
** ===================================================================
**     Method      :  Mode2_SetVal (component BitIO)
**     Description :
**         This method sets (sets to one) the output value.
**           a) direction = Input  : sets the output value to "1";
**                                   this operation will be shown on
**                                   output after the direction has
**                                   been switched to output
**                                   (SetDir(TRUE);)
**           b) direction = Output : directly writes "1" to the
**                                   appropriate pin
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#define Mode2_SetVal() (BitIoLdd6_SetVal(BitIoLdd6_DeviceData))

/* END Mode2. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __Mode2_H */
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