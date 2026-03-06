#ifndef LED_TASK_H // в файл led-task.h добавить объявление прототипов функций инициализации без аргументов и обработчика без аргументов;
#define LED_TASK_H

#include <stdint.h>

typedef enum {
    LED_STATE_OFF,
    LED_STATE_ON,
    LED_STATE_BLINK
} led_state_t;


void led_task_state_set(led_state_t state); // в файл led-task.h добавить объявление прототипов функций изменения состояния светодиода
void led_task_init();
void led_task_handle();
void led_blink_set_period_ms(uint32_t period_ms);

#endif