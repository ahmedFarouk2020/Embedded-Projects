/*********************************************************/
/* author  : Farouk                                      */
/* Version : v01                                         */
/* Date    : August 19 2020                              */
/*********************************************************/
#ifndef NVIC_INTERFACE_H
#define NVIC_INTERFACE_H

/* Group & Subgroup Priority Configration */
/* THE NUMS IN MACROS REFER TO THE NUM OF SUB GRP */ 
#define     CONFIG0     0xFA050300
#define     CONFIG1     0xFA050400
#define     CONFIG2     0xFA050500
#define     CONFIG3     0xFA050600
#define     CONFIG4     0xFA050700

void MNVIC_voidEnableInterrupt(u8 copy_u8IntNum);
void MNVIC_voidDisableInterrupt(u8 copy_u8IntNum);
void MNVIC_voidSetPendingFlag(u8 copy_u8IntNum);
void MNVIC_voidClearPendingFlag(u8 copy_u8IntNum);
//u8 MNVIC_u8GetActiveFlag(u8 copy_u8IntNum);
void MNVIC_voidSetPriority(u32 Copy_u8GroupSubConfig , u8 Copy_u8GrpPriority , u8 Copy_u8SubPriority , u8 Copy_u8IntId );

#endif
