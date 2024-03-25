#include "common.h"
#include "gdt.h"
#include "pager.h"

void entry(void)
{
	gdt_init();
	pager_init();
}
