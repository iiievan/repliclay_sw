
#include "consoleUtils.h"
#include "soc_AM335x.h"
#include "beaglebone.h"
#include "interrupt.h"
#include "dmtimer.h"
#include "error.h"
#include "hal_bspInit.h"


#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

#include <string>

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif
  
extern void Entry(void);

#define NUM_INTERRUPTS                 (128u)
void (*fnRAMVectors[NUM_INTERRUPTS])(void);

xSemaphoreHandle xBinarySemaphore;
void init(void)
{
	halBspInit();
}

void vTask1(void *pvParameters) {
    int i = 0;
    while (1) {
       xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
       ConsoleUtilsPrintf("Task 1 message %d!\r\n", i++);
       xSemaphoreGive(xBinarySemaphore);
       vTaskDelay(1000);
    }
}

void vTask2(void *pvParameters) {
    int i = 0;
    while (1) {
        xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
        ConsoleUtilsPrintf("Task 2 message %d!\r\n", i++);
        xSemaphoreGive(xBinarySemaphore);
        vTaskDelay(500);
    }
}

void Delay_HMSM(uint32_t Hours, uint32_t Minutes, uint32_t Seconds, uint32_t Millis)
{
    /* Block for 500ms. */
    TickType_t  xTicksToDelay  = 1; /* Lets do a minimum of 1 Tick Period */
    if(Hours)   xTicksToDelay += Hours   * 3600 * 1000 / portTICK_PERIOD_MS;
    if(Minutes) xTicksToDelay += Minutes *   60 * 1000 / portTICK_PERIOD_MS;
    if(Seconds) xTicksToDelay += Seconds * 1000        / portTICK_PERIOD_MS;
    if(Millis)  xTicksToDelay += Millis                / portTICK_PERIOD_MS;
    
    vTaskDelay( xTicksToDelay );
}

void vApplicationStackOverflowHook(TaskHandle_t pxTask, signed char *pcTaskName)
{
	(void) pcTaskName;
	(void) pxTask;

	/**
	 * Run time stack overflow checking is performed if
	 * configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.
	 * This hook function is called if a stack overflow is
	 * detected.
	 */
	for (;;) 
    {
        Delay_HMSM(0,0,1,0);
        ConsoleUtilsPrintf("\n\r\n\rIn Function:%s.\n\r",__FUNCTION__);
	}
	taskDISABLE_INTERRUPTS();
}

#ifdef __cplusplus
}
#endif
int main() 
{
    init();
    ConsoleUtilsPrintf("Platform initialized.\r\n");

    xBinarySemaphore = xSemaphoreCreateBinary();
    xSemaphoreGive(xBinarySemaphore);

    int ret = xTaskCreate(vTask1, "Task 1", 1000, NULL, 1, (TaskHandle_t *)NULL);
    if (ret == pdPASS) 
    {
        ConsoleUtilsPrintf("Task %x succesfully created.\r\n", vTask1);
    } 
    else 
    {
        ConsoleUtilsPrintf("Task not created: %d", ret);
    }
    
    ret =  xTaskCreate(vTask2, "Task 2", 1000, NULL, 2, (TaskHandle_t *)NULL);
    if (ret == pdPASS) 
    {
        ConsoleUtilsPrintf("Task %x succesfully created.\r\n", vTask2);
    } 
    else 
    {
        ConsoleUtilsPrintf("Task not created: %d", ret);
    }
    
    vTaskStartScheduler();

    while(1);


}

