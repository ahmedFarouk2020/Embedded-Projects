#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "STK_interface.h"

#include "DAC_interface.h"
#include "DAC_private.h"
#include "DAC_config.h"

#include "file.h"

static volatile u8 time = 125;// 1/freq

void DAC_voidReadAudioArr(void)// can be optimized
{

	u8 Local_u8Bit = 0;
	for(u16 i=0 ; i<38359 ; i++)
	{
		/* DAC0*/
		Local_u8Bit = GET_BIT(audioSession_raw[i],0);
		MGPIO_voidSetPinValue(GPIOA,PIN8,Local_u8Bit);
		/* DAC1 */
		Local_u8Bit = GET_BIT(audioSession_raw[i],1);
		MGPIO_voidSetPinValue(GPIOA,PIN9,Local_u8Bit);
		/* DAC2 */
		Local_u8Bit = GET_BIT(audioSession_raw[i],2);
		MGPIO_voidSetPinValue(GPIOA,PIN10,Local_u8Bit);
		/* DAC3 */
		Local_u8Bit = GET_BIT(audioSession_raw[i],3);
		MGPIO_voidSetPinValue(GPIOA,PIN11,Local_u8Bit);
		/* DAC4 */
		Local_u8Bit = GET_BIT(audioSession_raw[i],4);
		MGPIO_voidSetPinValue(GPIOA,PIN12,Local_u8Bit);
		/* DAC5 */
		Local_u8Bit = GET_BIT(audioSession_raw[i],5);
		MGPIO_voidSetPinValue(GPIOA,PIN15,Local_u8Bit);
		/* DAC6 */
		Local_u8Bit = GET_BIT(audioSession_raw[i],6);
		MGPIO_voidSetPinValue(GPIOB,PIN11,Local_u8Bit);
		/* DAC7 */
		Local_u8Bit = GET_BIT(audioSession_raw[i],7);
		MGPIO_voidSetPinValue(GPIOB,PIN12,Local_u8Bit);
		DAC_delay();
	}
}

void  DAC_voidIncreaseFreq(void)
{
	if(time > 15)
	   time -= 10  ;
}

void  DAC_voidDecreaseFreq(void)
{
	if(time < 230)
	   time += 10  ;
}

void DAC_delay(void)// for LEDMTRX
{
	for(u8 i=0 ; i<time ;i++)
	{
			asm("NOP");
	}
}
