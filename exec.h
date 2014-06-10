#ifndef _EXEC_H_
#define _EXEC_H_

/*!
 * \file exec.h
 * \brief Exécution d'une instruction.
 */

#include "machine.h"

//! Effectue un ILLOP sur la machine
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return
 */
static bool illop_fonc(Machine pmach, Instruction instr);

//!	Effectue un ILLOP sur la machine
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return vrai
 */
static bool nop_fonc(Machine pmach, Instruction instr);

//!	Effectue un ILLOP sur la machine
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return
 */
static bool load_fonc(Machine pmach, Instruction instr);

//!	Effectue un ILLOP sur la machine
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return
 */
static bool store_fonc(Machine pmach, Instruction instr);

//!	Effectue un ILLOP sur la machine
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return
 */
static bool add_fonc(Machine pmach, Instruction instr);

//!	Effectue un ILLOP sur la machine
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return
 */
static bool sub_fonc(Machine pmach, Instruction instr);

//!	Effectue un ILLOP sur la machine
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return
 */
static bool branch_fonc(Machine pmach, Instruction instr);

//!	Effectue un ILLOP sur la machine
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return
 */
static bool call_fonc(Machine pmach, Instruction instr);

//!	Effectue un ILLOP sur la machine
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return
 */
static bool ret_fonc(Machine pmach, Instruction instr);

//!	Effectue un ILLOP sur la machine
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return
 */
static bool push_fonc(Machine pmach, Instruction instr);

//!	Effectue un ILLOP sur la machine
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return
 */
static bool pop_fonc(Machine pmach, Instruction instr);

//!	Effectue un ILLOP sur la machine
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return
 */
static bool halt_fonc(Machine pmach, Instruction instr);

//! Décodage et exécution d'une instruction
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return faux après l'exécution de \c HALT ; vrai sinon
 */
bool decode_execute(Machine *pmach, Instruction instr);

//! Trace de l'exécution
/*!
 * On écrit l'adresse et l'instruction sous forme lisible.
 *
 * \param msg le message de trace
 * \param pmach la machine en cours d'exécution
 * \param instr l'instruction à exécuter
 * \param addr son adresse
 */
void trace(const char *msg, Machine *pmach, Instruction instr, unsigned addr);

#endif