#include <stdio.h>
#include "error.h"

void warning(Warning warn, unsigned addr)
{
	printf("WARNING: ");
	if (warn == WARN_HALT)
	{
		printf("HALT reached at address 0x%x\n",addr);
	}
}

void error(Error err, unsigned addr)
{
	printf("Error: ");
	switch(err){
		case ERR_UNKNOWN: 
			printf("Unknowed instruction at address 0x%x\n",addr); 
			exit(1);
    	case ERR_ILLEGAL:
    		printf("Illegal instruction at address 0x%x\n",addr);	
    		exit(1);
    	case ERR_CONDITION:
    		printf("Illegal condition at address 0x%x\n",addr);
    		exit(1);
    	case ERR_IMMEDIATE:	
    		printf("Immediate value forbidden at address 0x%x\n",addr); 
    		exit(1);
    	case ERR_SEGTEXT:
    		printf("Segmentation fault in text at address 0x%x\n",addr);
    		exit(1);	
    	case ERR_SEGDATA: 
    		printf("Segmentation fault in data at address 0x%x\n",addr);	
    		exit(1);
    	case ERR_SEGSTACK: 
    		printf("Segmentation fault in stack at address 0x%x\n",addr);
    		exit(1);
    	case ERR_NOERROR:
    		exit(0);
	}
}
