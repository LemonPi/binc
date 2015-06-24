#include <iostream>
#include <bitset>
#include <cmath>    // abs
#include "../core/consts.h"
#include "../core/lookup.h"
#include "../core/lexer.h"


namespace Bincalc {

using std::cout;

void print_result(rep_type result) {
    // suppress should only take affect for one result
    if (suppress_print) {suppress_print = false; return;}

    if (std::abs(result) < round_off) result = 0;
    // need to query previous token since parsing eats the next token
    if (ts.previous().kind != Kind::last) history.push_back(result);

    // skip binary representation
    if (terse) {
        if (cout.flags() & std::ios::dec) cout << result << '\n'; 
        else cout << (long long) result << '\n';
        return;
    }


    std::bitset<bit_num> bin_rep(result);
    for (int bit = bit_num - 1; bit >= 3; bit -= 4) {
        cout << bin_rep[bit] << bin_rep[bit - 1] << bin_rep[bit - 2] << bin_rep[bit - 3] << ' ';
    }

    if (cout.flags() & std::ios::dec) cout << '(' << result << ')' << '\n';    // normal print for decimals
    else cout << '(' << (long long) result << ')' << '\n';  // need to cast to integral form for hex and oct printing
}

void print_prompt() {
    cout << prompt;
}


}   // end namespace Bincalc
