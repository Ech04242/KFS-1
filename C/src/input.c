#include "../headers/header.h"

extern uint8_t inb(uint16_t port);

static const char scancode_set1[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
	0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, 
    0, 0, ' '};

char keyboard_getchar(void)
{
	uint8_t scancode = inb(0x60);
	if (scancode & 0x80)
		return (0);
	return (scancode_set1[scancode]);
}