#include <stdio.h>

#include "lmc.h"
#include "misc.h"
struct LMC
initLMC() {
	struct LMC c = {.accumulator = 0, .outbox = 0, .pc = 0, .negative = false};
	for(uint8_t i = 0; i < 100; ++i) {
		c.mailboxes[i] = 0;
	}
	return c;
}

bool
stepLMC(struct LMC* comp) {
	//    comp->pc = 0;
	//    printf("(pc = %d)\n", comp->pc);
	Instruction_t current_instruction =
	    decodeMailboxValue(comp->mailboxes[comp->pc]);
	switch(current_instruction.op) {
		case ADD:
			comp->accumulator += comp->mailboxes[current_instruction.value];
			comp->negative = false;
			// todo: overflow
			++(comp->pc);
			break;
		case SUB:
			if(comp->mailboxes[current_instruction.value] > comp->accumulator) {
				comp->negative = true;
			} else {
				comp->accumulator -= comp->mailboxes[current_instruction.value];
			}
			++(comp->pc);
			break;
		case STA:
			comp->mailboxes[current_instruction.value] = comp->accumulator;
			++(comp->pc);
			break;
		case LDA:
			comp->accumulator = comp->mailboxes[current_instruction.value];
			++(comp->pc);
			break;
		case BRA:
			comp->pc = current_instruction.value;
			break;
		case BRZ:
			if(comp->accumulator == 0 && !(comp->negative)) {
				comp->pc = current_instruction.value;
			} else {
				++(comp->pc);
			}
			break;
		case BRP:
			if(!(comp->negative)) {
				comp->pc = current_instruction.value;
			} else {
				++(comp->pc);
			}
			break;
		case INP:
			char input_string[6];
			printf(": ");
			gets(input_string);
			uint16_t input_num = atoi(input_string);
			comp->accumulator  = input_num;
			++(comp->pc);
			break;
		case OUT:
			comp->outbox = comp->accumulator;
			printf("%d\n", comp->outbox);
			++(comp->pc);
			break;
		case HLT:
		default:
			return true;
	}
	return false;
}

char*
opcodeToString(opcode_t op) {
	switch(op) {
		case HLT:
			return "HLT";
		case ADD:
			return "ADD";
		case SUB:
			return "SUB";
		case STA:
			return "STA";
		case LDA:
			return "LDA";
		case BRA:
			return "BRA";
		case BRZ:
			return "BRZ";
		case BRP:
			return "BRP";
		case INP:
			return "INP";
		case OUT:
			return "OUT";
		default:
			printf("err: %d\n", op);
			exit(-1);
	}
}

Instruction_t
decodeMailboxValue(uint16_t value) {
	Instruction_t ins = {
	    .op    = getFirstDigitOfThreeDigitNumber(value) * 100,
	    .value = value - (getFirstDigitOfThreeDigitNumber(value) * 100)};
	if(value == 901) {
		ins.op = INP;
	}
	if(value == 902) {
		ins.op = OUT;
	}
	return ins;
}

uint16_t
numericCode(opcode_t op, uint16_t value) {
	return op + value;
}
