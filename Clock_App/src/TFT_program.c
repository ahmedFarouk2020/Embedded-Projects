/*********************************************************/
/* author  : Farouk                                      */
/* Version : v01                                         */
/* Date    : Sept 21 2020                                */
/*********************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "STK_interface.h"
#include "SPI_interface.h"

#include "TFT_interface.h"
#include "TFT_private.h"
#include "TFT_config.h"

s8 countSec1 = 0;
s8 countSec2 = 0;
s8 countMin1 = 0;
s8 countMin2 = 0;
s8 countHor1 = 0;
s8 countHor2 = 0;

void TFT_voidInit(void)
{
	/* reset pulse */
	MGPIO_voidSetPinValue(TFT_RESET_PIN,HIGH);
	STK_voidSetBusyWait(100);
	MGPIO_voidSetPinValue(TFT_RESET_PIN,LOW);
	STK_voidSetBusyWait(1);
	MGPIO_voidSetPinValue(TFT_RESET_PIN,HIGH);
	STK_voidSetBusyWait(100);
	MGPIO_voidSetPinValue(TFT_RESET_PIN,LOW);
	STK_voidSetBusyWait(100);
	MGPIO_voidSetPinValue(TFT_RESET_PIN,HIGH);
	STK_voidSetBusyWait(120000);
	
	/* sleep out command */
	TFT_voidWriteCommand(0x11);
	
	/* wait 150 msec */
	STK_voidSetBusyWait(150000);
	
	/* color mode command */
	TFT_voidWriteCommand(0x3A);
	TFT_voidWriteData(0x05);
	
	/* display on command */
	TFT_voidWriteCommand(0x29);
}

void TFT_voidDisplayImg(const u16* copy_u16pImg)
{
	u16 counter;
	u8 Data;

    /* set X address*/
	TFT_voidWriteCommand(0x2A);
	/* the beginning */
	TFT_voidWriteData(0);
	TFT_voidWriteData(0);
	/* the end */
	TFT_voidWriteData(0);
	TFT_voidWriteData(127);

	/* set Y address*/
	TFT_voidWriteCommand(0x2B);
	/* the beginning */
	TFT_voidWriteData(0);
	TFT_voidWriteData(0);
	/* the end */
	TFT_voidWriteData(0);
	TFT_voidWriteData(159);

	/* RAM Write */
	TFT_voidWriteCommand(0x2C);

    /* show img */
	for(counter=0 ;counter<20480;counter++)
	{
		Data = copy_u16pImg[counter] >> 8;

		/* Write the high byte */
		TFT_voidWriteData(Data);
		/* Write the low byte */
		Data = copy_u16pImg[counter] & 0x00FF;
		TFT_voidWriteData(Data);
	}
	
}

static void TFT_voidWriteCommand(u8 copy_u8Command)
{
	u8 Local_u8Temp;
	
	/* A0 is LOW */
	MGPIO_voidSetPinValue(TFT_A0_PIN,LOW);
	
	/* send command over SPI */
	SPI1_voidSendReceiveSync(copy_u8Command,&Local_u8Temp);
}

static void TFT_voidWriteData(u8 copy_u8Data)
{
	u8 Local_u8Temp;
	
	/* A0 is HIGH */
	MGPIO_voidSetPinValue(TFT_A0_PIN,HIGH);
	
	/* send data over SPI */
	SPI1_voidSendReceiveSync(copy_u8Data,&Local_u8Temp);
}

void TFT_voidFillColor(u16 color)
{
	u16 counter;
	u8 Data;

    /* set X address*/
	TFT_voidWriteCommand(0x2A);
	/* the beginning */
	TFT_voidWriteData(0);
	TFT_voidWriteData(0);
	/* the end */
	TFT_voidWriteData(0);
	TFT_voidWriteData(127);

	/* set Y address*/
	TFT_voidWriteCommand(0x2B);
	/* the beginning */
	TFT_voidWriteData(0);
	TFT_voidWriteData(0);
	/* the end */
	TFT_voidWriteData(0);
	TFT_voidWriteData(159);

	/* RAM Write */
	TFT_voidWriteCommand(0x2C);

    /* show img */
	for(counter=0 ;counter<20480;counter++)
	{
		Data = color>> 8;

		/* Write the high byte */
		TFT_voidWriteData(Data);
		/* Write the low byte */
		Data = color & 0x00FF;
		TFT_voidWriteData(Data);
	}

}

