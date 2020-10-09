/**
 * CC2511 Lab 10
 */

	.text 			/* The "text" section of the executable is where code is placed. */
	.align	2 		/* Make sure the starting address is a multiple of 2. */
	.global	main 	/* Declare "main" as a global symbol (callable from other files). */
  .syntax unified /* Enable Thumb2 instruction set support */

/* Main function */
main:
	push {lr}  /* The return address is in the "link register" (lr). Preserve it by pushing it to the stack. */

	/* Write your code here */
	// we want to turn on ibe LED on/off with delay
	// Enable the clock for the port control module
	// SIM_SCGC5 |= 0x3e00;
	//Load sim SCGC5 adress into r1
	//mov r1 with 4004_8038h
	movw r1, #0x8038
	movt r1, #0x4004
	// load 4004_8038h
	//ldr r1, = 4004_8038h
	// store the value that we need to write to SIM_CSGC5 in r
	ldr r2, =0x3e00;
	// write the value in r2 to the memory address that r1 point to
	str r2, [r1]

	// Select the GPIO mode for the green LED
	//PORTD_PCR4 = 0x100
	ldr r1, =0x4004C010 //Load the address
	ldr r2, =0 // PORTD_CR4 = 0x100
	str r2, [r1]

	// Select the GPIO mode for the blue LED
	ldr r1, =0x40049008 //Load the address
	ldr r2, =0 // PORTA_PCR2 = 0x100
	str r2, [r1]

	// Select GPIO mode for the red LED pin PTC3
	//Set the GPIO mode for the red LED by doing the following
	// PORTC_PCR3 = 0x100;
	.equ PORTC_PCR3, 0x4004B00C
	ldr r1, =PORTC_PCR3
	ldr r2, =0x100
	str r2, [r1]

	// Select output data direction for the red LED
	// GPIOC_PDDR = (1 << 3); // set PTC3 to output
	.equ GPIOC_PDDR, 0x400FF094
	ldr r1, =GPIOC_PDDR
	ldr r2, =0x8
	str r2, [r1]

main_loop:

	// Set the data output register to zero and one to turn it on or off
	.equ GPIOC_PDOR, 0x400FF080
	ldr r1, =GPIOC_PDOR
	ldr r2, =0
	str r2, [r1]
	ldr r0, =1000000 /* r0 = 1000000 */
myloop1:
	sub r0, #1 /* r0 -= 1 */
	cmp r0, #0 /* is r0 equal to zero? */
	bne myloop1/* branch if not equal */
	// Delay for a while
	ldr r2, =0b1000 // Write all zeros to the register to turn the LED off
	str r2, [r1]
	// delay for a while
	ldr r0, =1000000 /* r0 = 1000000 */

myloop2:
	sub r0, #1 /* r0 -= 1 */
	cmp r0, #0 /* is r0 equal to zero? */
	bne myloop2/* branch if not equal */
	b main_loop


	pop {pc}  /* Return from this function, by popping the return address into the program counter (pc) */
