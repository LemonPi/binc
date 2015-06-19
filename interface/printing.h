#include <iostream>
#include <bitset>
#include "../core/consts.h"

void print_result(rep_type result) {
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
