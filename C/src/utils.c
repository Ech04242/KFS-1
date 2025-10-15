#include "../headers/header.h"

uint32_t ft_strlen(const char* str)
{
	uint32_t res = 0;

	while (*(str++))
	    res++;
	return res;
}