void TFT_voidDrawRectangle(u8 x1, u8 x2, u8 y1, u8 y2 ,u16 color)
{
	u16 counter;
	u8 Data;

	u16 size = (x2-x1) * (y2-y1);// data validation is not specified

    /* set X address*/
	TFT_voidWriteCommand(0x2A);
	/* the beginning */
	TFT_voidWriteData(0);
	TFT_voidWriteData(x1);
	/* the end */
	TFT_voidWriteData(0);
	TFT_voidWriteData(x2);

	/* set Y address*/
	TFT_voidWriteCommand(0x2B);
	/* the beginning */
	TFT_voidWriteData(0);
	TFT_voidWriteData(y1);
	/* the end */
	TFT_voidWriteData(0);
	TFT_voidWriteData(y2);

	/* RAM Write */
	TFT_voidWriteCommand(0x2C);

    /* show img */
	for(counter=0 ;counter<size;counter++)
	{
		Data = color>> 8;

		/* Write the high byte */
		TFT_voidWriteData(Data);
		/* Write the low byte */
		Data = color & 0x00FF;
		TFT_voidWriteData(Data);
	}

}

void TFT_voidDrawChar(u8 x1, u8 x2, u8 y1, u8 y2 ,u16* letter)
{
	u16 counter;
	u8 Data;

	u16 size = (x2-x1+1) * (y2-y1+1);

    /* set X address*/
	TFT_voidWriteCommand(0x2A);
	/* the beginning */
	TFT_voidWriteData(0);
	TFT_voidWriteData(x1);
	/* the end */
	TFT_voidWriteData(0);
	TFT_voidWriteData(x2);

	/* set Y address*/
	TFT_voidWriteCommand(0x2B);
	/* the beginning */
	TFT_voidWriteData(0);
	TFT_voidWriteData(y1);
	/* the end */
	TFT_voidWriteData(0);
	TFT_voidWriteData(y2);

	/* RAM Write */
	TFT_voidWriteCommand(0x2C);

    /* show img */
	for(counter=0 ;counter<size;counter++)
	{
		u16 colorCopy;

		/* check for the validation of color of the letter
		 *  and change it to the selected color
		 */
	//	if( (color != letter[counter]) && (letter[counter] != Background) )
		//	colorCopy = color;

		    /* transfer data into 1 byte */
		    Data = letter[counter]>> 8;

		    /* Write the high byte */
		    TFT_voidWriteData(Data);

		    /* Write the low byte */
		    Data = letter[counter] & 0x00FF;
		    TFT_voidWriteData(Data);
	}
}

void TFT_voidStartClk(void)
{
	countSec1 ++;
	if(countSec1 == 10)
	{
		countSec1 = 0;
		countSec2 ++;
		TFT_voidDrawChar(46 ,55 ,0,13,NumPtr[countSec1]);// secs a7ad rest

		if(countSec2 == 6)
		{
			countSec2=0;
			countMin1++;
			TFT_voidDrawChar(58 ,67 ,0,13,NumPtr[countSec2]);// secs 34raat reset

			if(countMin1 == 10)
			{
				countMin1=0;
				countMin2 ++;
				TFT_voidDrawChar(74 ,83 ,0,13,NumPtr[countMin1]);// mins a7ad reset
				if(countMin2 == 6)
				{
					countMin2=0;
					countHor1 ++;
					TFT_voidDrawChar(86 ,95 ,0,13,NumPtr[countMin2]);// mins 34raat reset

					if(countHor1 == 10  &&  countHor2 != 2)
					{
						countHor1=0;
						countHor2 ++;
						TFT_voidDrawChar(100 ,109 ,0,13,NumPtr[countHor1]);// hours a7ad reset
					}

					else if( (countHor1 == 4) &&  (countHor2 == 2) )
					{
						countHor1=0;
						countHor2=0;
						TFT_voidDrawChar(112 ,121 ,0,13,NumPtr[countHor2]);// hours 34raat reset
						TFT_voidDrawChar(100 ,109 ,0,13,NumPtr[countHor1]);// hours a7ad reset
					}

					else
					{
					    TFT_voidDrawChar(100 ,109 ,0,13,NumPtr[countHor1]);// hours a7ad

					}
				}

				else
				{
					TFT_voidDrawChar(58 ,67 ,0,13,NumPtr[countSec2]);// secs 34raat
					TFT_voidDrawChar(46 ,55 ,0,13,NumPtr[countSec1]);// secs a7ad
					TFT_voidDrawChar(74 ,83 ,0,13,NumPtr[countMin1]);// mins a7ad
					TFT_voidDrawChar(86 ,95 ,0,13,NumPtr[countMin2]);// mins 34raat
				}

			}

			else
			{
				 TFT_voidDrawChar(58 ,67 ,0,13,NumPtr[countSec2]);// secs 34raat
				 TFT_voidDrawChar(46 ,55 ,0,13,NumPtr[countSec1]);// secs a7ad
				 TFT_voidDrawChar(74 ,83 ,0,13,NumPtr[countMin1]);// mins a7ad
			}
		}

		else
			{
			    TFT_voidDrawChar(58 ,67 ,0,13,NumPtr[countSec2]);// secs 34raat
			    TFT_voidDrawChar(46 ,55 ,0,13,NumPtr[countSec1]);// secs a7ad
			}
	}

	else
	{
		TFT_voidDrawChar(46 ,55 ,0,13,NumPtr[countSec1]);// secs a7ad
	}







}
