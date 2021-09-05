#ifndef LMC_LEX_H
#define LMC_LEX_H

#include "lmc.h"

typedef struct {
	size_t size;
	char* data;
} StringBuffer_t;

typedef enum {
	OPERATOR,
	VALUE,
	LABEL
} token_t;

typedef struct {
	opcode_t op;
	uint8_t value;
} Statement_t;

StringBuffer_t readFileToStringBuffer(const char* path);
Statement_t* lexStringBuffer(StringBuffer_t* buffer);
size_t getLineCountFromStringBuffer(StringBuffer_t* buffer);
#endif