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
	{"ln", log},	// natural
	{"log", log10},
	{"lg", log2},	// base 2
	{"exp", exp},
	{"exp2", exp2},

	// root functions
	{"sqrt", sqrt},
	{"cbrt", cbrt}

};


unordered_map<string, Modifier_func> modifier_funcs {
	{"exit", binc_exit},
	{"quit", binc_exit},
	// numeric formatting
	{"hex", print_hex},
	{"oct", print_oct},
	{"dec", print_dec},
	// print modes
	{"terse", print_terse},
	{"verbose", print_verbose},

	{"hist", print_history},
	{"history", print_history}
};


}	// end namespace Bincalc