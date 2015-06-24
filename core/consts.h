#pragma once

// #define DEBUG_BUILD

#ifdef DEBUG_BUILD
#	define DEBUG(x) {std::cerr << x << '\n';} 
#else
#	define DEBUG(x)
#endif

namespace Bincalc {

using rep_type = double;   // int, unsigned int, double 
constexpr unsigned int bit_num = 32;
constexpr rep_type round_off = 1e-10;

// whether to print the binary representation or not
extern bool terse;
// sometimes want to suppress printing such as after a modifying function call
extern bool suppress_print;
}