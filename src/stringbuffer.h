#ifndef LMC_STRINGBUFFER_H
#define LMC_STRINGBUFFER_H
typedef struct {
	size_t size;
	char* data;
} StringBuffer_t;

StringBuffer_t stringBufferNew();
void stringBufferAppend(StringBuffer_t* buffer, char c);
StringBuffer_t readFileToStringBuffer(const char* path);
void stringBufferSet(StringBuffer_t* buff, const char* str);

#endif // LMC_STRINGBUFFER_H
