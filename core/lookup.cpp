#include <cmath>
#include <iostream>
#include "lookup.h"
#include "functions.h"

namespace Bincalc {

using namespace std;

vector<rep_type> history;

// predefined values
unordered_map<string, rep_type> table {
	{"pi", 3.14159265358979323846},
	{"e", 2.71828182845904523536}
};

unordered_map<string, Unary_func> unary_funcs {
	{"abs", abs},
	{"ceil", ceil},
	{"floor", floor},
	{"trunc", trunc},
	{"round", round},

	// trig functions
	{"cos", cos},
	{"sin", sin},
	{"tan", tan},
	{"acos", acos},
	{"asin", asin},
	{"atan", atan},

	// hyperbolic trig
	{"cosh", cosh},
	{"sinh", sinh},
	{"tanh", tanh},
	{"acosh", acosh},
	{"asinh", asinh},
	{"atanh", atanh},

	// logarithms and exponential
	{"log", log},	// natural
	{"log10", log10},
	{"log2", log2},
	{"exp", exp},
	{"exp2", exp2},

	// root functions
	{"sqrt", sqrt},
	{"cbrt", cbrt}

};


// Num_formatter numeric_format = std::dec;
unordered_map<string, Modifier_func> modifier_funcs {
	{"exit", binc_exit},
	{"quit", binc_exit},
	{"hex", print_hex},
	{"oct", print_oct},
	{"dec", print_dec}
};


}	// end namespace Bincalc