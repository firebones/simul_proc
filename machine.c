#include "machine.h"
#include "exec.h"
#include "debug.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
/*!
 * \file machine.c
 * \brief Description de la structure du processeur et de sa mémoire
 */

//! Méthode permettant d'afficher un message d'erreur et de quitter le programme .
void die(const char *texte){
	perror(texte);
	exit(1);
}

void load_program(Machine *pmach,
                  unsigned textsize, Instruction text[textsize],
                  unsigned datasize, Word data[datasize],  unsigned dataend) 
{
	pmach->_textsize = textsize;
	pmach->_text = text;
	pmach->_datasize = datasize;
	pmach->_data = data;
	pmach->_dataend = dataend;
	pmach->_cc = 0; //! initialisation à 0, cf page 8 du pdf
	pmach->_pc = 0;
	for(int i = 0 ; i < NREGISTERS-1 ; i++)//! de R0 à R14 initialisés à 0 .
	{
		pmach->_registers[i] = 0;
	}
	pmach->_registers[NREGISTERS-1] = datasize - 1;
}

void read_program(Machine *pmach, const char *programfile)
{
	
		FILE *fichier;
		if((fichier = fopen(programfile,"r"))== NULL)
			die("./machine.c read_program : erreur à l'ouverture du fichier");

		unsigned int textsize;
		if(fread(&textsize,sizeof(unsigned int),1,fichier)!= 1)
			die("./machine.c read_program : erreur à la lecture de textsize");

		unsigned int datasize;
		if(fread(&datasize,sizeof(unsigned int),1,fichier) != 1)
			die("./machine.c read_program : erreur à la lecture de datasize");

		unsigned int dataend;
		if(fread(&dataend,sizeof(unsigned int),1,fichier) != 1)
			die("./machine.c read_program : erreur à la lecture de dataend");

		Instruction *text = malloc(textsize*sizeof(Instruction));
		if(fread(text,sizeof(Word),textsize,fichier) != textsize)
			die("./machine.c read_program : erreur à la lecture des instructions");

		Word *data = malloc(datasize*sizeof(Word));
		if(fread(data,sizeof(Word),datasize,fichier) != datasize)
			die("./machine.c read_program : erreur à la lecture des données");

		//! initialisation de la machine .
		load_program(pmach,textsize,text,datasize,data,dataend);
		
		if(fclose(fichier)== -1)
			die("./machine.c read_program : erreur à la fermeture du fichier");
}

void dump_memory(Machine *pmach)
{
	FILE *dump;
	if((dump = fopen("dump.bin","w+"))== NULL)
		die("./machine.c dump_memory : erreur à l'ouverture du fichier .");

	if(fwrite(&(pmach->_textsize),sizeof(unsigned int ),1,dump)!= 1)
		die("./machine.c dump_memory : erreur à l'écriture de textsize .");

	if(fwrite(&(pmach->_datasize),sizeof(unsigned int ),1,dump)!= 1)
		die("./machine.c dump_memory : erreur à l'écriture de datasize .");

	if(fwrite(&(pmach->_dataend),sizeof(unsigned int ),1,dump)!= 1)
		die("./machine.c dump_memory : erreur à l'écriture de dataend .");

	if(fwrite(&(pmach->_text->_raw),sizeof(Word),pmach->_textsize,dump) != pmach->_textsize)
		die("./machine.c dump_memory : erreur à l'écriture des instructions .");

	if(fwrite(&(pmach->_data),sizeof(Word),pmach->_datasize,dump) != pmach->_datasize)
		die("./machine.c dump_memory : erreur à l'écriture des données .");

	if(fclose(dump) == -1)
		die("./machine.c dump_memory : erreur à la fermeture du fichier binaire .");

	printf("Instruction text[] = {\n");

	for(unsigned int i = 0; i < pmach->_textsize;i++)
	{
		Instruction *instruction = pmach->_text + i;
		if(i%4 == 0)
			printf("	0x%08X, ",instruction->_raw);
		else if(i%4 == 3)
			printf("0x%08X,\n",instruction->_raw);
		else
			printf("0x%08X, ",instruction->_raw);
	}

	printf("\n};\n");
	printf("unsigned textsize = %d;\n\n",pmach->_textsize);
	printf("Word data[] = {\n");

	for(unsigned int i = 0; i <pmach->_datasize;i++)
	{
		Word *donnee = pmach->_data + i;
		if(i%4 == 0)
			printf("	0x%08X, ",*donnee);
		else if(i%4 == 3)
			printf("0x%08X,\n",*donnee);
		else
			printf("0x%08X, ",*donnee);
	}

	printf("};\n");
	printf("unsigned datasize = %d;\n",pmach->_datasize);
	printf("unsigned dataend = %d;\n",pmach->_dataend);
}

void print_program(Machine *pmach)
{
		printf("*** PROGRAM (size: %d) ***\n",pmach->_textsize);
		for( unsigned int i = 0; i < pmach->_textsize ; i++ )
		{
			Instruction *instruction = pmach->_text + i;
			printf("Ox%04X: Ox%08X	",i,instruction->_raw);
			print_instruction(*instruction,i);
			printf("\n");
		}
		printf("\n");
}

void print_data(Machine *pmach)
{
printf("*** DATA (size: %d, end = Ox%08X (%d)) ***\n",pmach->_datasize,pmach->_dataend,pmach->_dataend);
	for(unsigned int i = 0; i < pmach->_datasize;i++)
	{
		Word *donnee = pmach->_data + i;
		if(i%3 == 2)
			printf("Ox%04X: Ox%08X %d\n",i,*donnee,*donnee);
		else
			printf("Ox%04X: Ox%08X %d       ",i,*donnee,*donnee);
	}
	printf("\n\n");
}

void print_cpu(Machine *pmach)
{	
	char type_cc;
	switch(pmach->_cc)
	{
		case CC_U : 
			type_cc = 'U';
		break;

		case CC_Z : 
			type_cc = 'Z';
		break;

		case CC_P : 
			type_cc = 'P';
		break;

		case CC_N : 
			type_cc = 'N';
		break;
	}
	printf("*** CPU ***\n");
	printf("PC: Ox%08X   CC: %c\n",pmach->_pc,type_cc);
	for(int i = 0;i < NREGISTERS;i++)
	{
		Word registre = pmach->_registers[i];
		if(i%3 == 2)
			printf("R%02d: Ox%08X %d\n",i,registre,registre);
		else
			printf("R%02d: Ox%08X %d     ",i,registre,registre);
	}
	printf("\n\n");
}

void simul(Machine *pmach, bool debug)
{
	int run = 1;
	while(run == 1){
		if(pmach->_pc >= pmach->_textsize)
		{

			error(ERR_SEGTEXT, pmach->_pc);
		} 
			

		Instruction instruction = pmach->_text[pmach->_pc++];
		trace("Executing",pmach,instruction,pmach->_pc-1);
		run = decode_execute(pmach,instruction);
		if(debug)
			debug_ask(pmach);
	}
}