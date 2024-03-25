#pragma once
#include "common.h"

#define TTY_WIDTH (80)
#define TTY_HEIGHT (25)

typedef struct {
	uint8_t x, y;
} tty_pos;

void tty_init(void);

void tty_putc(char);
void tty_puts(const char *);

void tty_setpos(tty_pos value);
tty_pos tty_getpos(void);
