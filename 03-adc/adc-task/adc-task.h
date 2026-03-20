#ifndef ADC_TASK_H
#define ADC_TASK_H

// typedef enum
// {
// 	ADC_TASK_STATE_IDLE = 0,
// 	ADC_TASK_STATE_RUN = 1,
// } adc_task_state_t;

// Создать прототип функции инициализации модуля adc-task в файле adc-task.h^^
void adc_task_init(void);
float adc_task_voltage(void);
float adc_task_temperature(void);

// void adc_task_handle();
// void adc_task_set_state(adc_state_t state);

#endif