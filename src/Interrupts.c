//=========================================================
// src/Interrupts.c: generated by Hardware Configurator
//
// This file will be regenerated when saving a document.
// leave the sections inside the "$[...]" comment tags alone
// or they will be overwritten!
//=========================================================

         
// USER INCLUDES			
#include <SI_EFM8UB1_Register_Enums.h>
#include "InitDevice.h"
#include "Dali.h"

//extern bit MDone;
//extern bit MOutput;

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------
// Configurator set for HFOSC0/8
#define SYSCLK             3062000

static xdata DALI_TXFRAME State = START;
//static xdata uint8_t bitCounter = 0;
static xdata uint8_t daliRXOutput=0;
bit _1stHalf;
bit _2ndHalf;

SI_SBIT (LED2,SFR_P1, 4);			   //PB0 Switch Definition



//-----------------------------------------------------------------------------
// INT1_ISR
//-----------------------------------------------------------------------------
//
// TIMER0 ISR Content goes here. Remember to clear flag bits:
// TCON::TF0 (Timer 0 Overflow Flag)
//
// Here we process the Timer0 interrupt and toggle the LED when appropriate
//
//-----------------------------------------------------------------------------
SI_INTERRUPT (INT1_ISR, INT1_IRQn)
{
   static xdata uint8_t intcounter = 0;

   //Clear int Flag
  // TCON =0;// &=0xEF;

  // xdata uint16_t timerRead;

  // timerRead = GetDaliRxTimer();

	LED2^=1;

   if((GetDaliIntputPin()==0) &&(intcounter==0))
	//if((GetBusQuietCounter()>3)&&(GetDaliIntputPin()==0) &&(intcounter==0))
	{

		_1stHalf=GetDaliIntputPin();
		//IT01CF = 0xF0;
		SetDaliInputPinPolarity(ACTIVE_HIGH);
		//EnableInt1();
	}

	if ((intcounter++==1)) //&& (timerRead>196)&&(timerRead<238))
	{
		_2ndHalf=GetDaliIntputPin();
		SetDaliInputPinPolarity(ACTIVE_LOW);
		intcounter = 0;

	}


/*
   if((GetDaliIntputPin()==0) &&(intcounter==0))
	//if((GetBusQuietCounter()>3)&&(GetDaliIntputPin()==0) &&(intcounter==0))
	{
		LED2^=1;
		//DisableInt1 ();
	//	DisableDaliRxTimerInt();
	//	ReloadDaliRxTimer(0,0);
	//	StartDaliRxTimer();
		_1stHalf=GetDaliIntputPin();
		//IT01CF = 0xF0;
		SetDaliInputPinPolarity(ACTIVE_HIGH);
		//EnableInt1();
	}


	if ((intcounter++==1)) //&& (timerRead>196)&&(timerRead<238))
	{
	//	LED2^=1;
		_2ndHalf=GetDaliIntputPin();
		SetDaliInputPinPolarity(ACTIVE_LOW);

	}

	else
	{
		//SetDaliRxErrorFlag();
		SetDaliInputPinPolarity(ACTIVE_LOW);
	}



	if ((_1stHalf==0) && (_2ndHalf==1))// && (GetDaliRxErrorFlag()==0))			// Start bit received
	{
		DisableInt1 ();
		StopDaliRxTimer();

		//It will reload a one period worth of time, so it will start sampling on the next bit
		ReloadDaliRxTimer(TMH, TML);
		EnableDaliRxTimerInt();
		StartDaliRxTimer();
		daliRXOutput=0;
		State = DATA;
		intcounter=0;
		_1stHalf = _2ndHalf =0;
		//

	}
	else if (intcounter==2)
	{
		intcounter=0;
		_1stHalf = _2ndHalf =0;
	}
*/

}


//-----------------------------------------------------------------------------
// TIMER1_ISR
//-----------------------------------------------------------------------------
//
// TIMER1 ISR Content goes here. Remember to clear flag bits:
// TCON::TF1 (Timer 0 Overflow Flag)
//
// Here we process the Timer dedicated to Dali RX
//
//-----------------------------------------------------------------------------
SI_INTERRUPT (TIMER1_ISR, TIMER1_IRQn)
{

#if 0
static xdata uint8_t sampleCounter = 0;
static xdata uint8_t bitsCounter = 7;
xdata uint8_t buffer[8];
xdata uint8_t BitBuffer[72];
bit input;
bit outputbit;
xdata BITS_BYTE sample;
xdata BITS_BYTE DataOutput;

static xdata uint8_t Bunter=0;

	ReloadDaliRxTimer(STMH, STML);
	//input = GetDaliIntputPin();


	//This state machine makes sure the Rx handler is in the right State
	switch (State)

		{

			case START:			//In this state, it checks if the RX bus was quite and also if it receives the start bit
					{
						break;
					}

			case DATA:
					{
/*						//This state machine counts samples and store them to the sample struct
						switch (sampleCounter++)
						{
						//Reading the First Half of the bit, 1st interaction
							case 0:
									{
										sample.nybble.BB0 = input;
										break;
									}
						//Reading the First Half of the bit, 2nd interaction
							case 1:
									{
										sample.nybble.BB1 = input;
										break;
									}
						//Reading the Second Half of the bit, 1st interaction
							case 2:
									{
										sample.nybble.BB4 = input;
										break;
									}
						//Reading the Second Half of the bit, 2nd interaction
							case 3:
									{
										sample.nybble.BB5 = input;

										// Logic 1 received
										if (sample.Abyte==0x30) outputbit =1;
										// Logic 0 received
										else if (sample.Abyte==0x03) outputbit =0;

										//This state machine places the bit in the right bit location on the DataOutput Structure
										switch (bitsCounter--)
										{
											case 0:
													{
														DataOutput.nybble.BB0 = outputbit;
														bitsCounter=8;
														break;
													}
											case 1:
													{
														DataOutput.nybble.BB1 = outputbit;
														break;
													}
											case 2:
													{
														DataOutput.nybble.BB2 = outputbit;
														break;
													}
											case 3:
													{
														DataOutput.nybble.BB3 = outputbit;
														break;
													}
											case 4:
													{
														DataOutput.nybble.BB4 = outputbit;
														break;
													}
											case 5:
													{
														DataOutput.nybble.BB5 = outputbit;
														break;
													}
											case 6:
													{
														DataOutput.nybble.BB6 = outputbit;
														break;
													}
											case 7:
													{
														DataOutput.nybble.BB7 = outputbit;
														break;
													}
										}



										break;
									}

						}//End of switch (sampleCounter++)

*/			//			LED2^=1;
						BitBuffer[Bunter++] = GetDaliIntputPin();
						if (Bunter==72)
						{
							Bunter=0;
							EnableInt1();
							State = START;
						}

						break;
					}//End of case DATA:

		}//End of Switch State:
#endif

}


//-----------------------------------------------------------------------------
// Dali TX Timer ISR (TIMER0)
//-----------------------------------------------------------------------------
//
// TIMER0 ISR Content goes here. Remember to clear flag bits:
// TCON::TF0 (Timer 0 Overflow Flag)
//
// Here we process the Timer0 interrupt and toggle the LED when appropriate
//
//-----------------------------------------------------------------------------
SI_INTERRUPT (TIMER0_ISR, TIMER0_IRQn)
{

	ReloadDaliTxTimer(TMH, TML);
	DaliTxHandler();
	QueryDaliBus();

}


