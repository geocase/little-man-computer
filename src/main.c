#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "lex.h"
#include "lmc.h"
uint16_t*
loadProgramFromFile(const char* path) {
	uint16_t mail[100];
	FILE* f = fopen(path, "rb");
	rewind(f);
	fread(mail, sizeof(uint16_t), 100, f);
	return mail;
}

int
main() {
	//	struct LMC comp = initLMC();

	//	uint16_t* buffer = loadProgramFromFile("countdown.lmp");
	//	memcpy(comp.mailboxes, buffer, sizeof(uint16_t) * 100);

	//	for(int i = 0; i < 100; ++i) {
	//		Instruction_t ins = decodeMailboxValue(comp.mailboxes[i]);
	//		printf(
	//		    "%s, %d (%d)\n",
	//		    opcodeToString(ins.op),
	//		    ins.value,
	//		    comp.mailboxes[i]);
	//	}
	//
	//	while(comp.pc < 100 && !(stepLMC(&comp))) {}
	StringBuffer_t prog = readFileToStringBuffer("test.lma");

	lexStringBuffer(&prog);
	getchar();
	free(prog.data);
}