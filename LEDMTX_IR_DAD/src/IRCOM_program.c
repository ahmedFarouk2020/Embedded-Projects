/*********************************************************/
/* author  : Farouk                                      */
/* Version : v01                                         */
/* Date    : Sept. 3 2020                                */
/*********************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "STK_interface.h"
#include "EXTI_interface.h"
#include "LEDMRX_interface.h"
//#include "file.h"

#include "IRCOM_interface.h"
#include "IRCOM_private.h"
#include "IRCOM_config.h"

static volatile u8 counter = 0;
static volatile u8 data    = 0;
static volatile u16 IRCOM_Frame[50] = {0};

/* read frame signal in microsec. from remote into array */
void IRCOM_voidReadFrameSegTime(void)
{
	if(counter == 0) /* enter this condition the first time only */
	{
		STK_voidSetIntervalSingle(1000000 , IRCOM_voidDoFunction);
		counter++;
	}
    else
	{
		IRCOM_Frame[counter - 1] = STK_u32GetElapsedTime();
		counter++;
	    STK_voidResetTimer();
	}
}


void IRCOM_voidGetData(void)
{

	for(u8 i = 0 ; i<8 ; i++)
	{
		if(IRCOM_Frame[17+i] < 2400 && IRCOM_Frame[17+i] > 2100 )     // 2250
		{
			SET_BIT(data,i);
		}
		else if(IRCOM_Frame[17+i] < 1300 && IRCOM_Frame[17+i] > 1000) // 1125
		{
			CLR_BIT(data,i);
		}
	}
	//IRCOM_voidDoFunction();
}

void IRCOM_voidDoFunction(void)
{
	IRCOM_voidGetData();
	/* reset counter and frame for the next frame */
	counter = 0;
	switch (data)
	{
	//	case  REMOTE_0  :  DAC_voidReadAudioArr();                          break;
		case  REMOTE_1  :  HLEDMRX_voidStatic();           break;
		case  REMOTE_2  :  HLEDMRX_voidEnableHamada();     break;
		case  REMOTE_3  :  HLEDMRX_voidEnableShift();      break;
	//	case  REMOTE_4  :  DAC_voidDecreaseFreq();                                                break;
	    case  REMOTE_5  :                                                break;
	//  case  REMOTE_6  :  DAC_voidIncreaseFreq();                          break;
	    case  REMOTE_7  :                                                   break;
	    case  REMOTE_8  :                                                   break;
	    case  REMOTE_9  :                                                   break;
	    case  OFF       : STK_voidStopTimer();                              break;
	    case  MUTE      :                                                   break;
	    case  VOL_UP    :                               break;
	    case  VOL_DOWN  :             break;
	    case  STOP_RES  :                                                   break;
		case  MODE      :                                                   break;
	    // case  LEFT     : HLEDMRX_voidShiftLeft();                       break;
	   // case  RIGHT    : HLEDMRX_voidShiftRight();                      break;
	  //   case  EQ    :                                           break;
	 //  case  RPT   :                                                          break;
	//  case  U_SD  :                                                         break;
    }

}
