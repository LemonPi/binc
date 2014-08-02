#include <iostream>
#include "error.h"

int Error::no_of_errors;
int Error::error(const string& s) {
    no_of_errors++;
    cerr << "error: " << s << '\n';
    return 1;
}
