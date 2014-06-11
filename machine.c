#include "machine.h"
#include "exec.h"//possible?
#include "debug.h"//possible?
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
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

void read_program(Machine *pmach, const char *programfile)
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

		Instruction text[textsize];
		Word data[datasize];

		for(unsigned int i = 0;i<textsize;i++)
		{
			Instruction instruction;
			read(fd,&instruction,32);
			text[i] = instruction;
		}

		for(unsigned int i = 0;i<datasize;i++)
		{
			Word donnee;
			read(fd,&donnee,32);
			data[i] = donnee;
		}

		//initialisation de la machine .
		load_program(pmach,textsize,text,datasize,data,dataend);
		close(fd);//fermeture du fichier .
	}
}


 

void dump_memory(Machine *pmach)
{
	printf("*** Sauvegarde des programmes et données initiales en format binaire ***\n\n");
	printf("Instruction text[] = {\n");
	//boucle pour récupérer les instructions
	for(unsigned int i = 0; i < pmach->_textsize;i++)
	{
		Instruction *instruction = pmach->_text + i;
		printf("0x%08X, ",instruction->_raw);
	}
	printf("\n};\n");
	printf("unsigned textsize = %d;\n\n",pmach->_textsize);
	printf("Word data[] = {\n");
	//boucle pour récupérer les donnees
	for(unsigned int i = 0; i <pmach->_datasize;i++){
		Word *donnee = pmach->_data + i;
		printf("0x%08X, ",*donnee);
	}
	printf("};\n");
	printf("unsigned datasize = %d\n;",pmach->_datasize);
	printf("unsigned dataend = %d\n;",pmach->_dataend);
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