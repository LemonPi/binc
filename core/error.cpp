#include <iostream>
#include "error.h"

namespace Bincalc {

int no_of_errors {};
int error(const std::string& s) {
    no_of_errors++;
    std::cerr << "error: " << s << '\n';
    return 1;
}

}
