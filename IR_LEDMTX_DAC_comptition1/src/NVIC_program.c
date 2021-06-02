/*********************************************************/
/* author  : Farouk                                      */
/* Version : v01                                         */
/* Date    : August 19 2020                              */
/*********************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "NVIC_interface.h"
#include "NVIC_private.h"
#include "NVIC_config.h"

void MNVIC_voidEnableInterrupt(u8 copy_u8IntNum)
{
	if(copy_u8IntNum <= 31)
	{
		NVIC_ISER0 = 1 << copy_u8IntNum;
	}
	else if(copy_u8IntNum <= 59)
	{
		copy_u8IntNum -= 32;
		NVIC_ISER1 = 1 << copy_u8IntNum;
	}
    else
    {
		/* RETURN ERROR */
	}		
}   

void MNVIC_voidDisableInterrupt(u8 copy_u8IntNum)
{
	if(copy_u8IntNum <= 31)
	{
		NVIC_ICER0 = 1 << copy_u8IntNum;
	}
	else if(copy_u8IntNum <= 59)
	{
		copy_u8IntNum -= 32;
		NVIC_ICER1 = 1 << copy_u8IntNum;
	}
    else
    {
		/* RETURN ERROR */
	}		
}   

void MNVIC_voidSetPendingFlag(u8 copy_u8IntNum)
{
	if(copy_u8IntNum <= 31)
	{
		NVIC_ISPR0 = 1 << copy_u8IntNum;
	}
	else if(copy_u8IntNum <= 59)
	{
		copy_u8IntNum -= 32;
		NVIC_ISPR1 = 1 << copy_u8IntNum;
	}
    else
    {
		/* RETURN ERROR */
	}		
}   

void MNVIC_voidClearPendingFlag(u8 copy_u8IntNum)
{
	if(copy_u8IntNum <= 31)
	{
		NVIC_ICPR0 = 1 << copy_u8IntNum;
	}
	else if(copy_u8IntNum <= 59)
	{
		copy_u8IntNum -= 32;
		NVIC_ICPR1 = 1 << copy_u8IntNum;
	}
    else
    {
		/* RETURN ERROR */
	}		
}   

u8 MNVIC_u8GetActiveFlag(u8 copy_u8IntNum)
{
	u8 Local_u8Result = 0;
	if(copy_u8IntNum <= 31)
	{
		Local_u8Result = GET_BIT( NVIC_IABR0 , copy_u8IntNum );
	}
	else if(copy_u8IntNum <= 59)
	{
		copy_u8IntNum -= 32;
		Local_u8Result = GET_BIT( NVIC_IABR1 , copy_u8IntNum );
	}
    else
    {
		/* RETURN ERROR */
	}
    return 	Local_u8Result;
}

void MNVIC_voidSetPriority(u32 Copy_u8GroupSubConfig , u8 Copy_u8GrpPriority , u8 Copy_u8SubPriority , u8 Copy_u8IntId )
{
	SCB_AIRCR = Copy_u8GroupSubConfig;
	u8 Local_u8priority = 0;
	Local_u8priority = (Copy_u8GrpPriority << ((Copy_u8GroupSubConfig - CONFIG0)/256) ) | Copy_u8SubPriority;
	/* CORE PREPHERAL INT */
	
	
	/* EXT PREPHERAL INT */
	if(Copy_u8IntId >= 0)
		NVIC_IPR[Copy_u8IntId] = Local_u8priority << 4;
}








