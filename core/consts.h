#pragma once
#include <string>

#ifdef DEBUG_BUILD
#	define DEBUG(x) {std::cerr << x << '\n';} 
#else
#	define DEBUG(x)
#endif

namespace Bincalc {

using rep_type = double;   // int, unsigned int, double 

// number of bits to print out in verbose mode
constexpr unsigned int bit_num = 32;
// how small a number is to 0 to be considered 0
constexpr rep_type round_off = 1e-10;
// how much space to reserve for history at the start
constexpr size_t init_hist_capacity = 500;

// whether to print the binary representation or not
extern bool terse;
// sometimes want to suppress printing such as after a modifying function call
extern bool suppress_print;
// prompt message to print on newline
extern std::string prompt;

}
