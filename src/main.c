#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
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
	StringBuffer_t prog = readFileToStringBuffer("countdown.lma");
	uint16_t* k         = lexStringBuffer(&prog);
	free(prog.data);

	FILE* f = fopen("countdown_from_asm.lmp", "wb");
	fwrite(k, sizeof(uint16_t), 100, f);
	fclose(f);

	struct LMC comp = initLMC();

	//	uint16_t* buffer = loadProgramFromFile("countdown.lmp");
	//	memcpy(comp.mailboxes, k, sizeof(uint16_t) * 100);

	//	comp.mailboxes = loadProgramFromFile("countdown.lmp");
	uint16_t* lmp = loadProgramFromFile("countdown_from_asm.lmp");

	memcpy(comp.mailboxes, k, sizeof(uint16_t) * 100);

	printf("\n");
	for(int i = 0; i < 100; ++i) {
		Instruction_t ins = decodeMailboxValue(comp.mailboxes[i]);
		printf(
		    "%s, %d (%d)\n",
		    opcodeToString(ins.op),
		    ins.value,
		    comp.mailboxes[i]);
	}

	while(comp.pc < 100 && !(stepLMC(&comp))) {}
}
