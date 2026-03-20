#include "led-task.h"

#include "pico/stdlib.h"
#include "hardware/gpio.h"

const uint LED_PIN = 25;
uint LED_BLINK_PERIOD_US = 500000;

uint64_t led_ts;
led_state_t led_state;

// создать функцию инициализации, она должна:
// - задать состояние светодиода OFF
// - задать метку времени led_ts как ноль
// - проинициализировать светодиод

void led_task_init() {
    led_state = 0;
    led_ts = 0;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}

// создать функцию обработчика. В зависимости от состояния она должна:
// - включать светодиод
// - выключать светодиод
// - неблокирующе мигать светодиодом

void led_task_handle() {
    switch (led_state)
    {
    case LED_STATE_OFF:
	    gpio_put(LED_PIN, 0);  
	    break;
    case LED_STATE_ON:
	    gpio_put(LED_PIN, 1);
	    break;
    case LED_STATE_BLINK:

	    if (time_us_64() > led_ts) {

            led_ts = time_us_64() + (LED_BLINK_PERIOD_US / 2);
            // здесь переключить светодиод (если горит - выключить, если не горит - включить)
            if (gpio_get(LED_PIN) == 0) {
                gpio_put(LED_PIN, 1);
            }
            else {
                gpio_put(LED_PIN, 0);
            }
        }
	    break;
    default:
	    break;
    }
}

void led_blink_set_period_ms(uint32_t period_ms) {
    LED_BLINK_PERIOD_US = period_ms * 1000;
}

void led_task_state_set(led_state_t state) {
    led_state = state;
}