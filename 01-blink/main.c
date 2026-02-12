#include "pico/stdlib.h"
#include "hardware/gpio.h"
const uint LED_PIN = 25;
int main()
{
// весь следующий код пишем тут
gpio_init(LED_PIN); // 8.  Инициализировать нужный нам GPIO вывод в начале функции `main`:
gpio_set_dir(LED_PIN, GPIO_OUT); // 9. Настроить GPIO вывод как выход:
while (1) // 10. Затем необходимо создать бесконечный цикл `while (1)`:
{
// код мигания пишем здесь
gpio_put(LED_PIN, 1);
sleep_ms(250);
gpio_put(LED_PIN, 0);
sleep_ms(1000);
}
}