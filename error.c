#include <stdio.h>
#include "error.h"

/*!
 * \file error.c
 * \brief Messages et codes d'erreurs.
 */

void warning(Warning warn, unsigned addr)
{
	fprintf(stdout,"WARNING: ");
	if (warn == WARN_HALT)
	{
		fprintf(stdout,"HALT reached at address 0x%x\n",addr);
    }
}

void error(Error err, unsigned addr)
{
	fprintf(stderr,"Error: ");
	switch(err){
		case ERR_UNKNOWN:      //!< Imprimer erreur d'instruction inconnue
			fprintf(stderr,"Unknowed instruction at address 0x%x\n",addr); 
			exit(1);
    	case ERR_ILLEGAL:      //!< Imprimer erreur d'instruction illégale
    		fprintf(stderr,"Illegal instruction at address 0x%x\n",addr);	
    		exit(1);
    	case ERR_CONDITION:    //!< Imprimer erreur d'condition illégale
    		fprintf(stderr,"Illegal condition at address 0x%x\n",addr);
    		exit(1);
    	case ERR_IMMEDIATE:	   //!< Imprimer erreur d'valeur immédiate interdite
    		fprintf(stderr,"Immediate value forbidden at address 0x%x\n",addr); 
    		exit(1);
    	case ERR_SEGTEXT:      //!< Imprimer erreur d'violation de taille du segment de texte
    		fprintf(stderr,"Segmentation fault in text at address 0x%x\n",addr);
    		exit(1);	
    	case ERR_SEGDATA:      //!< Imprimer erreur d'violation de taille du segment de données
    		fprintf(stderr,"Segmentation fault in data at address 0x%x\n",addr);	
    		exit(1);
    	case ERR_SEGSTACK:     //!< Imprimer erreur d'violation de taille du segment de pile
    		fprintf(stderr,"Segmentation fault in stack at address 0x%x\n",addr);
    		exit(1);
    	case ERR_NOERROR:      //!< Pas d'erreur
    		exit(0);
        default:
            exit(0);
	}
}
