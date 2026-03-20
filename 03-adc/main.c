// Подключить заголовочные файлы трех библиотек:
#include "stdio.h" // заголовочный файл стандартной библиотеки ввода-вывода (stdio)
#include "stdlib.h" // заголовочный файл стандартной библиотеки: stdlib.h
#include "pico/stdlib.h" // заголовочный файл базового взаимодействия с микрокнтроллером: pico/stdlib.h
#include "hardware/gpio.h"
#include "stdio-task/stdio-task.h" // в main.c добавить включение заголовочного файла модуля stdio-task:
#include "protocol-task/protocol-task.h" // в main.c добавить включение заголовочного файла модуля protocol-task
#include "led-task/led-task.h"
#include "adc-task/adc-task.h" // инициализация модуля adc-task

// Задать макросы с именем устройства и версией прошивки:
#define DEVICE_NAME "my-pico-device"
#define DEVICE_VRSN "v0.0.1"

// Создать до функции main() глобальную переменную и глобальную постоянную:
uint32_t global_variable = 0;

const uint32_t constant_variable = 42;
// const uint LED_PIN = 25;

// Объявление прототипов: (без них выдавало пачку ошибок), будет время можно поэкспериментировать
void version_callback(const char* args);
void led_on_callback(const char* args);
void led_off_callback(const char* args);
void led_blink_callback(const char* args);
void led_blink_set_period_ms_callback(const char* args);  
void help_callback(const char* args);
void get_adc_callback(const char* args);
void get_temp_callback(const char* args);


// в main.c создать массив команд с одной командой version, указателем на колбэк этой команды и с описанием:
// Внимание! Последним элементом массива должна быть нулевая структура. Это наша договоренность, чтобы легко определять длину массива.
// API устройства:
api_t device_api[] =
{
	{"version", version_callback, "get device name and firmware version"},
    {"on", led_on_callback, "turn led on"},
    {"off", led_off_callback, "turn led off"},
    {"blink", led_blink_callback, "make led blink"},
    {"period", led_blink_set_period_ms_callback, "set blink period in ms"},  
    {"help", help_callback, "print help"},
    {"get_adc", get_adc_callback, "print voltage"},
    {"get_temp", get_temp_callback, "print temperature in C"},
    // {"tm_start", tm_start_callback, "start measures"}, //  <=> restore adc-task into RUN
    // {"tm_stop", tm_stop_callback, "stop measures"},
	{NULL, NULL, NULL},
};

// в main.c создать функцию с именем version_callback для вывода версии устройства:
void version_callback(const char* args) {
	printf("device name: '%s', firmware version: %s\n", DEVICE_NAME, DEVICE_VRSN);
}

void led_on_callback(const char* args) {
    led_task_state_set(LED_STATE_ON);
}
void led_off_callback(const char* args) {
    led_task_state_set(LED_STATE_OFF);
}
void led_blink_callback(const char* args) {
    led_task_state_set(LED_STATE_BLINK);
}
void led_blink_set_period_ms_callback(const char* args) {
    uint period_ms = 0;
    int res = sscanf(args, "%u", &period_ms);
    if (period_ms == 0) {
        printf("Error!");
        return;
    }   
    led_blink_set_period_ms(period_ms);//led_task_set_blink_period_ms(period_ms); //led_task_set_blink_period_ms
}
void help_callback(const char* args) {
    for (int i = 0; device_api[i].command_name != NULL; i++) {
        printf("command name: '%s', description %s\n", device_api[i].command_name, device_api[i].command_help);
    }
}
void get_adc_callback(const char* args) {
    float voltage_V = adc_task_voltage();
    printf("%f\n", voltage_V);
}
void get_temp_callback(const char* args) {
    float temp_C = adc_task_temperature();
    printf("%f\n", temp_C);
}
// void tm_start_callback(const char* args) {
//     adc_state = ADC_TASK_STATE_RUN;
//     printf("ADC measurements started\n");
// }
// void tm_stop_callback(const char* args) {
//     adc_state = ADC_TASK_STATE_IDLE;
//     printf("ADC measurements stopped\n");
// }

int main() {
    // -- В теле main() инициализировать систему ввода/вывода stdio следующей строчкой:
    stdio_init_all(); // В теле `main()` инициализировать систему ввода/вывода `stdio` следующей строчкой
    protocol_task_init(device_api);
    led_task_init();
    adc_task_init(); // инициализация модуля adc-task

    // перед бесконечным циклом один раз вызвать функцию инициализации stdio_task
    stdio_task_init();

    while (1){
        char *cmd = stdio_task_handle();
        protocol_task_handle(cmd);
        led_task_handle();

    }
}