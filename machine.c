#include "machine.h"
#include "exec.h"//possible?
#include "debug.h"//possible?
#include <stdio.h>
//PROBLEME: print_program

//kékireste : vérifications, tests .
void load_program(Machine *pmach,
                  unsigned textsize, Instruction text[textsize],
                  unsigned datasize, Word data[datasize],  unsigned dataend) 
{
	pmach->_textsize = textsize;
	pmach->_text = text;
	pmach->_datasize = datasize;
	pmach->_data = data;
	pmach->_dataend = dataend;
	pmach->_cc = 0; //initialisation à 0, cf page 8 du pdf
	pmach->_pc = 0;
	for(int i = 0 ; i < NREGISTERS-1 ; i++)//de R0 à R14 initialisés à 0 .
	{
		pmach->_registers[i] = 0;
	}
	pmach->_registers[NREGISTERS-1] = datasize - 1;
}

void read_program(Machine *mach, const char *programfile)
{
	//les entiers sont sur 32 bits .
	//kékonfé ? ^o^
	//Ouverture du fichier
	int fd = open(programfile,O_RDONLY);
	if(fd != -1)
	{
		//1) _textsize
		unsigned int textsize;
		read(fd,&textsize,32);

		//2) _datasize
		unsigned int datasize;
		read(fd,&datasize,32);

		//3) _dataend
		unsigned int dataend;
		read(fd,&dataend,32);

		for(unsigned int i = 0;i<textsize;i++)
		{
			//lecture des instructions
		}
		for(unsigned int i = 0;i<datasize;i++)
		{
			//lecture des donnees
		}

		//initialisation de la machine .
		close(fd);//fermeture du fichier .
	}
}


//kékecé un dump? *epic flemme*
void dump_memory(Machine *pmach)
{
		//kékonfé ? ^o^
}

//PROBLEME : l'adresse de l'instruction, c'est bien i ?
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

//kékireste :tests
void print_data(Machine *pmach)
{
printf("*** DATA (size: %d, end = Ox%08X (%d)) ***\n",pmach->_datasize,pmach->_dataend,pmach->_dataend);
	for(unsigned int i = 0; i < pmach->_datasize;i++)
	{
		Word *donnee = pmach->_data + i;
		printf("Ox%04X: Ox%08X %d\n",i,*donnee,*donnee);
	}
	printf("\n");
}

//kékireste : tests
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
		printf("R%02d: Ox%08X %d\n",i,registre,registre);
	}

}

//toupabo : dupplication de code .
void simul(Machine *pmach, bool debug)
{
	if(!debug)//si il n'y a pas de debug prévu
	{
		//tant qu'on est pas arrivé à la fin du segment d'instructions, qui est de taille _textsize
		for( unsigned int i = pmach->_pc ; pmach->_text + i < pmach->_textsize ; i++ )
		{
			Instruction *instruction = pmach->_text + pmach->_pc;//instruction courante
					//décodage puis exécution de l'instruction
			decode_execute(pmach,*instruction);
		}
	}
	else//mode debug
	{
		//tant qu'on est pas arrivé à la fin du segment d'instructions, qui est de taille _textsize
		for( unsigned int i = pmach->_pc ; pmach->_text + i < pmach->_textsize ; i++ )
		{
			if(debug_ask(pmach))
			{
				Instruction *instruction = pmach->_text + pmach->_pc;//instruction courante
				//décodage puis exécution de l'instruction
				decode_execute(pmach,*instruction);
			}
		}
	}
}