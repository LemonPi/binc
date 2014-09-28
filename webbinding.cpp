#include "consts.h"
#include "parser.h"
#include "lexer.h"
#include "error.h"
#include "table.h"
#include <sstream>
#include <bitset>
#include "emscripten/bind.h"
using namespace emscripten;
using namespace Lexer;
using Parser::expr;
using Table::table;

string calc_str(string input) {
	cout << input << endl;
	
	istringstream in(input);
	ts.set_input(in);
	rep_type result = expr(true);
	
	bitset<bit_num> bin_rep(result);
	stringstream out;
	out << "Result: " << bin_rep << " (" << result << ")";
	return out.str();
}
EMSCRIPTEN_BINDINGS(my_module) {
	emscripten::function("calc_str", &calc_str);
}