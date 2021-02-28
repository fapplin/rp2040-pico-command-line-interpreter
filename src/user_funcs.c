#include "user_funcs.h"
#include "console.h"
#include "hardware/irq.h"
#include "hardware/uart.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Each user function you create, you must also
// add to the init_user_functions routine.
void init_user_functions() {
  // This is my first user-defined function. I give
  // the command a name - in this case "blink_led"
  // then I point the user_functions struct array
  // to the actual name of my user-defined function.
  strcpy(user_functions[0].command_name, "blink_led");
  user_functions[0].user_function = blink_led;

  strcpy(user_functions[1].command_name, "read_pir_sensor");
  user_functions[1].user_function = read_pir_sensor;
}

void blink_led(char tokens[][MAX_STRING_SIZE]) {
  uint8_t LED_PIN = atoi(tokens[1]);
  uint16_t iters = atoi(tokens[2]);
  uint16_t millis = atoi(tokens[3]);

  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);

  for (int i = 0; i < iters; i++) {
    gpio_put(LED_PIN, 1);
    sleep_ms(millis);
    gpio_put(LED_PIN, 0);
    sleep_ms(millis);
  } // end for
}

void read_pir_sensor(char tokens[][MAX_STRING_SIZE]) {

  char str[80];

  uint8_t pirState = 0; // Init state to low
  uint8_t val;
  uint8_t PIR_PIN = atoi(tokens[1]);

  console_putc('\n');

  gpio_init(25);
  gpio_set_dir(25, GPIO_OUT);

  gpio_init(PIR_PIN);
  gpio_set_dir(PIR_PIN, GPIO_IN);

  sleep_ms(5000);

  for (int i = 0; i < 5000; i++) {
    val = gpio_get(PIR_PIN); // HIGH or LOW?
    // sprintf(str, "val: %d\n", val);
    // console_puts(str);

    if (val == 1) // check if the input is HIGH
    {
      gpio_put(25, 1); // turn LED ON

      if (pirState == 0) {
        console_puts("Motion detected!\n"); // print on output change
        pirState = 1;
      } // end if
    } else {
      gpio_put(25, 0); // turn LED OFF

      if (pirState == 1) {
        console_puts("Motion ended!\n"); // print on output change
        pirState = 0;
      } // end if
    }   // end if

    sleep_ms(12);
  } // end for

} // end read_pir_sensor