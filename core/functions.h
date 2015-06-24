#include "consts.h"
#include <cstdlib>
#include <iostream>

namespace Bincalc {

void binc_exit() {
	exit(0);
}

// numeric base format flag
void print_hex() {
	std::cout << std::hex;
}
void print_oct() {
	std::cout << std::oct;
}
void print_dec() {
	std::cout << std::dec;
}

} // end namespace bincalc