#include "../core/consts.h" // redundant, included in each separate header
#include "../core/parser.h"
#include "../core/lexer.h"
#include "../core/error.h"
#include "../core/lookup.h"
#include "printing.h"
#include <sstream>

namespace Bincalc {

// for command line usage, print verbose by default
bool terse = false;
// print normally
bool suppress_print = false;
std::string prompt {"> "};

void calculate() {
    ts.set_input(cin);
    print_prompt();
    while (true) {
        ts.get();
        DEBUG('[' << static_cast<char>(ts.current().kind) << ']')

        if (ts.current().kind == Kind::end) break;
        if (ts.current().kind == Kind::print) continue;
        rep_type result = expr(false);

        print_result(result);
        if (ts.current().kind == Kind::newline) print_prompt();
    }
}

// print tersely and without prompt
void calculate_pipe() {
    terse = true;
    while (true) {
        ts.get();
        if (ts.current().kind == Kind::end) break;
        if (ts.current().kind == Kind::print) continue;
        rep_type result = expr(false);
        print_result(result);
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
    bc::history.reserve(bc::init_hist_capacity);

    switch (argc) {
        case 1:
            bc::calculate();
            break;
        default:
            std::stringstream str_stream; 
            for (int arg = 1; arg < argc; ++arg) str_stream << argv[arg];

            bc::ts.set_input(str_stream);
            bc::calculate_pipe();
    }


    return bc::no_of_errors;
}
