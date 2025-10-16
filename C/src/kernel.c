#include "../headers/header.h"

size_t terminal_row = 0;
size_t terminal_column = 0;
uint8_t terminal_color = 0;
uint16_t* terminal_buffer = (uint16_t*)VGA_MEMORY;

extern void outb(uint16_t port, uint8_t value);

static inline uint8_t vga_entry_color(enum vga_color text_color, enum vga_color bg_color)
{ 
	return (text_color | bg_color << 4); 
}

void term_move_cursor()
{
    if (terminal_row >= VGA_HEIGHT || terminal_column >= VGA_WIDTH)
        return;
    uint16_t pos = terminal_row * VGA_WIDTH + terminal_column;
    outb(VGA_PORT_COMMAND, 14);
    outb(VGA_PORT_DATA, (pos >> 8) & 0xFF);
    outb(VGA_PORT_COMMAND, 15);
    outb(VGA_PORT_DATA, pos & 0xFF);
}

static inline uint16_t vga_entry(unsigned char c, uint8_t color)
{ 
	return ((uint16_t) c | (uint16_t) color << 8); 
}

void term_init()
{
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	for (size_t y = 0; y < VGA_HEIGHT; y++)
	{
		for (size_t x = 0; x < VGA_WIDTH; x++)
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void term_set_color(uint8_t color)
{ 
	terminal_color = color; 
}

void term_put_entry_at(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}


void term_scroll()
{
	ft_memmove(terminal_buffer, terminal_buffer + VGA_WIDTH, 65535);
	terminal_column = 0;
	terminal_row = 24;
	term_move_cursor();
}


void term_put_char(char c)
{
	if (c == '\n')
	{
		terminal_column = 0;
		terminal_row++;
	}
	else
	{
		term_put_entry_at(c, terminal_color, terminal_column, terminal_row);
		++terminal_column;
		if (terminal_column == VGA_WIDTH)
		{
			terminal_column = 0;
			terminal_row++;
		}
	}
	if (terminal_row == VGA_HEIGHT)
		{ term_scroll(); }
	term_move_cursor();
}

void term_write(const char* str, size_t len)
{
	for (size_t i = 0; i < len; i++)
		term_put_char(str[i]);
}

void term_write_str(const char* str)
{ 
	term_write(str, ft_strlen(str)); 
}