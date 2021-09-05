#include <stdio.h>
#include <stdlib.h>

#include "lex.h"

StringBuffer_t
readFileToStringBuffer(const char* path) {
	size_t file_size;
	StringBuffer_t buffer;
	FILE* f = fopen(path, "rb");
	fseek(f, 0, SEEK_END);
	file_size = ftell(f);
	buffer.data = malloc(file_size + 1);
	rewind(f);
	fread(buffer.data, sizeof(char), file_size, f);
	buffer.data[file_size] = '\0';
	fclose(f);

	buffer.size = file_size;

	return buffer;
}

Statement_t*
lexStringBuffer(StringBuffer_t* buffer) {
	printf("%s\n", buffer->data);
	printf("%zd\n", getLineCountFromStringBuffer(buffer));
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
