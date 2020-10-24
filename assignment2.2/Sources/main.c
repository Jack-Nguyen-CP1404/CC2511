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
#include "EFil1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <math.h>	//these are needed for comparing strings

static const double PWM2_PERIOD = 6.25;
/* User includes (#include below this line is not maintained by Processor Expert) */

//These are variables required for receiving command from user
volatile char buffer [100];
volatile int index;
volatile bool command_complete;
volatile bool sendMode= false;

volatile bool complete_command = false;	//dont know if we need this
const int MOTOR_ON1;	//these two values is because of the difference in FTMs
const int MOTOR_ON2;
const int MOTOR_OFF = 0;
//every variable benether this aidan added
volatile bool auto_mode = 0;
volatile int current_mode;
volatile bool X_on, Y_on, Z_on = 0;	//i think for elegance sake name these XYZ
//these variables will be used in calculating distance
volatile float radius = 40;	//this value is in millimetres, it is a float because it will be multiplied by numbers with lots of decimal places
//volatile float x_distance, y_distance;
volatile char read_info[10][3];	//this is the 2d array that will be read to holding the drawing info, 3 across 10 down

int a_pressed; //might need to change X_pressed variable to bool later, no need to at the moment however
int d_pressed;
int s_pressed;
int w_pressed;
int c_pressed;
int e_pressed;
int q_pressed;
int x_distance, y_distance, z_distance, i;
int x_time_to_move, y_time_to_move, z_time_to_move;
uint16 RPM;


/*
void test_function()
{
	int i;
	PWM2_SetRatio16(MOTOR_ON2);
	for (i=0;i<test_var;i++){}
	PWM2_SetRatio16(0);

}
*/
void read_text_file()
{
	char* filename = "E:\Test location"; //this will be in a different spot for whoever is testing.
	FILE *fp = fopen(filename,"r");		//open the file named "text.txt" in read mode

	int j;
	for (j=0; j<10; j++)	//while the file "fp" is not at the end of the file, read in each line
	{
		int i;
		for (i=0; i<3; i++)
			{
				read_info[j][i];
			}
	}
	fclose(fp);
}

void move_position(float x_distance, float y_distance, float z_distance, int* x_time_to_move, int* y_time_to_move, int* z_time_to_move)
{
	float dist_per_step;
	float x_amount_of_steps,y_amount_of_steps, z_amount_of_steps;
	int x_time_of_rotation, y_time_of_rotation, z_time_of_rotation, i;


	if (current_mode == 1)
	{
		//step angle in mode 1 is 0.0314159 radians
		dist_per_step = radius * 0.0314159;
	}
	else if (current_mode == 2)
		{
			//step angle in mode 2 is 0.01570795 radians
			dist_per_step = radius * 0.0157095;
		}
	else if (current_mode == 3)
		{
			//step angle in mode 3 is 0.007853975 radians
			dist_per_step = radius * 0.007853975;
		}
	else if (current_mode == 4)
		{
			//step angle in mode 4 is 0.0039269875 radians
			dist_per_step = radius * 0.0039269875;
		}
	else if (current_mode == 5)
		{
			//step angle in mode 5 is 0.00196349375 radians
			dist_per_step = radius * 0.00196349375;		}
	else if (current_mode == 6)
	{
		//step angle in mode 6 is 0.00098174687 radians
		dist_per_step = radius * 0.00098174687;
	}
	// Find number of steps in X, Y, Z direction
	x_amount_of_steps = x_distance / dist_per_step;
	y_amount_of_steps = y_distance / dist_per_step;
	z_amount_of_steps = z_distance / dist_per_step;

	//Find time of rotation (PWM = 6.25us)
	x_time_of_rotation = round(x_amount_of_steps * PWM2_PERIOD);//because time_of_rotation is an int, and the other two are floats, i hope that the int rounds to the nearest hole number (//round is in a c library that i need to include)
	y_time_of_rotation = round(y_amount_of_steps * PWM2_PERIOD);
	z_time_of_rotation = round(z_amount_of_steps * PWM2_PERIOD);

	// Time for the motor to move X, Y, Z distance
	*x_time_to_move = x_time_of_rotation * 50000;
	*y_time_to_move = y_time_of_rotation * 50000;
	*z_time_to_move = z_time_of_rotation * 50000;
}

