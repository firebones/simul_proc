#include <stdio.h>

#include "error.h"
#include "exec.h"

//! Récupère l'adresse d'une instruction en mode absolu/indexé
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return l'adresse absolu en mode absolu, l'adresse indexée sinon
 */
static unsigned address(Machine *pmach, Instruction instr) 
{
	if (instr.instr_generic._immediate) {
		return instr.instr_immediate._value;
	}
	else if (instr.instr_generic._indexed) {
		return pmach->_registers[instr.instr_indexed._rindex]
			+ instr.instr_indexed._offset;
	}
	return instr.instr_absolute._address;
}

//! Vérifie s'il doit faire un jump ou non
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return vrai s'il doit faire un jump, faux s'il ne doit pas et rien s'il y a une erreur
 */
static bool jump_or_not(Machine *pmach, Instruction instr)
{
	if (instr.instr_generic._regcond > LAST_CONDITION) {
		error(ERR_CONDITION, pmach->_pc - 1);
	}
	switch (instr.instr_generic._regcond)
	{
		case NC:
			return true;
		case EQ:
			return pmach->_cc == CC_Z;
		case NE:
			return pmach->_cc != CC_Z;
		case GT:
			return pmach->_cc == CC_P;
		case GE:
			return pmach->_cc == CC_P || pmach->_cc == CC_Z;
		case LT:
			return pmach->_cc == CC_N;
		case LE:
			return pmach->_cc == CC_N || pmach->_cc == CC_Z;
		default:
			error(ERR_CONDITION, pmach->_pc - 1);
	}
}

//! Vérifie s'il n'y a pas d'erreur de segmentation des données
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param addr l'adressse de l'instruction
 */
 static void test_error_dataseg(Machine *pmach, unsigned addr)
 {
 	if (addr >= pmach->_datasize) {
		error(ERR_SEGDATA, pmach->_pc -1);
	}
 }

 //! Vérifie s'il n'y a pas d'erreur de segmentation de la pile
/*!
 * \param pmach la machine/programme en cours d'exécution
 */
 static void test_error_datastack(Machine *pmach)
 {
 	if (pmach->_sp < 0 || pmach->_sp >= pmach->_datasize) {
		error(ERR_SEGSTACK, pmach->_pc - 1);
	}
 }

//!	Effectue un LOAD sur la machine
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return vrai s'il n'y a pas d'erreur
 */
static bool load(Machine *pmach, Instruction instr)
{
	unsigned rc = instr.instr_generic._regcond;
	if (instr.instr_generic._immediate) {
		pmach->_registers[rc] = instr.instr_immediate._value;
	} 
	else {
		unsigned addr = address(pmach, instr);
		test_error_dataseg(pmach, addr);
		pmach->_registers[rc] = pmach->_data[addr];
	}
	if (pmach->_registers[rc] < 0) {
		pmach->_cc = CC_N;
	}
	else if (pmach->_registers[rc] == 0) {
		pmach->_cc = CC_Z;
	}
	else {
		pmach->_cc = CC_P;
	}
	return true;
}

//!	Effectue un STORE sur la machine
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return brai s'il n'y a pas d'erreur
 */
static bool store(Machine *pmach, Instruction instr)
{
	if (instr.instr_generic._immediate) {
		error(ERR_IMMEDIATE, pmach->_pc - 1);
	}
	unsigned addr = address(pmach, instr);
	test_error_dataseg(pmach, addr);
	pmach->_data[addr] = pmach->_registers[instr.instr_generic._regcond];
	return true;
}

//!	Effectue un ADD ou un SUB sur la machine
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return vrai s'il n'y a pas d'erreur
 */
