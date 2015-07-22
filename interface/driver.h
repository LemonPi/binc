#include <iostream>
#include <bitset>
#include <cmath>    // abs
#include "../core/consts.h"
#include "../core/lookup.h"
#include "../core/lexer.h"


namespace Bincalc {

void print_result(rep_type result, std::ostream& out = os) {
    // suppress should only take affect for one result
    if (suppress_print) {suppress_print = false; return;}

    if (std::abs(result) < round_off) result = 0;
    // add to history if the previous statement wasn't a pure query
    if (!ts.pure_query_expr()) history.push_back(result);

    // skip binary representation
    if (terse) {
        if (out.flags() & std::ios::dec) out << result << '\n'; 
        else out << (long long) result << '\n';
        return;
    }


    std::bitset<bit_num> bin_rep(result);
    for (int bit = bit_num - 1; bit >= 3; bit -= 4) {
        out << bin_rep[bit] << bin_rep[bit - 1] << bin_rep[bit - 2] << bin_rep[bit - 3] << ' ';
    }

    if (out.flags() & std::ios::dec) out << '(' << result << ')' << '\n';    // normal print for decimals
    else out << '(' << (long long) result << ')' << '\n';  // need to cast to integral form for hex and oct printing
}

void print_prompt(std::ostream& out = os) {
    out << prompt;
}

void calculate() {
    print_prompt();
    while (true) {
        // ts.get();
        rep_type result = expr(true);

        if (ts.current().kind == Kind::end) break;
        print_result(result);
        if (ts.current().kind == Kind::print) continue;

        if (ts.current().kind == Kind::newline) print_prompt();
    }
}

// print tersely and without prompt
void calculate_pipe() {
    terse = true;
    while (true) {
        if (ts.current().kind == Kind::end) break;
        rep_type result = expr(false);
        print_result(result);
    }
}


}   // end namespace Bincalc
