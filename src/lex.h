#ifndef LMC_LEX_H
#define LMC_LEX_H

#include "stringbuffer.h"
#include "lmc.h"

typedef enum { NUMERA, ALPHA, OTHER } char_type_t;

typedef enum { OPERATOR, VALUE, LABEL } token_type_t;

typedef struct {
	token_type_t type;
	uint16_t value;
} token_t;

token_t stringBufferToToken(StringBuffer_t* buffer);

typedef struct {
	opcode_t op;
	uint8_t value;
} Statement_t;

uint16_t* lexStringBuffer(StringBuffer_t* buffer);
size_t getLineCountFromStringBuffer(StringBuffer_t* buffer);
#endif