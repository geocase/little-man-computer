#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stringbuffer.h"

StringBuffer_t
stringBufferNew() {
	StringBuffer_t sb;
	sb.data = NULL;
	sb.size = 0;
	return sb;
}

void
stringBufferAppend(StringBuffer_t* buffer, char c) {
	buffer->data = realloc(buffer->data, sizeof(char) * (buffer->size + 2));
	buffer->data[buffer->size] = c;
	buffer->size += 1;
	buffer->data[buffer->size] = '\0';
}

StringBuffer_t
readFileToStringBuffer(const char* path) {
	size_t file_size;
	StringBuffer_t buffer = stringBufferNew();
	FILE* f               = fopen(path, "rb");
	fseek(f, 0, SEEK_END);
	file_size   = ftell(f);
	buffer.data = malloc(file_size + 1);
	rewind(f);
	fread(buffer.data, sizeof(char), file_size, f);
	buffer.data[file_size] = '\0';
	fclose(f);

	buffer.size = file_size;

	return buffer;
}

void
stringBufferSet(StringBuffer_t* buff, const char* str) {
	if(buff->data != NULL) {
		free(buff->data);
	}
	buff->size = strlen(str) + 1;
	buff->data = malloc(sizeof(char) * buff->size);
	memcpy(buff->data, str, buff->size);
	buff->data[buff->size] = '\0';
}