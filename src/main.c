#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "lmc.h"

uint8_t getFirstDigitOfThreeDigitNumber(uint16_t num);

uint8_t
getFirstDigitOfThreeDigitNumber(uint16_t num) {
	if(num < 100) {
		return 0;
	}
	return num / 100;
}

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
	struct LMC comp = initLMC();

	uint16_t* buffer = loadProgramFromFile("countdown.lmp");
	memcpy(comp.mailboxes, buffer, sizeof(uint16_t) * 100);

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