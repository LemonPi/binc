#include "../core/consts.h"
#include "../core/parser.h"
#include "../core/lexer.h"
#include "../core/error.h"
#include "../core/table.h"
#include <sstream>
#include <bitset>
#include "emscripten/bind.h"
using namespace emscripten;
using namespace Lexer;
using Parser::expr;
using Table::table;


string calc_str(string input) {
	ts.set_input(new istringstream(input));
	rep_type result = expr(true);
	
	bitset<bit_num> bin_rep(result);
	stringstream out;
	out << "Result: " << bin_rep << " (" << result << ")";
	return out.str();
}
EMSCRIPTEN_BINDINGS(my_module) {
	emscripten::function("calc_str", &calc_str);
}