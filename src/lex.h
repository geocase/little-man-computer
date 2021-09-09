#ifndef LMC_LEX_H
#define LMC_LEX_H

#include "lmc.h"

typedef struct {
	size_t size;
	char* data;
} StringBuffer_t;

StringBuffer_t stringBufferNew();
void stringBufferAppend(StringBuffer_t* buffer, char c);
StringBuffer_t readFileToStringBuffer(const char* path);
void stringBufferSet(StringBuffer_t* buff, const char* str);

typedef enum {
	NUMERA,
	ALPHA,
	OTHER
} char_type_t;

typedef enum {
	OPERATOR,
	VALUE,
	LABEL
} token_type_t;

typedef struct {
	token_type_t type;
	uint16_t value;
} token_t;

token_t stringBufferToToken(StringBuffer_t* buffer);

typedef struct {
	opcode_t op;
	uint8_t value;
} Statement_t;

Statement_t* lexStringBuffer(StringBuffer_t* buffer);
size_t getLineCountFromStringBuffer(StringBuffer_t* buffer);
#endif