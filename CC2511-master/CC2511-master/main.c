/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "Cpu.h"
#include "Events.h"
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "MK20D5.h"
#include "MK20D5_simple.h"
#include <stdbool.h>

void control_LED(bool R, bool G, bool B)
{
	// Turn LED on or off

	GPIOD_PDOR = (R<<4); // Turn red LED on
	GPIOA_PDOR = (B<<2) ; // Turn blue LED on
	GPIOC_PDOR = (G << 3); //Turn Green on

	// Flash LED
	int counter;
		for (counter = 0; counter < 10000000; counter++) {}
					// spin
}

int main(void)
{
	// Enable the clock for the port control module
//	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK;
	// Enable the clock for the port control module
	SIM_SCGC5 |= 0x3e00;
	// Initialize the red LED
	PORTC_PCR3 = 0x100; // Select GPIO mode
	GPIOC_PDDR = (1 << 3); // set PTC3 to output
	// Initialize the green LED
	PORTD_PCR4 = 0x100; // Select GPIO mode
	GPIOD_PDDR = (1 << 4); // set PTC3 to output
	// Initialize the blue LED
	PORTA_PCR2 = 0x100; // Select GPIO mode
	GPIOA_PDDR = (1 << 2); // set PTC3 to output
	for (;;){
	control_LED (0, 0, 1);
	control_LED (0, 1, 0);
	control_LED (0, 1, 1);
	control_LED (1, 0, 0);
	control_LED (1, 0, 1);
	control_LED (1, 1, 0);
	control_LED (1, 1, 1);
	control_LED (0, 0, 0);
	}

    return 0;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
