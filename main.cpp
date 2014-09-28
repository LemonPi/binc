#include "consts.h" // redundant, included in each separate header
#include "parser.h"
#include "lexer.h"
#include "error.h"
#include "table.h"
#include <sstream>
#include <bitset>

using namespace Lexer;
using Parser::expr;
using Table::table;

namespace Driver {
    void calculate() {
		ts.set_input(cin);
        while (true) {
            ts.get();
            if (ts.current().kind == Kind::end) break;
            if (ts.current().kind == Kind::print) continue;
            rep_type result = expr(false);
            bitset<bit_num> bin_rep(result);
            cout << "Result: " << bin_rep << '(' << result << ')' << '\n';    // print out binary rep of answer
        }
    }
	

}

int main(int argc, char* argv[]) {
    switch (argc) {
        case 1:
            break;
        case 2:
            ts.set_input(new istringstream{argv[1]});
            break;
        default:
            Error::error("too many arguments");
            return 1;
    }
    // predefined names
    table["pi"] = 3.1415926536897932385;
    table["e"] = 2.7182818284590452354;

    Driver::calculate();
    return Error::no_of_errors;
}
