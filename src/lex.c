#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lex.h"
#include "stringbuffer.h"

char_type_t
getCharTypeOfChar(char c) {
	switch(c) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			return NUMERA;
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
			return ALPHA;
		default:
			return OTHER;
	}
	return OTHER;
}

token_t
stringBufferToToken(StringBuffer_t* buffer) {
	token_t t;
	if(buffer->size <= 0) {
		exit(-1);
	}
	StringBuffer_t op_strings[11];
	for(int i = 0; i < 11; ++i) {
		op_strings[i] = stringBufferNew();
	}
	stringBufferSet(&(op_strings[0]), "HLT");
	stringBufferSet(&(op_strings[1]), "ADD");
	stringBufferSet(&(op_strings[2]), "SUB");
	stringBufferSet(&(op_strings[3]), "STA");
	stringBufferSet(&(op_strings[4]), "LDA");
	stringBufferSet(&(op_strings[5]), "BRA");
	stringBufferSet(&(op_strings[6]), "BRZ");
	stringBufferSet(&(op_strings[7]), "BRP");
	stringBufferSet(&(op_strings[8]), "INP");
	stringBufferSet(&(op_strings[9]), "OUT");
	stringBufferSet(&(op_strings[10]), "DAT");

	opcode_t op_values[11] = {
	    HLT, ADD, SUB, STA, LDA, BRA, BRZ, BRP, INP, OUT, DAT};

	switch(getCharTypeOfChar(buffer->data[0])) {
		case NUMERA:
			t.type  = VALUE;
			t.value = atoi(buffer->data);
			break;
		case ALPHA:
			t.type   = OPERATOR;
			int iter = 0;
			while(iter < 11) {
				if(strcmp(buffer->data, op_strings[iter].data) == 0) {
					t.value = op_values[iter];
					break;
				}
				iter++;
			};
			break;
		case OTHER:
			exit(-1);
	}
	return t;
}

uint16_t*
lexStringBuffer(StringBuffer_t* buffer) {
	// todo: cleanup
	StringBuffer_t token_buffer[300];
	uint16_t token_buffer_index = 0;
	bool in_word                = false;
	for(uint16_t bi = 0; bi < 300; ++bi) {
		token_buffer[bi] = stringBufferNew();
	}

	for(size_t i = 0; i < buffer->size; ++i) {
		char curr = buffer->data[i];
		if(curr == '\n') {
			continue;
		}
		if(curr == ' ' || curr == '\t') {
			if(in_word) {
				token_buffer_index++;
			}
			in_word = false;
			continue;
		} else {
			stringBufferAppend(&(token_buffer[token_buffer_index]), curr);
			in_word = true;
		}
	}

	token_buffer_index++;
	token_t* tokens = malloc(sizeof(token_t) * token_buffer_index);
	for(int i = 0; i < token_buffer_index; ++i) {
		printf("(%s) ", token_buffer[i].data);
		tokens[i] = stringBufferToToken(&(token_buffer[i]));
		printf("[%d] ", tokens[i].value);
	}
	uint16_t* codes = malloc(sizeof(uint16_t) * 100);
	for(int i = 0; i < 100; ++i) {
		codes[i] = 0;
	}

	int index = 0;
	for(int k = 0; k < token_buffer_index; k += 2) {
		codes[index] = numericCode(tokens[k].value, tokens[k + 1].value);
		if(tokens[k].value == 1001) {
			codes[index] = tokens[k + 1].value;
		}
		index += 1;
	}

	return codes;
}

size_t
getLineCountFromStringBuffer(StringBuffer_t* buffer) {
	size_t count = 0;
	for(size_t i = 0; i < buffer->size; ++i) {
		if(buffer->data[i] == '\n') {
			++count;
		}
	}
	return count;
}
