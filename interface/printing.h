#include <iostream>
#include <bitset>
#include "../core/consts.h"
#include "../core/lookup.h"
#include "../core/lexer.h"

using Lookup::history;
using Lexer::ts;
using Lexer::Kind;

void print_result(rep_type result) {
	if (abs(result) < round_off) result = 0;
	
	if (ts.current().kind != Kind::last) history.push_back(result);
    std::bitset<bit_num> bin_rep(result);
    std::cout << "Result: "; 
    for (int bit = bit_num - 1; bit >= 3; bit -= 4) {
        std::cout << bin_rep[bit] << bin_rep[bit - 1] << bin_rep[bit - 2] << bin_rep[bit - 3] << ' ';
    }
    std::cout << '(' << result << ')' << '\n';    // print out binary rep of answer
}

void print_prompt() {
	std::cout << "> ";
}