void mode_change()
{
	Term1_MoveTo(1,1);		//when we can test the GUI, the start of these lines will go where the "Command Prompt" bit is in the main GUI, once this mode selection is finished
	Term1_Cls();			//it is all cleared
	Term1_MoveTo(1,2);
	Term1_SendStr("Choose Step Stepper Size");
	Term1_MoveTo(1,3);
	Term1_SendStr("Size 1: Full Step");
	Term1_MoveTo(1,4);
	Term1_SendStr("Size 2: 1 Half Step");
	Term1_MoveTo(1,5);
	Term1_SendStr("Size 3: 1 Quarter Step");
	Term1_MoveTo(1,6);
	Term1_SendStr("Size 4: 1 Eighth Step");
	Term1_MoveTo(1,7);
	Term1_SendStr("Size 4: 1 Sixteenth Step");
	Term1_MoveTo(1,8);
	Term1_SendStr("Size 5: 1 Thirty Second Step");
	Term1_MoveTo(1,9);
	Term1_SendStr("Cancel Changing Stepper Size: Any other button");
	while (!command_complete)
	  	 {
	  		 __asm ("wfi");
	  	 }
	command_complete = 0;
	if	(0 == strcmp((char*)buffer, "1"))
	{
		Mode0_SetVal();	//0
		Mode1_SetVal();	//0
		Mode2_SetVal();	//0
		current_mode = 1;
	}
	else if (0 == strcmp((char*)buffer, "2"))
	{
		Mode0_ClrVal();	//1
		Mode1_SetVal();	//0
		Mode2_SetVal();	//0
		current_mode = 2;
	}
	else if (0 == strcmp((char*)buffer, "3"))
	{
		Mode0_SetVal();	//0
		Mode1_ClrVal();	//1
		Mode2_SetVal();	//0
		current_mode = 3;
	}
	else if (0 == strcmp((char*)buffer, "4"))
	{
		Mode0_ClrVal();	//1
		Mode1_ClrVal();	//1
		Mode2_SetVal();	//0
		current_mode = 4;
	}
	else if (0 == strcmp((char*)buffer, "5"))
	{
		Mode0_SetVal();	//0
		Mode1_SetVal();	//0
		Mode2_ClrVal();	//1
		current_mode = 5;
	}
	else if (0 == strcmp((char*)buffer, "6"))
	{
		Mode0_ClrVal();	//1
		Mode1_SetVal();	//0
		Mode2_ClrVal();	//1
		current_mode = 6;
	}
	else
	{
		//itentionally leave this clear
	}
	Term1_Cls();


	//the values used for modes were taken from the datasheet website for the driver https://www.ti.com/lit/ds/symlink/drv8825.pdf page 13
}

