#include <cmath>
#include "parser_impl.h"
#include "table.h"

using Table::table;
using Table::history;

namespace Parser {

using namespace std;
rep_type expr(bool need_get) {    // add and subtract
    rep_type left = term(need_get);

    while (true) {
        switch (ts.current().kind) {
            case Kind::plus: left += term(true); break;
            case Kind::minus: left -= term(true); break;
            default: return left;
        }
    }
}

rep_type term (bool need_get) {   // multiply and divide
    rep_type left = bit_term(need_get);

    while (true) {
        switch (ts.current().kind) {
            case Kind::mul: left *= bit_term(true); break;
            case Kind::div: 
                if (auto d = bit_term(true)) {  // not dividing by 0
                    left /= d;
                    break;
                }
                return error("divide by 0");
            case Kind::mod:
                if (int base = static_cast<int>(bit_term(true))) {
                    left = static_cast<int>(left) % base;
                    break;
                }
                return error("modulo by 0");
            case Kind::pow: left = pow(left, bit_term(true)); break;
            default: return left;
        }
    }
}

rep_type bit_term (bool need_get) {   // bitwise operations
    rep_type left = unary_term(need_get);
    int left_int = left;  // ensure integral type used here

    while (true) {
        switch (ts.current().kind) {
            case Kind::lshift: left_int <<= static_cast<int>(unary_term(true)); left = left_int; break;
            case Kind::rshift: left_int >>= static_cast<int>(unary_term(true)); left = left_int; break;
            case Kind::band: left_int &= static_cast<int>(unary_term(true)); left = left_int; break;
            case Kind::bor: left_int |= static_cast<int>(unary_term(true)); left = left_int; break;
            case Kind::bxor: left_int ^= static_cast<int>(unary_term(true)); left = left_int; break;
            case Kind::mag_neg: left = -1 * unary_term(true); break;
            default: return left;
        }
    }
}

rep_type unary_term (bool need_get) {   // unary modification of term
    rep_type left = prim(need_get);
    int left_int = left;

    while (true) {
        switch (ts.current().kind) {
            case Kind::bneg: left_int = static_cast<int>(prim(true)); left_int = ~left_int; left = left_int; break;
            case Kind::lit: left = static_cast<rep_type>(prim(true)); break;
            // didn't call prim, so get next and return directly
            case Kind::fact: for (int i = left_int - 1; i > 1; --i) left *= i; ts.get(); 
            default: return left;
        }
    }
}

rep_type prim(bool need_get) {
    if (need_get) ts.get(); // read next token

    switch (ts.current().kind) {
        case Kind::fact:    // expects number to be stored 
        case Kind::number: {
            rep_type val = ts.current().number_val;
            ts.get();
            return val;
        }
        case Kind::name: {
            rep_type& val = table[ts.current().string_val];  // find corresponding val in table
            if (ts.get().kind == Kind::assign) val = expr(true);   // assigning to name
            return val;
        }
        case Kind::lp: {
            auto e = expr(true); // incoming expression
            // after reading in an ( expression ' ' <-- expecting rp
            if (ts.current().kind != Kind::rp) return error("')' expected");
            ts.get();    // eat ')'
            return e;
        }
        case Kind::lit: case Kind::bneg: case Kind::mag_neg: case Kind::pow:
            return rep_type{};     // unary operators
        case Kind::last: 
            if (ts.current().number_val <= history.size()) return history[history.size() - ts.current().number_val];
            else return error("looking past history's content");
        default: return error("primary expected");
    }
}

}   // end namespace Parser