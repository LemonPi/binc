#include "consts.h"
#include "lookup.h"
#include "lexer.h"
#include <cstdlib>
#include <iostream>

namespace Bincalc {

void binc_exit() {
    ts.end_stream();
	// exit(0);
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

// print information
void print_verbose() {
	terse = false;
}
void print_terse() {
	terse = true;
}
void set_prompt() {
    prompt = "> ";
}
void clear_prompt() {
    prompt = "";
}

void print_history() {
	for (const rep_type& val : history)
		std::cout << val << '\n';
}

} // end namespace bincalc
