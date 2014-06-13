#include <stdio.h>

#include "error.h"
#include "instruction.h"

const char *cop_names[] ={
    "ILLOP",
    "NOP",
    "LOAD",
    "STORE",
    "ADD",
    "SUB",
    "BRANCH",
    "CALL",
    "RET",
    "PUSH",
    "POP",
    "HALT",
};

const char *condition_names[] ={
    "NC",
    "EQ",
    "NE",
    "GT",
    "GE",
    "LT",
    "LE",
};

void print_instruction(Instruction instr, unsigned addr){
    Code_Op cop = instr.instr_generic._cop;

    if(cop > LAST_COP){
        error(ERR_UNKNOWN, addr);
    }
    printf("%s ", cop_names[cop]);

    if(cop == RET || cop == HALT || cop == NOP || cop == ILLOP){
        return;
    }
    else if(cop == BRANCH || cop == CALL){
        if(instr.instr_generic._regcond > LAST_CONDITION){
            error(ERR_CONDITION, addr);
        }
        printf("%s, ", condition_names[instr.instr_generic._regcond]);
    }

    else if(cop != PUSH && cop != POP){
        printf("R%02u, ", instr.instr_generic._regcond);
    }
    if(instr.instr_generic._immediate){
        printf("#%u", instr.instr_immediate._value);
    }
    else if(instr.instr_generic._indexed){
        printf("%d[R%02u]", instr.instr_indexed._offset, instr.instr_indexed._rindex);
    }
    else{
        printf("@0x%04x", instr.instr_absolute._address);
    }
}
