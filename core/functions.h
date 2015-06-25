#include "consts.h"
#include "lookup.h"
#include "lexer.h"
#include <cstdlib>
#include <iostream>

namespace Bincalc {

// unaries ------------------
rep_type generate_random(rep_type max) {
	return rand() % ((long long) max + 1);
}



// modifiers ----------------
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

// information printing
void print_history() {
	for (const rep_type& val : history)
		std::cout << val << '\n';
}
void print_unaries() {
	for (const auto& unary : unary_funcs)
		std::cout << unary.first << '\n';
}
void print_modifiers() {
	for (const auto& modifier : modifier_funcs)
		std::cout << modifier.first << '\n';
}


} // end namespace bincalc
