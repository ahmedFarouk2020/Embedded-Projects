#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "DIO_interface.h"
#include "NVIC_interface.h"
#include "EXTI_interface.h"
#include "STK_interface.h"
#include "LEDMRX_interface.h"
#include "IRCOM_interface.h"
/*
 * sometimes Code dont work correctly with debugger but when i turn it off the code
 * works i dont know why ?!
 *
 */



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
