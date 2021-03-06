/*
 * seal_MSG.h
 *
 * Created: 30-Apr-18 22:47:57
 *  Author: Ethan
 */

#ifndef SEAL_MSG_H_
#define SEAL_MSG_H_

//#include "seal_RTOS.h"
#include "seal_Types.h"

#define CTRL_STACK_SIZE                 (1000 / sizeof(portSTACK_TYPE))
#define CTRL_TASK_PRI                   (configMAX_PRIORITIES)

extern TaskHandle_t       xCTRL_th;           // Message accumulator for USB/MEM

/**
 * This function is the ISR callback intended for use with the VBUS interrupt.
 * It will be called on the rising and falling edge of VBUS.
 */
void vbus_detection_cb(void);

/**
 * Initializes the resources needed for the control task.
 * @return system error code. ERR_NONE if successful, or negative if failure (ERR_NO_MEMORY likely).
 */
int32_t CTRL_task_init(void);

/**
 * The control task. Only use as a task in RTOS, never call directly.
 */
void CTRL_task(void* pvParameters);

#endif /* SEAL_MSG_H_ */
