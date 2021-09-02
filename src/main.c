#include <stdio.h>
#include <stdint.h>

struct LMC {
    int16_t mailboxes[100];
    int16_t outbox;
    int16_t accumulator;
    uint8_t pc;
};

typedef enum {
    HLT = 0,
    ADD,
    SUB,
    STA,
    LDA,
    BRA,
    BRZ,
    BRP,
    INP,
    OUT
}  opcode_t;

typedef struct {
    opcode_t op;
    uint16_t value;
} Instruction_t;

uint8_t getFirstDigitOfThreeDigitNumber(uint16_t num);
Instruction_t decodeMailboxValue(uint16_t value);
struct LMC lmcInit();
void executeLMC(struct LMC* comp);

uint8_t getFirstDigitOfThreeDigitNumber(uint16_t num) {
    if(num < 100) {
        return 0;
    }
    return num / 100;
}

Instruction_t decodeMailboxValue(uint16_t value) {
    Instruction_t ins = {
            .op = getFirstDigitOfThreeDigitNumber(value),
            .value = value - (getFirstDigitOfThreeDigitNumber(value) * 100)
    };
    if(value == 901) {
        ins.op = INP;
    }
    if(value == 902) {
        ins.op = OUT;
    }
    return ins;
}

char* opcodeToString(opcode_t op) {
    switch(op) {
        case HLT:
            return "HLT";
        case ADD:
            return "ADD";
        case SUB:
            return "SUB";
        case STA:
            return "STA";
        case LDA:
            return "LDA";
        case BRA:
            return "BRA";
        case BRZ:
            return "BRZ";
        case BRP:
            return "BRP";
        case INP:
            return "INP";
        case OUT:
            return "OUT";
        default:
            exit(-1);
    }
}

struct LMC lmcInit() {
    struct LMC c = {
            .accumulator = 0,
            .outbox = 0,
            .pc = 0
    };
    for(uint8_t i = 0; i < 100; ++i) {
        c.mailboxes[i] = 0;
    }
    return c;
}

int16_t numericCode(opcode_t op, uint16_t value) {
    return op * 100 + value;
}

void executeLMC(struct LMC* comp) {
    comp->pc = 0;
    for(;comp->pc < 100; ++(comp->pc)) {
        Instruction_t current_instruction = decodeMailboxValue(comp->mailboxes[comp->pc]);
        switch(current_instruction.op) {
            case ADD:
                comp->accumulator += comp->mailboxes[current_instruction.value];
                break;
            case SUB:
                comp->accumulator -= comp->mailboxes[current_instruction.value];
                break;
            case STA:
                comp->mailboxes[current_instruction.value] = comp->accumulator;
                break;
            case LDA:
                comp->accumulator = comp->mailboxes[current_instruction.value];
                break;
            case OUT:
                comp->outbox = comp->accumulator;
                printf("%d\n", comp->outbox);
                break;
            case HLT:
            default:
                exit(0);
        }
    }
}

int main() {
    struct LMC comp = lmcInit();

    comp.mailboxes[0] = numericCode(LDA, 99);
    comp.mailboxes[1] = numericCode(SUB, 98);
    comp.mailboxes[2] = numericCode(OUT, 0);
    comp.mailboxes[3] = numericCode(SUB, 98);
    comp.mailboxes[4] = numericCode(OUT, 0);


    comp.mailboxes[98] = 2;
    comp.mailboxes[99] = 10;

    for(int i = 0; i < 100; ++i) {
        Instruction_t ins = decodeMailboxValue(comp.mailboxes[i]);
        printf("%s, %d (%d)\n", opcodeToString(ins.op), ins.value, comp.mailboxes[i]);
    }

    executeLMC(&comp);
}