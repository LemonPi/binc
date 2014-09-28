#include "parser_impl.h"
#include "table.h"

using Table::table;
using namespace std;

rep_type Parser::expr(bool need_get) {    // add and subtract
    rep_type left = term(need_get);

    while (true) {
        switch (ts.current().kind) {
            case Kind::plus: left += term(true); break;
            case Kind::minus: left -= term(true); break;
            default: return left;
        }
    }
}

rep_type Parser::term (bool need_get) {   // multiply and divide
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
            case Kind::mag_neg: left = -1 * bit_term(true); break;
            default: return left;
        }
    }
}

rep_type Parser::bit_term (bool need_get) {   // bitwise operations
    rep_type left = unary_term(need_get);
    int left_int = left;  // ensure integral type used here

    while (true) {
        switch (ts.current().kind) {
            case Kind::lshift: left_int <<= static_cast<int>(unary_term(true)); left = left_int; break;
            case Kind::rshift: left_int >>= static_cast<int>(unary_term(true)); left = left_int; break;
            case Kind::band: left_int &= static_cast<int>(unary_term(true)); left = left_int; break;
            case Kind::bor: left_int |= static_cast<int>(unary_term(true)); left = left_int; break;
            case Kind::bxor: left_int ^= static_cast<int>(unary_term(true)); left = left_int; break;
            default: return left;
        }
    }
}

rep_type Parser::unary_term (bool need_get) {   // unary modification of term
    rep_type left = prim(need_get);
    int left_int = left;

    while (true) {
        switch (ts.current().kind) {
            case Kind::bneg: left_int = static_cast<int>(prim(true)); left_int = ~left_int; left = left_int; break;
            case Kind::lit: left_int = static_cast<rep_type>(prim(true)); left = left_int; break;
            default: return left;
        }
    }
}

rep_type Parser::prim(bool need_get) {
    if (need_get) ts.get(); // read next token

    switch (ts.current().kind) {
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
        case Kind::lit: case Kind::bneg: case Kind::mag_neg: return rep_type{};     // unary operators
        default: return error("primary expected");
    }
}
