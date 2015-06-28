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




namespace bc = Bincalc;

bool bc::terse = false;
bool bc::suppress_print = false;
std::string bc::prompt {"> "};


std::string calc_str(std::string input) {
	bc::ts.set_input(new istringstream(input));
	ostringstream os = std::ostringstream {};
	rep_type result = expr(true);
	
	bc::print_result(result, os);
	return os.str();
}

EMSCRIPTEN_BINDINGS(my_module) {
	emscripten::function("calc_str", &calc_str);
}