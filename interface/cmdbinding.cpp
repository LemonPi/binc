#include "../core/consts.h" // redundant, included in each separate header
#include "../core/parser.h"
#include "../core/lexer.h"
#include "../core/error.h"
#include "../core/lookup.h"
#include "printing.h"
#include <sstream>

namespace Bincalc {

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

namespace bc =  Bincalc;
int main(int argc, char* argv[]) {
    switch (argc) {
        case 1:
            break;
        case 2:
            bc::ts.set_input(new std::istringstream{argv[1]});
            break;
        default:
            bc::error("too many arguments");
            return 1;
    }


    bc::calculate();
    return bc::no_of_errors;
}
