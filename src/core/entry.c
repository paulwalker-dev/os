#include "common.h"
#include "tty.h"
#include "gdt.h"
#include "pager.h"

void entry(void)
{
	gdt_init();
	pager_init();
	tty_init();
	tty_puts("Hello,\nWorld!\n");
	tty_puts("Hello,\nWorld!\n");
	tty_puts("Hello,\nWorld!\n");
	tty_puts("Hello,\nWorld!\n");
	tty_puts("Hello,\nWorld!\n");
	tty_puts("Hello,\nWorld!\n");
	tty_puts("Hello,\nWorld!\n");
	tty_puts("Hello,\nWorld!\n");
}
