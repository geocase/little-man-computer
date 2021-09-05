#ifndef LMC_H
#define LMC_H

#include <stdbool.h>
#include <stdint.h>

struct LMC {
	uint16_t mailboxes[100];
	uint16_t outbox;
	uint16_t accumulator;
	uint8_t pc;
	bool negative;
};

bool stepLMC(struct LMC* comp);

struct LMC initLMC();

typedef enum {
	HLT = 0,
	ADD = 100,
	SUB = 200,
	STA = 300,
	LDA = 500,
	BRA = 600,
	BRZ = 700,
	BRP = 800,
	INP = 901,
	OUT = 902
} opcode_t;

char* opcodeToString(opcode_t op);

typedef struct {
	opcode_t op;
	uint16_t value;
} Instruction_t;

Instruction_t decodeMailboxValue(uint16_t value);

uint16_t numericCode(opcode_t op, uint16_t value);

#endif