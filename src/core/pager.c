#include "pager.h"

uint32_t page_directory[1024] __attribute__((aligned(4096))) = {0};
uint32_t page_table1[1024] __attribute__((aligned(4096))) = {0};
extern uint32_t boot_page_table1[1024];

void pager_set_directory(void);

void idpaging(uint32_t *first_pte, uint32_t from, int size)
{
	from = from & 0xfffff000; // discard bits we don't want
	for (; size > 0; from += 4096, size -= 4096, first_pte++)
	{
		*first_pte = from | 1; // mark page present.
	}
}

void pager_init(void)
{
	idpaging(page_table1, 0x0, 0x100000);
	page_table1[0xB8] |= 3;

	page_directory[0] = ((uint32_t)page_table1 - 0xC0000000) | 0x003;
	page_directory[768] = ((uint32_t)boot_page_table1 - 0xC0000000) | 0x003;

	uint32_t dir = (uint32_t)page_directory - 0xC0000000;
	asm("movl %0, %%eax\nmovl %%eax, %%cr3" : : "r"(dir) : "eax");
}
