#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "DIO_interface.h"
#include "NVIC_interface.h"
#include "EXTI_interface.h"
#include "STK_interface.h"
#include "LEDMRX_interface.h"
#include "IRCOM_interface.h"
#include "DAC_interface.h"



int main()
{

	/* ENABLE HSE CLOCK */
	RCC_voidInitSysClock();
	/* ENABLE CLK ON GPIOA and GPIOB */
	RCC_voidEnableClock(RCC_APB2 , 2);
	RCC_voidEnableClock(RCC_APB2 , 3);

	MNVIC_voidEnableInterrupt(6);// enable EXTI0 from NVIC

	// IR receiver pin (out pin)
	MGPIO_voidSetPinDirection(PORTA,PIN0,INPUT_FLOATING);

    /* DAC init (SET Directions) */
	MGPIO_voidSetPinDirection(GPIOA , PIN8 , OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinDirection(GPIOA , PIN9 , OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinDirection(GPIOA , PIN10, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinDirection(GPIOA , PIN11, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinDirection(GPIOA , PIN12, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinDirection(GPIOA , PIN15, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinDirection(GPIOB , PIN11, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinDirection(GPIOB , PIN12, OUTPUT_2MHZ_PP);
	/* enable EXTI0 and set callback for EXTI0 */
	EXTI_voidSetCallBack( IRCOM_voidReadFrameSegTime );
	EXTI_voidInit();

	STK_voidInit();// clk AHP/8

	HLEDMRX_voidInit();// set pins as output (led matrix)
	while(1)
	{
		hamda();
	}
    return 0;
}
