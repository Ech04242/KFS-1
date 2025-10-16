#include "../headers/header.h"

extern uint8_t inb(uint16_t port);
extern size_t terminal_row;
extern size_t terminal_column;
extern uint8_t terminal_color;


void kernel_main(void)
{
	term_init();
	term_move_cursor();
	print_open_message();
	print_user();
	while (42){
		uint8_t status = inb(0x64);
		if (status & 1) {
			char c = keyboard_getchar();
            if (c == '\n'){
				term_put_char('\n');
				print_user();
			}
			else if (c == '\b'){
				if (terminal_column > 6){
					terminal_column--;
					term_put_entry_at(' ', 7, terminal_column, terminal_row);
					term_move_cursor();
				}
			}
			else if (c == F1)
				ft_printk("profil 1 a charger");
			else if (c == F2)
				ft_printk("profil 2 a charger");
			else if (c == F3)
				ft_printk("profil 3 a charger");
			else if (c == F4)
				ft_printk("profil 4 a charger");
			else if (c)
				term_put_char(c);
		}
	}
}