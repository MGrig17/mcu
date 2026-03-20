#pragma once // добавить директиву препроцессора для предотвращения многократного включения заголовочного файл

typedef void(*command_callback_t)(const char* args); // в файл protocol-task.h добавить объявление типа command_callback_t, являющего указателем на функцию:

// в файл protocol-task.h добавить объявление типа структуры команды, состоящего из имени команды, колбэка команды, описания команды:
typedef struct
{
	const char* command_name;
	command_callback_t command_callback;
	const char* command_help;
} api_t;

// в файл protocol-task.h добавить объявление прототипа функции инициализации, принимающей аргументом указатель на массив команд:
void protocol_task_init(api_t* device_api);

// в файл protocol-task.h добавить объявление прототипа функции обработчика, принимающей аргументом строку с командой:
void protocol_task_handle(char* command_string);