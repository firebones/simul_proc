#include <stdio.h>

#include "error.h"
#include "exec.h"


//!	
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return
 */
static bool illop_fonc(Machine pmach, Instruction instr)
{
	error(ERR_ILLEGAL, pmach->_pc - 1);
}

//!	
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return
 */
static bool nop_fonc(Machine pmach, Instruction instr)
{
	return true;
}

//!	
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return
 */
static bool load_fonc(Machine pmach, Instruction instr)
{
	
}

//!	
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return
 */
static bool store_fonc(Machine pmach, Instruction instr)
{
	
}

//!	
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return
 */
static bool add_fonc(Machine pmach, Instruction instr)
{
	
}

//!	
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return
 */
static bool sub_fonc(Machine pmach, Instruction instr)
{
	
}

//!	
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return
 */
static bool branch_fonc(Machine pmach, Instruction instr)
{
	
}


//!	
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return
 */
static bool call_fonc(Machine pmach, Instruction instr)
{
	
}

//!	
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return
 */
static bool ret_fonc(Machine pmach, Instruction instr)
{
	
}

//!	
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return
 */
static bool push_fonc(Machine pmach, Instruction instr)
{
	
}

//!	
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return
 */
static bool pop_fonc(Machine pmach, Instruction instr)
{
	
}

//!	
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return
 */
static bool halt_fonc(Machine pmach, Instruction instr)
{
	
}

/*!
 * \file exec.c
 * \brief Implémentation de exec.h. Exécute une instruction.
 */

//! Décodage et exécution d'une instruction
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return faux après l'exécution de \c HALT ; vrai sinon
 */
bool decode_execute(Machine *pmach, Instruction instr)
{
	switch(instr.instr_generic._cop)
	{
		case ILLOP:
			illop_fonc(pmach, instr);
			break;
		case NOP:
			nop_fonc(pmach, instr);
			break;
		case LOAD:
			load_fonc(pmach, instr);
			break;
		case STORE:
			store_fonc(pmach, instr);
			break;
		case ADD:
			add_fonc(pmach, instr);
			break;
		case SUB:
			sub_fonc(pmach, instr);
			break;
		case BRANCH:
			branch_fonc(pmach, instr);
			break;
		case CALL:
			call_fonc(pmach, instr);
			break;
		case RET:
			ret_fonc(pmach, instr);
			break;
		case PUSH:
			push_fonc(pmach, instr);
			break;
		case POP:
			pop_fonc(pmach, instr);
			break;
		case HALT:
			halt_fonc(pmach, instr);
			break;
		default:
			error(ERR_UNKNOWN, pmach->_pc - 1);
			break;
	}
}

//! Trace de l'exécution
/*!
 * On écrit l'adresse et l'instruction sous forme lisible.
 *
 * \param msg le message de trace
 * \param pmach la machine en cours d'exécution
 * \param instr l'instruction à exécuter
 * \param addr son adresse
 */
void trace(const char *msg, Machine *pmach, Instruction instr, unsigned addr)
{
	printf("TRACE : %s: 0x%04x: ", msg, addr);
	print_instruction(instr, addr);
	printf("\n");
}