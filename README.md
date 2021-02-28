# rp2040-pico-command-line-interpreter

This is a work in progress. I wanted to create a command line interpreter for the Raspberry Pi Pico (rp2040) with the idea that a programmer could simply add code into a couple "C" source files, recompile, and the programmer would be able to run those commands in a pseudo shell like environment.

As an example, suppose I wanted to test several routines that I wrote to use different sensors. Instead of having several programs, I could have just one and use commands to execute them. If I wanted to blink an LED on a certain pin, I could run a command like the following from the command line interpreter:
```
$blink_led 25 10 250
OK
$
```

The programmer defines a routine in a "C" source file (user_funcs.c) and accompanying header file (user_funcs.h) like:

This would be added to the file user_funcs.c
```
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
```
The parameters are passed in as an array of string tokens. These are the arguments to the command line command. The command name is tokens[0]. In the example code above, the arguments are the LED pin, the number of times to blink, and the duration of the blink (in milliseconds).

The command blink_led also has to be added to an intialization routine. The two pieces of information are the command name and the function name.

This also needs modifying in user_funcs.c
```
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
```

Finally, the function needs to be added to the accompanying header file (user_funcs.h).

```
void blink_led(char tokens[][MAX_STRING_SIZE]);
```

This should be all the programmer has to worry about. Run the make command in the build directory and then copy the .uf2 file to the Pico. The command line interpreter should start to run with the prompt "$" waiting for you to type a command to run.

