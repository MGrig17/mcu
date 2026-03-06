// Подключить заголовочные файлы трех библиотек:
#include "stdio.h" // заголовочный файл стандартной библиотеки ввода-вывода (stdio)
#include "stdlib.h" // заголовочный файл стандартной библиотеки: stdlib.h
#include "pico/stdlib.h" // заголовочный файл базового взаимодействия с микрокнтроллером: pico/stdlib.h
#include "hardware/gpio.h"

// Задать макросы с именем устройства и версией прошивки:
#define DEVICE_NAME "my-pico-device"
#define DEVICE_VRSN "v0.0.1"

// Создать до функции main() глобальную переменную и глобальную постоянную:
uint32_t global_variable = 0;

const uint32_t constant_variable = 42;
const uint LED_PIN = 25;

int main() {
    // -- В теле main() инициализировать систему ввода/вывода stdio следующей строчкой:
    stdio_init_all(); // В теле `main()` инициализировать систему ввода/вывода `stdio` следующей строчкой

    gpio_init(LED_PIN); // Инициализировать нужный нам GPIO вывод в начале функции `main`:
    gpio_set_dir(LED_PIN, GPIO_OUT); // Настроить GPIO вывод как выход:

    while (1){

        // добавить в тело бесконечного цикла блокирующее посимвольное считывание из USB через stdio
       char symbol = getchar(); 
        // добавить вывод в терминал считанный символ и его код в ASCII. Пример для вывода кода символа в ASCII
       printf("received char: %c [ ASCII code: %d ]\n", symbol, symbol); // 

       // После вывода кода символа в ASCII, добавить логику включения светодиода при приеме символа e (e от "enable"):
        switch(symbol){
        case 'e':
	       gpio_put(LED_PIN, true);
	       printf("led enable done\n");
	       break;
        
        // добавить логику выключения светодиода при приеме символа d (d от "disable");
        case 'd':
            gpio_put(LED_PIN, false);
            printf("led disable done\n");
            break;
        // добавить логику вывода имени и версии устройства при приеме символа v (v от "version")
        case 'v':
            printf("device name: '%s', firmware version: %s\n", DEVICE_NAME, DEVICE_VRSN);
            break;

        default:
	        break;        
        }

    }

}