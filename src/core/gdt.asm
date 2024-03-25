GDT_Start:
	null_descriptor:
		dd 0
		dd 0
	kernel_code_descriptor:
		dw 0xffff
		dw 0
		db 0
		db 0b10011010
		db 0b11000001
		db 0xc0
	kernel_data_descriptor:
		dw 0xffff
		dw 0
		db 0
		db 0b10010010
		db 0b11000001
		db 0xc0
	GDT_End:

GDT_Descriptor:
	dw GDT_End - GDT_Start - 1
	dd GDT_Start

global gdt_init
gdt_init:
	cli
	lgdt [GDT_Descriptor]
	ret
