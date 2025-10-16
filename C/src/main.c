#include "../headers/header.h"

extern uint8_t inb(uint16_t port);
extern size_t terminal_row;
extern size_t terminal_column;

void kernel_main(void)
{
	term_init();
	term_move_cursor();
	print_open_message();
	while (42){
		uint8_t status = inb(0x64);
		if (status & 1) {
			char c = keyboard_getchar();
            if (c == '\n')
				ft_printk("\\n detecter ! ");
			else if (c == '\b'){
				if (terminal_column){
					terminal_column--;
					term_put_entry_at(' ', 7, terminal_column, terminal_row);
					term_move_cursor();
				}
			}
			else if (c) {
				term_put_char(c);
			}
		}
	}
}