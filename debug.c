#include <stdio.h>
#include <string.h>
 #include <stdlib.h>
#include "debug.h"


void print_help()
{
	printf("Available commands:\n");
	printf("\th\thelp\n");
	printf("\tc\tcontinue (exit interactive debug mode)\n");
	printf("\ts\tstep by step (next instruction)\n");
	printf("\tRET\tstep by step (next instruction)\n");
	printf("\tr\tprint registers\n");
	printf("\td\tprint data memory\n");
	printf("\tt\tprint text (program) memory\n");
	printf("\tp\tprint text (program) memory\n");
	printf("\tm\tprint registers and data memory\n");
}

bool debug_ask(Machine *pmach)
{
		printf("DEBUG? ");
		char option = getchar();
		if (option == 'h' && getchar() == '\n')
		{
			print_help();
		} 
		else if (option == 'c' && getchar() == '\n')
		{
			return false;
		} 
		else if (option == 's' && getchar() == '\n')
		{
			return true;
		} 
		else if (option == 'r' && getchar() == '\n')
		{
			print_cpu(pmach);
		} 
		else if (option == 'd' && getchar() == '\n')
		{
			print_data(pmach);
		} 
		else if ((option == 't' || option == 'p') && getchar() == '\n')
		{
			print_program(pmach);
		} 
		else if (option == 'm' && getchar() == '\n')
		{
			print_cpu(pmach);
			print_data(pmach);
		} 
		else if (option == 'R')
		{
			if (getchar() == 'E' && getchar() == 'T' && getchar() == '\n')
			{
				return true;
			}
		} 
		else if (option == '\n')
		{
			return true;
		} 
		else
		{
			while(getchar() != '\n');
		}		
		return debug_ask(pmach);
}
