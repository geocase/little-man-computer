#include <stdint.h>

#include "misc.h"

uint8_t
getFirstDigitOfThreeDigitNumber(uint16_t num) {
	if(num < 100) {
		return 0;
	}
	return num / 100;
}