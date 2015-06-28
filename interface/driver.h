#include <iostream>
#include <bitset>
#include <cmath>    // abs
#include "../core/consts.h"
#include "../core/lookup.h"
#include "../core/lexer.h"


namespace Bincalc {

void print_result(rep_type result) {
    // suppress should only take affect for one result
    if (suppress_print) {suppress_print = false; return;}

    if (std::abs(result) < round_off) result = 0;
    // need to query previous token since parsing eats the next token
    if (ts.previous().kind != Kind::last) history.push_back(result);

    // skip binary representation
    if (terse) {
        if (os.flags() & std::ios::dec) os << result << '\n'; 
        else os << (long long) result << '\n';
        return;
    }


    std::bitset<bit_num> bin_rep(result);
    for (int bit = bit_num - 1; bit >= 3; bit -= 4) {
        os << bin_rep[bit] << bin_rep[bit - 1] << bin_rep[bit - 2] << bin_rep[bit - 3] << ' ';
    }

    if (os.flags() & std::ios::dec) os << '(' << result << ')' << '\n';    // normal print for decimals
    else os << '(' << (long long) result << ')' << '\n';  // need to cast to integral form for hex and oct printing
}

void print_prompt() {
    os << prompt;
}

void calculate() {
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


}   // end namespace Bincalc
