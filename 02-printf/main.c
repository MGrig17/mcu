// Подключить заголовочные файлы трех библиотек:
#include "stdio.h" // заголовочный файл стандартной библиотеки ввода вывода (stdio)
#include "stdlib.h" // заголовочный файл стандартной библиотеки: stdlib.h
#include "pico/stdlib.h" // заголовочный файл базового взаимодействия с микрокнтроллером: pico/stdlib.h


// Задать макросы с именем устройства и версией прошивки:
#define DEVICE_NAME "my-pico-device"
#define DEVICE_VRSN "v0.0.1"

// Создать до функции main() глобальную переменную и глобальную постоянную:
uint32_t global_variable = 0;

const uint32_t constant_variable = 42;

int main() 
{
    // -- В теле main() инициализировать систему ввода/вывода stdio следующей строчкой:
    stdio_init_all(); 
    while (1) 
    {
        // В тело бесконечного цикла добавить вывод просто строковой константы
        printf("Hello World!\n");

        // В тело бесконечного цикла добавить вывод строки с аргументами:
        printf("device name: '%s', firmware version: %s\n", DEVICE_NAME, DEVICE_VRSN); 

        // В теле бесконечного цикла считать счетчик микросекунд и вывести его значение:
        uint64_t timestamp = time_us_64(); 
        printf("system timestamp: %llu us\n", timestamp);
        
        // В теле бесконечного цикла создать переменную на стеке и вывести ее адрес и значение в разных форматах:
        uint32_t stack_variable = 8888;
        printf("stack variable | addr = 0x%X | value = %u\n", &stack_variable, *(&stack_variable));
        printf("stack variable | addr = 0x%X | value = %X\n", &stack_variable, *(&stack_variable));
        printf("stack variable | addr = 0x%X | value = 0x%X\n", &stack_variable, *(&stack_variable));

        // В теле бесконечного цикла инкрементировать значение глобальной переменной и вывести ее значение и адрес:
        global_variable++;
        printf("global variable | addr = 0x%X | value = %u\n", &global_variable, *(&global_variable));

        // В теле бесконечного цикла создать переменную на куче, записать в нее значение и вывести ее значение и адрес:
        uint32_t* heap_variable = (uint32_t*)malloc(sizeof(uint32_t));
        *heap_variable = 5555;
        printf("heap variable | addr = 0x%X | value = %u\n", heap_variable, *heap_variable);
        // <- Error! Go to p.9 in instruction and read warning
        
        // В тело бесконечного цикла добавить вывод адреса и значения постоянной:
        printf("constant variable | addr = 0x%X | value = %u\n", &constant_variable, *(&constant_variable));

        // В теле бесконечного цикла добавить вывод адреса и значения строковой постоянной:
        printf("constant string | addr = 0x%X | value = 0x%X, [%s]\n", DEVICE_NAME, *((uint32_t*)DEVICE_NAME), DEVICE_NAME);

        // В теле бесконечного цикла добавить вывод адреса и значения одного из множества регистров RP2040 с обращением прямо по адресу:
        printf("reg chip id | addr = 0x%X | value = 0x%X\n", 0x40000000, *((uint32_t*)0x40000000));

        // В теле бесконечного цикла добавить вывод адреса и значения global_variable с обращением прямо по адресу:
        printf("var by addr | addr = 0x%X | value = %u\n", 0x20002278, *((uint32_t*)0x20002278));
        
        // В теле бесконечного цикла добавить вывод адреса функции main и первых бинарных команд этой функции:
        printf("main function | addr = 0x%X | value = 0x%X\n", main, *((uint32_t*)main));

        // Добавить задержку в тело бесконечного цикла:
        sleep_ms(1000);

    }

}