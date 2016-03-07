//-----------------------------------------------------------------------------
// EFM8UB1_Timer0_8bitReload.c
//-----------------------------------------------------------------------------
// Copyright 2014 Silicon Laboratories, Inc.
// http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt
//
// Program Description:
//
// This program uses Timer0 in 8-bit counter/timer with reload mode.
// It uses the Timer0 to create an interrupt at a certain rate and toggles
// the LED when the interrupt counter reaches the selected value.
//
// Resources:
//   SYSCLK - 24.5 MHz HFOSC0 / 8
//   Timer0 - 10 Hz interrupt
//   P1.4   - LED green
//   P2.3   - Display enable
//
//-----------------------------------------------------------------------------
// How To Test: EFM8UB1 STK
//-----------------------------------------------------------------------------
// 1) Place the switch in "AEM" mode.
// 2) Connect the EFM8UB1 STK board to a PC using a mini USB cable.
// 3) Compile and download code to the EFM8UB1 STK board.
//    In Simplicity Studio IDE, select Run -> Debug from the menu bar,
//    click the Debug button in the quick menu, or press F11.
// 4) Run the code.
//    In Simplicity Studio IDE, select Run -> Resume from the menu bar,
//    click the Resume button in the quick menu, or press F8.
// 5) Check that the green LED is blinking.
//
// Target:         EFM8UB1
// Tool chain:     Generic
//
// Release 0.1 (ST)
//    - Initial Revision
//    - 10 OCT 2014
//

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <SI_EFM8UB1_Register_Enums.h>
#include "InitDevice.h"
#include "Dali.h"


//-----------------------------------------------------------------------------
// Pin Definitions
//-----------------------------------------------------------------------------

#define DISP_BC_DRIVEN   0             // 0 = Board Controller drives display
#define DISP_EFM8_DRIVEN 1             // 1 = EFM8 drives display

//-----------------------------------------------------------------------------
// Main Routine
//-----------------------------------------------------------------------------
void main (void)
{
	uint8_t test=0;

	uint16_t fcounter;
   enter_DefaultMode_from_RESET();

   DISP_EN = DISP_BC_DRIVEN;           		// EFM8 does not drive display

   IE_EA = 1;                          		// Enable global interrupts
   PRTDRV |=0x1;							//Enable high drive strength on P0
   SetDaliInputPinPolarity(ACTIVE_LOW);

   while (1) {
	   DALI_OUT=1;
	   if (PB0_SW==0) {
		  // ManchesterEncoder(0xf0);
		  DaliTXStateMachine(0xff, 0x00);
		   for(fcounter=0; fcounter<0xfff; fcounter++);
	   }

   }


}
