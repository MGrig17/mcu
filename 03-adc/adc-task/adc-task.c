#include "adc-task.h" 

#include "hardware/adc.h" // для работы с АЦП
#include "stdio.h" // заголовочный файл стандартной библиотеки ввода-вывода (stdio)
#include "pico/stdlib.h" // pico

// В adc-task.c создать константы с номером GPIO ножки и номером канала АЦП, который мы будем использовать. Ножка номер 26, канал АЦП номер 0
// const uint ADC_PIN = 26;
// const uint ADC_CHANNEL = 0; -> вар ниже вып аналогичные ф-ции, но не занимает места в памяти
#define ADC_PIN 26
#define ADC_CHANNEL 0
#define ADC_TEMPERATURE 4 // константа номером канала АЦП, подключенного к датчику температуры

// #define ADC_TASK_MEAS_PERIOD_US 100000 

// uint64_t adc_ts;
// adc_state_t adc_state;


void adc_task_init(void) { // Создать имплементацию функции инициализации в adc-task.c, содержащую следующие действия:
    // инициализировать периферийный модуль АЦП:
    adc_init();
    // инициализировать GPIO вывод на работу с АЦП:
    adc_gpio_init(ADC_PIN);
    adc_set_temp_sensor_enabled(true); //  включение встроенного датчика температуры
    // adc_ts = 0;
    // adc_state = ADC_TASK_STATE_RUN;
}

float adc_task_voltage(void){
    adc_select_input(ADC_CHANNEL); // выбрать канал АЦП для измерения:
    uint16_t voltage_counts = adc_read(); // запустить измерение и считать значение:
    float voltage_V = (3.3f / 4095.0f) * voltage_counts; // АЦП в RP2040 12-битный, значит максимальное значение = 2^12 - 1 = 4095
    return voltage_V;
}

float adc_task_temperature(void){
    adc_select_input(ADC_TEMPERATURE);
    uint16_t temp_counts = adc_read();
    float temp_V = (3.3f / 4095.0f) * temp_counts; // преобразовать значение в отсчетах (uint16_t temp_counts) в значение в вольтах (float temp_V)
    float temp_C = 27.0f - (temp_V - 0.706f) / 0.001721f; // преобразовать значение температуры в вольтах в значение в градусах цельсия
    return temp_C;
}

// void adc_task_set_state(adc_state_t state){
//     adc_state = state;
// }

// void adc_task_handle() {
//     switch(adc_state)
//     {
//     case ADC_TASK_STATE_RUN:
//         if (time_us_64() > adc_ts + ADC_TASK_MEAS_PERIOD_US) {
//             float temp_C = adc_task_temperature();
//             float voltage_V = adc_task_voltage();
//             adc_ts = time_us_64();
//             printf("%f %f\n", voltage_V, temp_C);
            
//         }
//         break;
//     default:
// 	    break;
//     }
// }