void draw_GUI()
{
	 //Draw the GUI for user i.e, the instructions on how to control the motors
	  Term1_MoveTo(1,1);
	  Term1_SetColor(clYellow,clBlack);
	  Term1_SendStr("CC2511 Assignment 2 Group 1");

	  Term1_MoveTo(1,3);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr("+-[Position status]-+");
	  Term1_MoveTo(23,3);
	  Term1_SetColor(clBlack,clBlack);
	  Term1_MoveTo(24,3);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr("+----------------[ How to use ]---------------+");

	  Term1_MoveTo(1,4);
	  Term1_SetColor(clBlack,clBlack);
	  Term1_SendStr("                                                                      ");
	  Term1_MoveTo(1,4);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(21,4);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(24,4);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(70,4);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");

	  // Set position to 5th row

	  Term1_MoveTo(1,5);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(3,5);
	  Term1_SetColor(clWhite, clBlack);
	  Term1_SendStr("Coordinates:               Type the following commands:                 ");
	  Term1_MoveTo(21,5);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(24,5);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(70,5);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");

	  Term1_MoveTo(1,6);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(3,6);
	  Term1_SetColor(clWhite, clBlack);
	  Term1_SendStr("X position:                > Positive X Direction:      D               ");
	  Term1_MoveTo(21,6);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(24,6);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(70,6);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");


	  Term1_MoveTo(1,7);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(3,7);
	  Term1_SetColor(clWhite, clBlack);
	  Term1_SendStr("Y position:                > Negative X Direction:      A               ");
	  Term1_MoveTo(21,7);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(24,7);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(70,7);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");

	  // Set position to 8th row

	  Term1_MoveTo(1,8);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(3,8);
	  Term1_SetColor(clWhite, clBlack);
	  Term1_SendStr("Z position:                > Positive Y Direction:      W             ");
	  Term1_MoveTo(21,8);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(24,8);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(70,8);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");

	  // Set position to 9th row

	  Term1_MoveTo(1,9);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(3,9);
	  Term1_SetColor(clWhite, clBlack);
	  Term1_SendStr("                           > Negative Y Direction:      S             ");
	  Term1_MoveTo(21,9);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(24,9);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(70,9);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");

	  // Set position to 10th row

	  Term1_MoveTo(1,10);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(3,10);
	  Term1_SetColor(clWhite, clBlack);
	  Term1_SendStr("                           > Raise Height of Spindle:   Q        ");
	  Term1_MoveTo(21,10);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(24,10);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(70,10);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");


	  // Set position to 11th row

	  Term1_MoveTo(1,11);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(3,11);
	  Term1_SetColor(clWhite, clBlack);
	  Term1_SendStr("                           > Lower Height of Spindle:   E         ");
	  Term1_MoveTo(21,11);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(24,11);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(70,11);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");

	  // Set position to 12th row

	  Term1_MoveTo(1,12);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(3,12);
	  Term1_SetColor(clWhite, clBlack);
	  Term1_SendStr("                           > Emergency Stop:            Spacebar          ");
	  Term1_MoveTo(21,12);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(24,12);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(70,12);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");

	  // Set position to 13th row

	  Term1_MoveTo(1,13);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(3,13);
	  Term1_SetColor(clWhite, clBlack);
	  Term1_SendStr("                           > Change the step size MODE: M       ");
	  Term1_MoveTo(21,13);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(24,13);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(70,13);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");

	  // Set position to 14th row

	  Term1_MoveTo(1,14);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(3,14);
	  Term1_SetColor(clWhite, clBlack);
	  Term1_SendStr("                           > Automatic Control Toggle:  C        ");
	  Term1_MoveTo(21,14);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(24,14);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(70,14);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");

	  // Set position to 15th row

	  Term1_MoveTo(1,15);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(3,15);
	  Term1_SetColor(clWhite, clBlack);
	  Term1_SendStr("                           > Set Custom Spindle RPM:    R         ");
	  Term1_MoveTo(21,15);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(24,15);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(70,15);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");

	  // Set position to 16th row

	  Term1_MoveTo(1,16);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(3,16);
	  Term1_SetColor(clWhite, clBlack);
	  Term1_SendStr("                           > Set Custom X, Y, Z postion:P       ");
	  Term1_MoveTo(21,16);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(24,16);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");
	  Term1_MoveTo(70,16);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr(" ");

	  // Set position to 17th row

	  	  Term1_MoveTo(1,17);
	  	  Term1_SetColor(clBlack,clCyan);
	  	  Term1_SendStr(" ");
	  	  Term1_MoveTo(3,17);
	  	  Term1_SetColor(clWhite, clBlack);
	  	  Term1_SendStr("                                                            ");
	  	  Term1_MoveTo(21,17);
	  	  Term1_SetColor(clBlack,clCyan);
	  	  Term1_SendStr(" ");
	  	  Term1_MoveTo(24,17);
	  	  Term1_SetColor(clBlack,clCyan);
	  	  Term1_SendStr(" ");
	  	  Term1_MoveTo(70,17);
	  	  Term1_SetColor(clBlack,clCyan);
	  	  Term1_SendStr(" ");

	  // Set position to the 18th row
	  Term1_MoveTo(1,18);
	  //Set foreground colour to cyan and background to black
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr("                     ");
	  Term1_MoveTo(23,18);
	  Term1_SetColor(clBlack,clBlack);
	  Term1_MoveTo(24,18);
	  Term1_SetColor(clBlack,clCyan);
	  Term1_SendStr("                                               ");

	  Term1_MoveTo(1,21);
	  Term1_SetColor(clWhite,clBlack);
	  Term1_SendStr("Command Prompt:");
	  Term1_MoveTo(1,22);	//these are very low down in the GUI only temporarily
	  Term1_SendStr("> ");
	  //End command Prompt Code
}

