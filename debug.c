#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "debug.h"

/*!
 * \file debug.c
 * \brief Fonctions de mise au point interactive.
 */
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
		char option = getchar();	//!<Lire le premier caractère
		
		if (option == 'h' && getchar() == '\n')
		{
			print_help();			//!<Imprime l'aide du debug
		} 
		else if (option == 'c' && getchar() == '\n')
		{
			return false;			//!<Exite debug
		} 
		else if (option == 's' && getchar() == '\n')
		{
			return true;			//!<Exécute instruction suivant
		} 
		else if (option == 'r' && getchar() == '\n')
		{
			print_cpu(pmach);		//!<Imprime l'information de cpu
		} 
		else if (option == 'd' && getchar() == '\n')
		{
			print_data(pmach);		//!<Imprime l'information de cpu
		} 
		else if ((option == 't' || option == 'p') && getchar() == '\n')
		{
			print_program(pmach);	//!<Imprime l'information de program
		} 
		else if (option == 'm' && getchar() == '\n')
		{
			print_cpu(pmach);		//!<Imprime les information de cpu et de data
			print_data(pmach);
		} 
		else if ((option == 'R') && (getchar() == 'E') && (getchar() == 'T') && (getchar() == '\n'))
		{
			return true;			//!<Exécute instruction suivant
		} 
		else if (option == '\n')	
		{
			return true;			//!<Exécute instruction suivant
		} 
		else
		{
			while(getchar() != '\n');	//!<Ignore les restes caractères
		}	

		return debug_ask(pmach);	//!<Continue debug cette instruction
}
