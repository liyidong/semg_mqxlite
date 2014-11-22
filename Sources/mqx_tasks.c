/* ###################################################################
 **     Filename    : mqx_tasks.c
 **     Project     : ProcessorExpert
 **     Processor   : MKL25Z128VLH4
 **     Component   : Events
 **     Version     : Driver 01.00
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2014-11-21, 21:35, # CodeGen: 0
 **     Abstract    :
 **         This is user's event module.
 **         Put your event handler code here.
 **     Settings    :
 **     Contents    :
 **         MainTask - void MainTask(uint32_t task_init_data);
 **
 ** ###################################################################*/
/*!
 ** @file mqx_tasks.c
 ** @version 01.00
 ** @brief
 **         This is user's event module.
 **         Put your event handler code here.
 */
/*!
 **  @addtogroup mqx_tasks_module mqx_tasks module documentation
 **  @{
 */
/* MODULE mqx_tasks */

#include "Cpu.h"
#include "Events.h"
#include "mqx_tasks.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* User includes (#include below this line is not maintained by Processor Expert) */


_task_id mainTaskId;
_task_id adTaskId;
_task_id armTaskId;

LWEVENT_STRUCT lwevent;

/*
 ** ===================================================================
 **     Event       :  MainTask (module mqx_tasks)
 **
 **     Component   :  Task1 [MQXLite_task]
 **     Description :
 **         MQX task routine. The routine is generated into mqx_tasks.c
 **         file.
 **     Parameters  :
 **         NAME            - DESCRIPTION
 **         task_init_data  -
 **     Returns     : Nothing
 ** ===================================================================
 */
void MainTask(uint32_t task_init_data)
{
    int counter = 0;

    mainTaskId = _task_get_id();
    printf("%x\n", mainTaskId);

    _mqx_uint result;
    result = _lwevent_create(&lwevent, 0);
    if(result != MQX_OK)
    {
        printf("Error: event component could not be created.\n");
    }


    printf("Create ad task.\n");
    adTaskId = _task_create_at(0, AD_TASK, 0, AD_task_stack, AD_TASK_STACK_SIZE);
    if(MQX_NULL_TASK_ID == adTaskId)
    {
        printf("...failed.\n");
    }

    printf("Create arm task.\n");
    armTaskId = _task_create_at(0, ARM_TASK, 0, ARM_task_stack, ARM_TASK_STACK_SIZE);
    if(MQX_NULL_TASK_ID == armTaskId)
    {
        printf("...failed.\n");
    }

    while(1)
    {
        counter++;

        /* Write your code here ... */
        printf("%d This is from the main task.\n", counter);
        if(counter % 3 == 0)
        {
            _lwevent_set(&lwevent, 0x01);
        }
        if(counter % 7 == 0)
        {
            _lwevent_set(&lwevent, 0x02);
        }
    }
}

/*
 ** ===================================================================
 **     Event       :  ADTask (module mqx_tasks)
 **
 **     Component   :  Task2 [MQXLite_task]
 **     Description :
 **         MQX task routine. The routine is generated into mqx_tasks.c
 **         file.
 **     Parameters  :
 **         NAME            - DESCRIPTION
 **         task_init_data  -
 **     Returns     : Nothing
 ** ===================================================================
 */
void ADTask(uint32_t task_init_data)
{
    int counter = 0;

    while(1)
    {
        counter++;

        /* Write your code here ... */
        _mqx_uint event_result;
        event_result = _lwevent_wait_ticks(&lwevent, 0x01, TRUE, NULL);
        if(event_result != MQX_OK)
        {
            _task_block();
        }

        printf("%d This is from ad task.\n", counter);
        if(counter % 10 == 0)
        {
            _lwevent_clear(&lwevent, 0x01);
        }
    }
}

/*
 ** ===================================================================
 **     Event       :  ARMTask (module mqx_tasks)
 **
 **     Component   :  Task3 [MQXLite_task]
 **     Description :
 **         MQX task routine. The routine is generated into mqx_tasks.c
 **         file.
 **     Parameters  :
 **         NAME            - DESCRIPTION
 **         task_init_data  -
 **     Returns     : Nothing
 ** ===================================================================
 */
void ARMTask(uint32_t task_init_data)
{
    int counter = 0;

    while(1)
    {
        counter++;

        /* Write your code here ... */
        _mqx_uint event_result;
        event_result = _lwevent_wait_ticks(&lwevent, 0x02, FALSE, NULL);
        if(event_result != MQX_OK)
        {
             _task_block();
        }
        printf("%d This is from arm task.\n", counter);
        if(counter % 10 == 0)
        {
            _lwevent_clear(&lwevent, 0x02);
        }

    }
}

/* END mqx_tasks */

#ifdef __cplusplus
} /* extern "C" */
#endif

/*!
 ** @}
 */
/*
 ** ###################################################################
 **
 **     This file was created by Processor Expert 10.3 [05.08]
 **     for the Freescale Kinetis series of microcontrollers.
 **
 ** ###################################################################
 */