void change_spindleRPM()
{
	sendMode = true;
	Term1_Cls();	//clears the gui for only this function, the only important thing on this gui is the information relating to the RPM of the Spindle
	Term1_MoveTo(1,1);
	Term1_SendStr("Input the desired RPM value, 0<RPM<32768");
	Term1_MoveTo(1,2);
	Term1_SendStr(">>>Command Prompt: ");
	uint16 RPM;	//the varaible that will be put into PWM4 set ratio
	while(!command_complete){		//reads the string put into the command prompt
			  __asm ("wfi");
		  }
	command_complete = 0;
	sscanf((char*)buffer, "%hu", &RPM);
	//if (RPM<32768 && RPM>0)		//only set the PWM4 ratio if the value input is between 0 and 32768
	//{								//also the terminal spits out a jumbled mess when this if statement is here, idk why
		PWM4_SetRatio16(RPM);
	//}
	Term1_MoveTo(1,3);
	Term1_SendNum(RPM);
	Term1_Cls(); //before this function exits we want to clear it so when we go back to the main function the main gui can be redrawn properly
	draw_GUI();
	sendMode = 0;
}


void move_motors(int x_time_to_move, int y_time_to_move, int z_time_to_move) {
	//Turn X_motor on for x_time_to_move
	PWM3_SetRatio16(MOTOR_ON2);
	for (i = 0; i < x_time_to_move; i++) {
	}
	PWM3_SetRatio16(0);
	//Turn Y_motor on for x_time_to_move
	PWM2_SetRatio16(MOTOR_ON2);
	for (i = 0; i < y_time_to_move; i++) {
	}
	PWM2_SetRatio16(0);
	//Turn Z_motor on for x_time_to_move
	PWM1_SetRatio16(MOTOR_ON1);
	for (i = 0; i < z_time_to_move; i++) {
	}
	PWM1_SetRatio16(0);
}

