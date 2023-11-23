/*
 * Kernal_program.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: HP
 */
#include "../STD_TYPES.h"
#include "../BIT_MATH.h"
#include "../MCAL/Timer0/Timer0Interface.h"
#include "../MCAL/GlobleIInterrupt/GIEInterface.h"

#include "Kernal_interface.h"
#include "Kernal_private.h"
#include "Kernal_config.h"

typedef struct {
	u16 Periodicity;
	void (*TaskFunc)(void);
	u8 State;
		u16 FirstDelay;
}Task_type;

Task_type SystemTasks[TASK_NUM] = {{NULL}};

void RTOS_voidStart(void){

Timer0_voidSetCallBack(Scheduler);
GI_voidEnable();
Timer0_voidInit();
Timer0_voidStart();

}
//with first Delay
u8 RTOS_u8CreateTask(u8 Copy_u8Priority,void (*Copy_pvTaskFunc)(void),u16 Copy_u16Periodicity,u16 Copy_u16FirstDelay)
{
	u8 Local_u8ErrorState= OK;
	if(Copy_pvTaskFunc != NULL)
	{
		/*check if the given priority is available or not*/
		if(SystemTasks[Copy_u8Priority].TaskFunc == NULL)
		{
			SystemTasks[Copy_u8Priority].Periodicity= Copy_u16Periodicity;
			SystemTasks[Copy_u8Priority].TaskFunc= Copy_pvTaskFunc;
			SystemTasks[Copy_u8Priority].State= RESUMED;
			SystemTasks[Copy_u8Priority].FirstDelay = Copy_u16FirstDelay;
		}
		else
		{
			/*priority is not available*/
		}
	}
	else
	{
		Local_u8ErrorState= NOK;
	}
	return Local_u8ErrorState;
}

void RTOS_voidSuspendTask(u8 Copy_u8Priority)
{
	SystemTasks[Copy_u8Priority].State=SUSPENDED;
}

void RTOS_voidResumeTask(u8 Copy_u8Priority)
{
	SystemTasks[Copy_u8Priority].State= RESUMED;
}

void RTOS_voidDeleteTask(u8 Copy_u8Priority)
{
	SystemTasks[Copy_u8Priority].TaskFunc= NULL;
}

static void Scheduler (void)
{
	u8 Local_u8TaskCounter;

	for(Local_u8TaskCounter=0;Local_u8TaskCounter<TASK_NUM;Local_u8TaskCounter++)
	{
		if(SystemTasks[Local_u8TaskCounter].State==RESUMED)
		{
			if(SystemTasks[Local_u8TaskCounter].FirstDelay ==0)
			{
				/*Invoke the task function if it is not NULL*/
				if(SystemTasks[Local_u8TaskCounter].TaskFunc != NULL)
				{
					SystemTasks[Local_u8TaskCounter].TaskFunc();
				}
				/*Make 1st delay equal to periodicity-1*/
				SystemTasks[Local_u8TaskCounter].FirstDelay= SystemTasks[Local_u8TaskCounter].Periodicity-1;
			}
			else
			{
				/*1st delay is not zero, so decrement the 1st delay*/
				SystemTasks[Local_u8TaskCounter].FirstDelay--;
			}
		}
		else
		{
			/*Task is suspended, Do nothing*/
		}
	}
}


//without First Delay
/*void RTOS_voidCreateTask(u8 Copu_u8Priority , void (*Copy_TaskFunc)(void) , u16 Copy_u16Periodicity){

	if (Copy_TaskFunc != NULL){
		    SystemTasks[Copu_u8Priority].Periodicity = Copy_u16Periodicity;
		    SystemTasks[Copu_u8Priority].TaskFunc = Copy_TaskFunc;
	}

}
static void Scheduler(void){
     volatile static  u16  Local_u16SysTickCounter=0;
     Local_u16SysTickCounter++;
     u8 Local_TaskCounter;
     for (Local_TaskCounter=0; Local_TaskCounter<TASK_NUM ; Local_TaskCounter++){
    	 if (Local_u16SysTickCounter % SystemTasks[Local_TaskCounter].Periodicity ==0){
    		   if (SystemTasks[Local_TaskCounter].TaskFunc != NULL){
    			   SystemTasks[Local_TaskCounter].TaskFunc();
    		   }
    	 }else {

    	 //nothing
     }}}
*/