static bool add_sub(Machine *pmach, Instruction instr)
{
	int sign = (instr.instr_generic._cop == ADD) ? 1 : -1;
	unsigned rc = instr.instr_generic._regcond;
	if (instr.instr_generic._immediate) {
		pmach->_registers[rc] += instr.instr_immediate._value * sign;
	} 
	else {
		unsigned addr = address(pmach, instr);
		test_error_dataseg(pmach, addr);
		pmach->_registers[rc] += pmach->_data[addr] * sign;
	}
	if (pmach->_registers[rc] < 0) {
		pmach->_cc = CC_N;
	}
	else if (pmach->_registers[rc] == 0) {
		pmach->_cc = CC_Z;
	}
	else {
		pmach->_cc = CC_P;
	}
	return true;
}

//!	Effectue un BRANCH sur la machine
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return vrai s'il n'y a pas d'erreur
 */
static bool branch(Machine *pmach, Instruction instr)
{
	if (instr.instr_generic._immediate) {
		error(ERR_IMMEDIATE, pmach->_pc - 1);
	}
	if (jump_or_not(pmach, instr)) {
		pmach->_pc = address(pmach, instr);
	}
	return true;
}

//!	Effectue un CALL sur la machine
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return vrai s'il n'y a pas d'erreur
 */
static bool call(Machine *pmach, Instruction instr)
{
	if (instr.instr_generic._immediate) {
		error(ERR_IMMEDIATE, pmach->_pc - 1);
	}
	if (jump_or_not(pmach, instr)) {
		test_error_datastack(pmach);
		pmach->_data[pmach->_sp] = pmach->_pc;
		pmach->_pc = address(pmach, instr);
		pmach->_sp--;
	}
	return true;
}

//!	Effectue un RET sur la machine
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return vrai s'il n'y a pas d'erreur
 */
static bool ret(Machine *pmach, Instruction instr)
{
	pmach->_sp++;
	test_error_datastack(pmach);
	pmach->_pc = pmach->_data[pmach->_sp];
	return true;
}

//!	Effectue un PUSH sur la machine
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return vrai s'il n'y a pas d'erreur
 */
static bool push(Machine *pmach, Instruction instr)
{
	test_error_datastack(pmach);
	if (instr.instr_generic._immediate) {
		pmach->_data[pmach->_sp] = instr.instr_immediate._value;
	}
	else {
		unsigned addr = address(pmach, instr);
		test_error_dataseg(pmach, addr);
		pmach->_data[pmach->_sp] = pmach->_data[addr];
	}
	pmach->_sp--;
	return true;
}

//!	Effectue un POP sur la machine
/*!
 * \param pmach la machine/programme en cours d'exécution
 * \param instr l'instruction à exécuter
 * \return vrai s'il n'y a pas d'erreur
 */
static bool pop(Machine *pmach, Instruction instr)
{
	pmach->_sp++;
	if (instr.instr_generic._immediate) {
		error(ERR_IMMEDIATE, pmach->_pc - 1);
	}
	test_error_datastack(pmach);
	unsigned addr = address(pmach, instr);
	test_error_dataseg(pmach, addr);
	pmach->_data[addr] = pmach->_data[pmach->_sp];
	return true;
}

bool decode_execute(Machine *pmach, Instruction instr)
{
	switch(instr.instr_generic._cop)
	{
		case ILLOP:
			error(ERR_ILLEGAL, pmach->_pc - 1);
		case NOP:
			return true;
		case LOAD:
			return load(pmach, instr);
		case STORE:
			return store(pmach, instr);
		case ADD:
		case SUB:
			return add_sub(pmach, instr);
		case BRANCH:
			return branch(pmach, instr);
		case CALL:
			return call(pmach, instr);
		case RET:
			return ret(pmach, instr);
		case PUSH:
			return push(pmach, instr);
		case POP:
			return pop(pmach, instr);
		case HALT:
			warning(WARN_HALT, pmach->_pc - 1);
			return false;
		default:
			error(ERR_UNKNOWN, pmach->_pc - 1);
	}
}

void trace(const char *msg, Machine *pmach, Instruction instr, unsigned addr)
{
	printf("TRACE : %s: 0x%04x: ", msg, addr);
	print_instruction(instr, addr);
	printf("\n");
}