int draw_image(uint32_t file_size, int maximum_line_size,
		char line[maximum_line_size], int x_distance, int z_distance,
		int y_distance, int x_time_to_move, int y_time_to_move,
		int z_time_to_move, volatile _Bool sendMode) {
	int line_index = 0;
	// Iterate through each character in 'example_data.txt'
	for (uint32_t i = 0; i < file_size; i++) {
		if (line_index < maximum_line_size) {
			line[line_index] = EFil1_GetValue(i);
			if (line[line_index] == '\r' || line[line_index] == '\n') {
				line[line_index] = 0;
				line_index = 0;
				if (sscanf(line, "%hu,%hu,%hu", &x_distance, &x_distance,
						&z_distance) == 3) {
					move_position(x_distance, y_distance, z_distance,
							&x_time_to_move, &y_time_to_move, &z_time_to_move);
					move_motors(x_time_to_move, y_time_to_move, z_time_to_move);
					// Update value for X position
					Term1_MoveTo(14, 6);
					Term1_SendStr("   ");
					Term1_MoveTo(15, 6);
					Term1_SendNum(x_distance);
					// Update value for Y position
					Term1_MoveTo(14, 7);
					Term1_SendStr("   ");
					Term1_MoveTo(15, 7);
					Term1_SendNum(y_distance);
					// Update value for Z position
					Term1_MoveTo(14, 8);
					Term1_SendStr("   ");
					Term1_MoveTo(15, 8);
					Term1_SendNum(z_distance);
				}
			} else {
				line_index++;
			}
		} else {
			Term1_SendStr("Line not read: too long.\r\n");
			line_index = 0;
		}
	}
	sendMode = 0;
	return line_index;
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
  sendMode = false;
  draw_GUI();

  //Turn off all motors from the beginning
   PWM1_SetRatio16(0);	//X
   PWM2_SetRatio16(0);	//Y
   PWM3_SetRatio16(0);	//Z
   PWM4_SetRatio16(0);	//Spindle motor

   for(;;)
   {
	   while (!command_complete)
	   {
		   __asm ("wfi");
	   }
	   command_complete = 0;
	   //Processing the received char and complete command

	   if ((0 == strcmp((char*)buffer, "c")))
	   {
		   if (c_pressed == 0)
		   {
			   c_pressed = 1;
			   auto_mode = 1;
		   }
		   else
		   {
			   c_pressed = 0;
			   auto_mode = 0;
		   }
	   }
	   else if (0 == strcmp((char*)buffer, "m"))
	   {
		   mode_change();
		   draw_GUI();
	   }
	   //		 When user type in following command it will turn or move stepper motor 1,2,3 on as desired
	   if (auto_mode == 0)
	   {
		   if ((0 == strcmp((char*)buffer, "a")) || (0 == strcmp((char*)buffer, "A")) )			//left movement. 	this if statement is taken from lab7, not to sure how the zero works but it does
		   {
			   Direction1_PutVal(1);		//we want 'd' to be the forward direction in the x axis, so if "Direction1" = 1 it must be going the opposite way, ie, left
			   d_pressed = 0;
			   if (a_pressed == 0)	//so, if a has been pressed and the previously pressed button was NOT a, then a is now the direction of travel
			   {
				   PWM3_SetRatio16(MOTOR_ON2);	//im not sure if the ratio needs to be 32000, or 16000. i initially think it relates to the size of the steps but i could be wrong
				   PWM4_SetRatio16(MOTOR_ON1);
				   a_pressed = 1;
			   }
			   else
			   {
				   PWM1_SetRatio16(MOTOR_OFF);
				   a_pressed = 0;	//set a_pressed to zero because a button other than a has been pressed
				   if(w_pressed == '0' || s_pressed ==  '0')	//if this if statement returns true, then neither the x axis or y axis is moving, so there is no need for the spindle to be spinning
					   PWM4_SetRatio16(MOTOR_OFF);	//if nothing is moving we dont want the spindle to turn on
			   }
		   }
		   else if ((0 == strcmp((char*)buffer, "d")) || (0 == strcmp((char*)buffer, "D")) )	//right movement
		   {
			   Direction1_PutVal(0);		//direction doesn't need to be changed for forward value in x axis, so "Direction1" is 0
			   a_pressed = 0;
			   if (d_pressed == 0)
			   {
				   PWM3_SetRatio16(MOTOR_ON2);	//im not sure if the ratio needs to be 32000, or 16000. i initially think it relates to the size of the steps but i could be wrong
				   d_pressed = 1;	//lol same
			   }
			   else
			   {
				   PWM1_SetRatio16(MOTOR_OFF);
				   d_pressed = 0;	//set d_pressed to zero because a button other than d has been pressed
				   if(w_pressed == '0' || s_pressed ==  '0')	//if this if statement returns true, then neither the x axis or y axis is moving, so there is no need for the spindle to be spinning
					   PWM4_SetRatio16(MOTOR_OFF);
			   }
		   }
		   else if ((0 == strcmp((char*)buffer, "w")) || (0 == strcmp((char*)buffer, "W")) )		//forward movement
		   {
			   Direction2_PutVal(0);		//w is the forward direction in y axis, so "Direction2" = 0, i.e, forward
			   s_pressed = 0;
			   if (w_pressed == 0)
			   {
				   PWM2_SetRatio16(MOTOR_ON2);	//im not sure if the ratio needs to be 32000, or 16000. i initially think it relates to the size of the steps but i could be wrong
				   //PWM1_SetRatio16(MOTOR_ON1);
				   w_pressed = 1;
			   }
			   else
			   {
				   PWM2_SetRatio16(MOTOR_OFF);
				   w_pressed = 0;
				   if(a_pressed == '0' || d_pressed ==  '0')	//if this if statement returns true, then neither the x axis or y axis is moving, so there is no need for the spindle to be spinning
					   PWM4_SetRatio16(MOTOR_OFF);
			   }

		   }
		   else if ((0 == strcmp((char*)buffer, "s")) || (0 == strcmp((char*)buffer, "S")) )		//backwards movement
		   {
			   Direction2_PutVal(1);
			   w_pressed = 0;
			   if (s_pressed == 0)
			   {
				   PWM2_SetRatio16(MOTOR_ON2);	//im not sure if the ratio needs to be 32000, or 16000. i initially think it relates to the size of the steps but i could be wrong
				   s_pressed = 1;
			   }
			   else
			   {
				   PWM2_SetRatio16(MOTOR_OFF);
				   s_pressed = 0;
				   if(a_pressed == '0' || d_pressed ==  '0')	//if this if statement returns true, then neither the x axis or y axis is moving, so there is no need for the spindle to be spinning
					   PWM4_SetRatio16(MOTOR_OFF);
			   }
		   }
		   else if ((0 == strcmp((char*)buffer, "e")) || (0 == strcmp((char*)buffer, "E")) )		//backwards movement
		   {
			   Direction3_PutVal(0);
			   q_pressed = 0;
			   if (e_pressed == 0)
			   {
				   PWM1_SetRatio16(MOTOR_ON1);	//im not sure if the ratio needs to be 32000, or 16000. i initially think it relates to the size of the steps but i could be wrong
				   e_pressed = 1;
			   }
			   else
			   {
				   PWM1_SetRatio16(MOTOR_OFF);
				   e_pressed = 0;
				   if(a_pressed == '0' || d_pressed ==  '0')	//if this if statement returns true, then neither the x axis or y axis is moving, so there is no need for the spindle to be spinning
					   PWM4_SetRatio16(MOTOR_OFF);
			   }
		   }
		   else if ((0 == strcmp((char*)buffer, "q")) || (0 == strcmp((char*)buffer, "Q")) )		//backwards movement
		   {
			   Direction3_PutVal(1);
			   e_pressed = 0;
			   if (q_pressed == 0)
			   {
				   PWM1_SetRatio16(MOTOR_ON1);	//im not sure if the ratio needs to be 32000, or 16000. i initially think it relates to the size of the steps but i could be wrong
				   q_pressed = 1;
			   }
			   else
			   {
				   PWM1_SetRatio16(MOTOR_OFF);
				   q_pressed = 0;
				   if(a_pressed == '0' || d_pressed ==  '0')	//if this if statement returns true, then neither the x axis or y axis is moving, so there is no need for the spindle to be spinning
					   PWM4_SetRatio16(MOTOR_OFF);
			   }
		   }

		   else if ((0 == strcmp((char*)buffer, "r")) || (0 == strcmp((char*)buffer, "R")))
		   {
			   change_spindleRPM();
		   }
		   else if ((0 == strcmp((char*)buffer, "h")) || (0 == strcmp((char*)buffer, "H")))
		   {
			   sendMode = true;
			   uint32_t file_size = EFil1_GetSize(); // Get the size (in bytes) of 'drawing_file.txt'
			   int maximum_line_size = 200; // Maximum number of characters per line
			   char line[maximum_line_size];
			   char buffer[maximum_line_size];
			   int line_index = draw_image(file_size, maximum_line_size, line,
					   x_distance, z_distance, y_distance, x_time_to_move,
					   y_time_to_move, z_time_to_move, sendMode);
		   }
		   else if ((0 == strcmp((char*)buffer, "p")) || (0 == strcmp((char*)buffer, "P")))
		   {//
			   sendMode = true;
			   Term1_Cls();
			   Term1_MoveTo(1,2);
			   Term1_SendStr("Type in command prompt: 			X: number, Y: number, Z: number");
			   Term1_MoveTo(1,4);
			   Term1_SendStr(">>>Command Prompt: ");
			   while(!command_complete){		//reads the string put into the command prompt
				   __asm ("wfi");
			   }
			   command_complete = 0;
			   //	sscanf((char*)buffer, "X:%hu, Y:%hu, Z:%hu", &x_distance, &y_distance, &z_distance);
			   (sscanf((char*)buffer, "%hu %hu %hu", &x_distance, &y_distance, &z_distance) > 0 );
			   move_position(x_distance, y_distance, z_distance, &x_time_to_move, &y_time_to_move, &z_time_to_move);

			   //Turn X_motor on for x_time_to_move
				move_motors(x_time_to_move, y_time_to_move, z_time_to_move);
			   draw_GUI();
			   sendMode = 0;
			   // Update value for X position
			   Term1_MoveTo(14,6);
			   Term1_SendStr("   ");
			   Term1_MoveTo(15,6);
			   Term1_SendNum(x_distance);

			   // Update value for Y position
			   Term1_MoveTo(14,7);
			   Term1_SendStr("   ");
			   Term1_MoveTo(15,7);
			   Term1_SendNum(y_distance);

			   // Update value for Z position
			   Term1_MoveTo(14,8);
			   Term1_SendStr("   ");
			   Term1_MoveTo(15,8);
			   Term1_SendNum(z_distance);
		   }

	   }

//	   else if (auto_mode == 1)
//	   {
//		   read_text_file();
//		   int j;
//		   for (j=0; j<10; j++)
//		   {
//			   if (read_info[j][1] == "X")	//here it thinks im comparing read_info to an integer, which makes no sense, im asking if that position in the array is equal to X
//			   {
//				   if (read_info[j][2] == 1)
//					   Direction1_PutVal(1);
//				   else if (read_info[j][2] == 0)
//					   Direction1_PutVal(0);
//
//				   int x_distance;
//				   x_distance = read_info[j][3];
//				   X_pos(x_distance);
//			   }
//			   else if (read_info[j][1] == "Y")
//			   {
//				   if (read_info[j][2] == 1)
//					   Direction2_PutVal(1);
//				   else if (read_info[j][2] == 0)
//					   Direction2_PutVal(0);
//
//				   int y_distance;
//				   y_distance = read_info[j][3];
//				   Y_pos(y_distance);
//			   }
//		   }
//	   }
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
