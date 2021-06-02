/*********************************************************/
/* author  : Farouk                                      */
/* Version : v01                                         */
/* Date    : August 19 2020                              */
/*********************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"

#define NULL     ((void*)0x00)

static void (* EXTI0_CallBack) (void) = NULL ;

void	EXTI0_IRQHandler(void)
{
	EXTI0_CallBack();
	SET_BIT(EXTI -> PR , 0);
}

void EXTI_voidInit(void)
{
	#if		EXTI_LINE == EXTI_LINE0
			SET_BIT(EXTI -> IMR , EXTI_LINE0 );
	#elif	EXTI_LINE == EXTI_LINE1
			SET_BIT(EXTI -> IMR , EXTI_LINE1 );
	#elif	EXTI_LINE == EXTI_LINE2
			SET_BIT(EXTI -> IMR , EXTI_LINE2 );
	#else
		#error ("Wrong Externl Interrupt Line !")
	#endif
	
	
	#if		EXTI_TRIG_MODE == FALLING_EDGE
			SET_BIT(EXTI -> FTSR , EXTI_LINE);
	#elif	EXTI_TRIG_MODE == RISING_EDGE
			SET_BIT(EXTI -> RTSR , EXTI_LINE);
	#elif	EXTI_TRIG_MODE == ON_CHANGE
			SET_BIT(EXTI -> RTSR , EXTI_LINE);
			SET_BIT(EXTI -> FTSR , EXTI_LINE);
	#else
		#error ("Wrong External Interrupt Sense Mode !")
	#endif
}

void EXTI_voidEnable(u32 Copy_u32LineInt)
{
	EXTI -> IMR = (1 << Copy_u32LineInt);
	//EXTI -> EMR = (1 << Copy_u32LineInt);
}

void EXTI_voidSetTrigMode(u8 Copy_u8TrigMode , u32 Copy_u32LineInt)
{
	#if   Copy_u8TrigMode == RISSING
	EXTI -> RTSR = (1 << Copy_u32LineInt);
	#elif Copy_u8TrigMode == FALLING
	EXTI -> FTSR = (1 << Copy_u32LineInt);
	#elif Copy_u8TrigMode == ON_CHANGE
	EXTI -> RTSR = (1 << Copy_u32LineInt);
	EXTI -> FTSR = (1 << Copy_u32LineInt);
	#endif
}

void EXTI_voidGeneratSwInt(u32 Copy_u32LineInt)
{
	EXTI -> SWIER = (1 << Copy_u32LineInt);
}

u8   EXTI_u8GetPF(u32 Copy_u32LineInt)
{
	//u8 Local_u8PendingVal = (1 << Copy_u32LineInt);
	return GET_BIT(EXTI -> PR , Copy_u32LineInt);
}

void EXTI_voidDisableEXTI(u8 Copy_u8EXTILine)
{
	CLR_BIT(EXTI -> IMR , Copy_u8EXTILine);
}

void EXTI_voidSetCallBack(void (*ptr) (void))
{
	EXTI0_CallBack = ptr ;
}


