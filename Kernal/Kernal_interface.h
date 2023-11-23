/*
 * Kernal_interface.h
 *      Author: Haneen Ahmed
 *      Layer : Kernal
 *      stack: OS
 *
 */

#ifndef KERNAL_KERNAL_INTERFACE_H_
#define KERNAL_KERNAL_INTERFACE_H_
#include "../STD_TYPES.h"
void RTOS_voidStart(void);
//void RTOS_voidCreateTask (u8 Copu_u8Priority ,  void (*Copy_TaskFunc)(void)  , u16 Copy_u16Periodicity);
u8 RTOS_u8CreateTask(u8 Copy_u8Priority,void (*Copy_pvTaskFunc)(void),u16 Copy_u16Periodicity,u16 Copy_u16FirstDelay);

#endif /* KERNAL_KERNAL_INTERFACE_H_ */
