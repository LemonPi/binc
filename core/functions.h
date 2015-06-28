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
	os << std::hex;
}
void print_oct() {
	os << std::oct;
}
void print_dec() {
	os << std::dec;
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
		os << val << '\n';
}
void print_unaries() {
	for (const auto& unary : unary_funcs)
		os << unary.first << '\n';
}
void print_modifiers() {
	for (const auto& modifier : modifier_funcs)
		os << modifier.first << '\n';
}


} // end namespace bincalc
