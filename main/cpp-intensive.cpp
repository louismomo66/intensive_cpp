#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include <stdlib.h>

static TaskHandle_t task_1= NULL;
static TaskHandle_t task_2= NULL;


static const uint8_t buf_len = 255;
static char *msg_ptr = NULL;
static volatile uint8_t msg_flag = 0;

void readMsg(void *pvParameter){
    char buffer[buf_len];
    int index = 0;
    int c;

    printf("\nEnter a message:");

    while(1){
        c = getchar();

        if (c == EOF){
            vTaskDelay(pdMS_TO_TICKS(100));
            continue;
        }
        if(c == '\r'){
            continue;
        }

        if(c == '\n'){
            buffer[index] = '\0';
            msg_ptr = strdup(buffer);
            msg_flag = 1;
            index = 0;
            printf("\nEnter a message:");
        }
        else if (index < buf_len - 1){
            buffer[index++] =(char)c;
            printf("%c", c);
            fflush(stdout);
    }
        vTaskDelay(pdMS_TO_TICKS(10));
    }

}

void printMsg(void *pvParameter){
    while(1){
        if (msg_flag){
            printf("\nReceived message: %s\n", msg_ptr);
            free(msg_ptr);
            msg_ptr = NULL;
            msg_flag = 0;
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

const char message[] = "Hello from Task 1!";
static volatile int ledDelay = 1000; // Delay in milliseconds for LED toggle
void startTask1(void *pvParametre){
    int msglen = sizeof(message);
    while(1){
        printf("\n");
        for(int i = 0; i<msglen;i++){
            printf("%c", message[i]);
        }
        printf("\n"); 
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void startTask2(void *pvParameter){
    while(1){
        printf("*");
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void toggleLed(void *pvParameter){
    while(1){
        gpio_set_level(GPIO_NUM_12, 1);
        vTaskDelay(ledDelay / portTICK_PERIOD_MS);
        gpio_set_level(GPIO_NUM_12, 0);
        vTaskDelay(ledDelay / portTICK_PERIOD_MS);
    }
}

void ReadSerialInput(void *pvParameter)
{
    char input[16];
    int index = 0;
    int c;

    printf("\nEnter new LED delay in ms: ");
    fflush(stdout);

    while (1)
    {
        c = getchar();   // Read one character

        if (c == '\n' || c == '\r')
        {
            input[index] = '\0';

            int newDelay = atoi(input);

            if (newDelay < 50) {
                printf("\nMinimum delay is 50 ms\n");
            } else {
                ledDelay = newDelay;
                printf("\nLED delay updated to %d ms\n", ledDelay);
            }

            index = 0;
            printf("\nEnter new LED delay in ms: ");
            fflush(stdout);
        }
        else if (index < sizeof(input) - 1 && c != EOF)
        {
            input[index++] = c;
            printf("%c", c);   // echo character
            fflush(stdout);
        }

        vTaskDelay(pdMS_TO_TICKS(10));   // prevent starvation
    }
}


extern "C" void app_main(void)
{   
    
    gpio_reset_pin(GPIO_NUM_12);
    gpio_set_direction(GPIO_NUM_12, GPIO_MODE_OUTPUT);

    // xTaskCreate(startTask1, "Task 1", 2048, NULL, 2, &task_1); 
    // xTaskCreate(startTask2, "Task 2", 2048, NULL, 1, &task_2);
    // xTaskCreate(toggleLed, "Toggle LED Task", 2048, NULL, 5, NULL);
    // xTaskCreate(ReadSerialInput, "Read Serial Input Task", 4096, NULL, 3, NULL);
    xTaskCreate(readMsg, "Read Message Task", 4096, NULL, 2, NULL);
    xTaskCreate(printMsg, "Print Message Task", 4096, NULL, 1, NULL);

// while(1){
//     for(int i = 0;i<3;i++){
//         vTaskSuspend(task_1); 
//         vTaskDelay(2000 / portTICK_PERIOD_MS); 
//         vTaskResume(task_1); 
//         vTaskDelay(2000 / portTICK_PERIOD_MS);
//     }

//     if (task_1 != NULL){ 
//         vTaskDelete(task_1); 
//         task_1 = NULL; 
//     } 
       
// }
}
