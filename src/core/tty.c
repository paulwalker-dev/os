#include "tty.h"

#define VGA ((volatile uint16_t *)0xC03FF000)

static tty_pos pos;

static tty_update_cursor(void)
{
	uint16_t coord = pos.y*TTY_WIDTH + pos.x;
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (coord & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((coord >> 8) & 0xFF));
}

void tty_init(void)
{
	uint16_t coord = 0;
	outb(0x3D4, 0x0F);
	coord |= inb(0x3D5);
	outb(0x3D4, 0x0E);
	coord |= ((uint16_t)inb(0x3D5)) << 8;

	pos.x = coord % TTY_WIDTH;
	pos.y = coord / TTY_WIDTH;
}

static void tty_nextpos()
{
	pos.x++;

	if (pos.x >= TTY_WIDTH) {
		pos.x = 0;
		pos.y++;
	}

	if (pos.y >= TTY_HEIGHT) {
		for (int y = 0; y < TTY_HEIGHT; y++) {
			for (int x = 0; x < TTY_WIDTH; x++) {
				uint32_t coord = y*TTY_WIDTH + x;
				if (y == TTY_HEIGHT-1) {
					VGA[coord] = 0;
					continue;
				}
				VGA[coord] = VGA[coord+TTY_WIDTH];
			}
		}

		pos.x = 0;
		pos.y = TTY_HEIGHT-1;
	}
	tty_update_cursor();
}

void tty_putc(char c)
{
	VGA[pos.y*TTY_WIDTH + pos.x] = (0x0f << 8) | c;
	tty_nextpos();
}

void tty_puts(const char *str)
{
	for (int i = 0; str[i]; i++) {
		if (str[i] == '\n') {
			pos.x = TTY_WIDTH;
			tty_nextpos();
			continue;
		}
		tty_putc(str[i]);
	}
}

void tty_setpos(tty_pos value)
{
	pos = value;
}

tty_pos tty_getpos(void)
{
	return pos;
}
