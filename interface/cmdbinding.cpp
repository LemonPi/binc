#include "../core/consts.h" // redundant, included in each separate header
#include "../core/parser.h"
#include "../core/lexer.h"
#include "../core/error.h"
#include "../core/table.h"
#include "printing.h"
#include <sstream>

using namespace Lexer;
using Parser::expr;
using Table::table;

namespace Driver {


void calculate() {
    ts.set_input(cin);
    print_prompt();
    while (true) {
        ts.get();
        if (ts.current().kind == Kind::end) break;
        if (ts.current().kind == Kind::print) continue;
        rep_type result = expr(false);
        // want to display with space between every 4 characters
        print_result(result);
        print_prompt();
    }
}

void calc_str(string s) {
    ts.set_input(new istringstream(s));
    rep_type result = expr(true);
    print_result(result);
    print_prompt();
}

void calc_str_loop() {
    print_prompt();
    while (true) {
        string s;
        getline(cin, s);
        calc_str(s);
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
