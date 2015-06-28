#include "../core/consts.h"
#include "../core/parser.h"
#include "../core/lexer.h"
#include "../core/error.h"
#include "../core/lookup.h"
#include "driver.h"
#include <sstream>
#include "emscripten/bind.h"
using namespace emscripten;
using namespace Bincalc;


namespace Bincalc {
bool terse = false;
bool suppress_print = false;
std::string prompt {"> "};
}


std::string calc_str(std::string input) {
	ts.set_input(new istringstream(input));
	ostringstream out = std::ostringstream {};
	rep_type result = expr(true);
	
	print_result(result, out);
	if (ts.current().kind == Kind::newline) print_prompt(out);
	return out.str();
}

EMSCRIPTEN_BINDINGS(my_module) {
	emscripten::function("calc_str", &calc_str);
}