#ifndef CONSOLE_H    /* This is an "include guard" */
#define CONSOLE_H

#define UART_ID uart0

void console_putc(char c) ;
char console_getc(void);
void console_puts(char *s);
int console_gets(char *s, int len);

#endif /* CONSOLE_H */