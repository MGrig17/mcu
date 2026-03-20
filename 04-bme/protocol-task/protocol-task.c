#include "protocol-task.h"
#include "stdio.h" // заголовочный файл стандартной библиотеки ввода-вывода (stdio)
#include "string.h" // заголовочный файл стандартной библиотеки работы со строками string.h

static api_t* api = {0};
static int commands_count = 0;

// в файл protocol-task.c добавить реализацию функции инициализации. 
// Функция должна сохранить указатель на массив комманд в переменную api, 
// подсчитать число команд и сохранить его в переменную commands_count;
// Подсказка!
// В массиве команд, после последней команды будет расположен элемент с нулевым значением вместо имени команды. 
// По нему можно понять, что вы дошли до конца массива команд.

void protocol_task_init(api_t* device_api) {
	api = device_api;
    commands_count = 0;
    for (int i = 0; api[i].command_name != 0; i++) {
        commands_count += 1;
    }
}
// в файл protocol-task.c создать обработчик. 
// Добавить в обработчик проверку на то, что command_string не равно NULL. 
// Если command_string равно NULL, то выйти из обработчика: строка команды еще не получена;
void protocol_task_handle(char* command_string) {
    if (command_string == NULL) {
        return;
    }
    const char* command_name = command_string;
    const char* command_args = NULL;

    // написать логику обработки полученной строки. Делим ее на команду и аргументы:
    char* space_symbol = strchr(command_string, ' ');
    if (space_symbol) {
	    *space_symbol = '\0';
	    command_args = space_symbol + 1;
    }
    else {
	    command_args = "";
    }
    printf("Command: %s\nArgs: %s\n", command_name, command_args); // добавить вывод найденных имени команды и ее аргументов;

    // написать цикл, который проходит по массиву команд api и ищет совпадение имени команды;
    // Подсказка
    // Для сравнения строк предлагается использовать функцию strcmp(). Она возвращает 0, если строки равны.
    // Пример ее использования: strcmp(command_name, api[i].command_name)
    int command_found = 0;
    for (int i = 0; i < commands_count; i += 1) {
        if (strcmp(command_name, api[i].command_name) == 0) {
            command_found = 1;
            //вызывать колбэк найденой команды. В аргументы колбэка передать строку с аргументами от пользователя:
            api[i].command_callback(command_args);
            break;
        }
    }
    // вывести ошибку, если команда не была найдена в списке команд;
    if (command_found == 0) {
        printf("Error! Try again, loser");
    }
}
