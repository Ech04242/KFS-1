#include "../headers/header.h"

void kernel_main(void)
{
	term_init();
	term_move_cursor();   
	term_write_str("42\n");
}