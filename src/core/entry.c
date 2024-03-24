#include <stdint.h>
#include "gdt.h"

void entry(void)
{
	init_gdt();
}
