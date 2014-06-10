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
    		printf("Illegal condition reached at address 0x%x\n",addr);
    		exit(1);
    	case ERR_IMMEDIATE:	
    		printf("Forbidden Immediate value reached at address 0x%x\n",addr); 
    		exit(1);
    	case ERR_SEGTEXT:
    		printf("Violation size of text segment reached at address 0x%x\n",addr);
    		exit(1);	
    	case ERR_SEGDATA: 
    		printf("Violation size of data segment reached at address 0x%x\n",addr);	
    		exit(1);
    	case ERR_SEGSTACK: 
    		printf("Violation size of stack segment at address 0x%x\n",addr);
    		exit(1);
    	case ERR_NOERROR:
    		printf("NO ERROR");
    		exit(0);
	}

}
