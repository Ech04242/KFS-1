#include "../headers/header.h"

void kernel_main(void)
{
	term_init();
	term_move_cursor();   
	ft_printk("42\n");
}	