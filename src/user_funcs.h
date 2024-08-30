#ifndef USER_FUNCS_H    /* This is an "include guard" */
#define USER_FUNCS_H

#define NUMBER_OF_STRING 10
#define MAX_STRING_SIZE 25

#define MAX_USER_FUNCTIONS 10

typedef void (*user_func)(char tokens[][MAX_STRING_SIZE]);

typedef  struct usr_funcs {

       char  command_name[20] ;
       char  command_help[80] ;
       user_func  user_function; // function pointer 

 } usr_funcs;

extern usr_funcs user_functions[MAX_USER_FUNCTIONS];


#define MAX_TIMINGS	85


void init_user_functions(); 


void blink_led(char tokens[][MAX_STRING_SIZE]);
void read_pir_sensor(char tokens[][MAX_STRING_SIZE]);
void calc(char tokens[][MAX_STRING_SIZE]);


#endif /* USER_FUNCS_H */
