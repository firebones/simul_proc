#include <stdio.h>
#include "error.h"

void warning(Warning warn, unsigned addr)
{
<<<<<<< HEAD
	fprintf(stdout,"WARNING: ");
	if (warn == WARN_HALT)
	{
		fprintf(stdout,"HALT reached at address 0x%x\n",addr);
=======
	fprintf(stderr,"WARNING: ");
	if (warn == WARN_HALT)
	{
		fprintf(stderr,"HALT reached at address 0x%x\n",addr);
>>>>>>> dc4be0f92b4824629413eff34ec95039394603dd
	}
}

void error(Error err, unsigned addr)
{
	fprintf(stderr,"Error: ");
	switch(err){
		case ERR_UNKNOWN: 
			fprintf(stderr,"Unknowed instruction at address 0x%x\n",addr); 
			exit(1);
    	case ERR_ILLEGAL:
    		fprintf(stderr,"Illegal instruction at address 0x%x\n",addr);	
    		exit(1);
    	case ERR_CONDITION:
    		fprintf(stderr,"Illegal condition at address 0x%x\n",addr);
    		exit(1);
    	case ERR_IMMEDIATE:	
    		fprintf(stderr,"Immediate value forbidden at address 0x%x\n",addr); 
    		exit(1);
    	case ERR_SEGTEXT:
    		fprintf(stderr,"Segmentation fault in text at address 0x%x\n",addr);
    		exit(1);	
    	case ERR_SEGDATA: 
    		fprintf(stderr,"Segmentation fault in data at address 0x%x\n",addr);	
    		exit(1);
    	case ERR_SEGSTACK: 
    		fprintf(stderr,"Segmentation fault in stack at address 0x%x\n",addr);
    		exit(1);
    	case ERR_NOERROR:
    		exit(0);
        default:
            exit(0);
	}
}
