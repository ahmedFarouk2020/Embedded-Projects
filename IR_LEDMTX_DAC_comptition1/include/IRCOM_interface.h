/*********************************************************/
/* author  : Farouk                                      */
/* Version : v01                                         */
/* Date    : Sept. 3 2020                                */
/*********************************************************/

#ifndef IRCOM_INTERFACE_H
#define IRCOM_INTERFACE_H
/* get total frame in microsec. */
void IRCOM_voidReadFrameSegTime(void); //done
/* get digital bits frame */
//u8 IRCOM_voidGetData(u16* copy_DataArr);
void IRCOM_voidGetData(void); // done
/* check if frame is sent correctly or not */
/*  */
void IRCOM_voidCheckFrame(u16* copy_DataArr);
/* do function according to data received 
 * total data will be stored 
 * do specific function at last
 */
void IRCOM_voidDoFunction(void);



#endif
