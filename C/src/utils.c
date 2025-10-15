#include "../headers/header.h"

size_t ft_strlen(const char* str)
{
	size_t res = 0;

	while (*(str++))
	    res++;
	return res;
}