/*********************************************************/
/* author  : Farouk                                      */
/* Version : v01                                         */
/* Date    : August 19 2020                              */
/*********************************************************/
#ifndef NVIC_PRIVATE_H
#define NVIC_PRIVATE_H

/* REGISTER DEFINITION */
#define NVIC_ISER0    (*(u32 *)0xE000E100)/* control int from 0 to 31 */
#define NVIC_ISER1    (*(u32 *)0xE000E104)

#define NVIC_ICER0    (*(u32 *)0xE000E180)/* control int from 0 to 31 */
#define NVIC_ICER1    (*(u32 *)0xE000E184)

#define NVIC_ISPR0    (*(u32 *)0xE000E200)/* control int from 0 to 31 */
#define NVIC_ISPR1    (*(u32 *)0xE000E204)

#define NVIC_ICPR0    (*(u32 *)0xE000E280)/* control int from 0 to 31 */
#define NVIC_ICPR1    (*(u32 *)0xE000E284)

#define NVIC_IABR0    (*(volatile u32 *)0xE000E300)
#define NVIC_IABR1    (*(volatile u32 *)0xE000E284)

#define SCB_AIRCR     (*(volatile u32 *)(0xE000ED00 + 0x0C))
/* ACCESS IT WITH INT ID IN VEC TABLE*/
#define NVIC_IPR      ((volatile u8 *)(0xE000E100)+0x300)
/* TRIGGER INT BY WRITING THE INT ID TO THIS REG */
#define NVIC_STIR     ((volatile u32 *)(0xE000E100)+(0xE00))










#endif
