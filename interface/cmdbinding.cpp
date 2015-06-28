#include "../core/consts.h" // redundant, included in each separate header
#include "../core/parser.h"
#include "../core/lexer.h"
#include "../core/error.h"
#include "../core/lookup.h"
#include "driver.h"
#include <sstream>

namespace Bincalc {

// for command line usage, print verbose by default
bool terse = false;
// print normally
bool suppress_print = false;
std::string prompt {"> "};

}

namespace bc =  Bincalc;
int main(int argc, char* argv[]) {
    bc::history.reserve(bc::init_hist_capacity);

    switch (argc) {
        case 1:
            bc::ts.set_input(std::cin);
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
