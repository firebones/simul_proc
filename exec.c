#include <stdio.h>

#include "error.h"
#include "exec.h"


//! Effectue un ILLOP sur la machine
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return
 */
static bool illop_fonc(Machine pmach, Instruction instr)
{
	error(ERR_ILLEGAL, pmach->_pc - 1);
}

//!	Effectue un ILLOP sur la machine
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return
 */
static bool nop_fonc(Machine pmach, Instruction instr)
{
	return true;
}

//!	Effectue un ILLOP sur la machine
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return
 */
static bool load_fonc(Machine pmach, Instruction instr)
{
	
}

//!	Effectue un ILLOP sur la machine
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return
 */
static bool store_fonc(Machine pmach, Instruction instr)
{
	
}

//!	Effectue un ILLOP sur la machine
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return
 */
static bool add_fonc(Machine pmach, Instruction instr)
{
	
}

//!	Effectue un ILLOP sur la machine
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return
 */
static bool sub_fonc(Machine pmach, Instruction instr)
{
	
}

//!	Effectue un ILLOP sur la machine
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return
 */
static bool branch_fonc(Machine pmach, Instruction instr)
{
	
}


//!	Effectue un ILLOP sur la machine
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return
 */
static bool call_fonc(Machine pmach, Instruction instr)
{
	
}

//!	Effectue un ILLOP sur la machine
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return
 */
static bool ret_fonc(Machine pmach, Instruction instr)
{
	
}

//!	Effectue un ILLOP sur la machine
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return
 */
static bool push_fonc(Machine pmach, Instruction instr)
{
	
}

//!	Effectue un ILLOP sur la machine
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return
 */
static bool pop_fonc(Machine pmach, Instruction instr)
{
	
}

//!	Effectue un ILLOP sur la machine
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
			return illop_fonc(pmach, instr);
		case NOP:
			return nop_fonc(pmach, instr);
		case LOAD:
			return load_fonc(pmach, instr);
		case STORE:
			return store_fonc(pmach, instr);
		case ADD:
			return add_fonc(pmach, instr);
		case SUB:
			return sub_fonc(pmach, instr);
		case BRANCH:
			return branch_fonc(pmach, instr);
		case CALL:
			return call_fonc(pmach, instr);
		case RET:
			return ret_fonc(pmach, instr);
		case PUSH:
			return push_fonc(pmach, instr);
		case POP:
			return pop_fonc(pmach, instr);
		case HALT:
			return halt_fonc(pmach, instr);
		default:
			error(ERR_UNKNOWN, pmach->_pc - 1);
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