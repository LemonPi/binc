// Bitwise stream calculator
// heavily influenced by Bjarne Stroustrup's desk calculator (The C++ Programming Language 4th Edition, chapter 10)
#include <iostream>
#include <bitset>
#include <stack>
#include <map>
#include <cctype>
#include <string>
#include <sstream>

#define SUCCESS 0
#define FAIL -1

using namespace std;
using rep_type = int;   // int, unsigned int, double, etc
constexpr unsigned int bit_num = 8;

// error handling ----------------------
int no_of_errors;

int error(const string& s) {
    no_of_errors++;
    cerr << "error: " << s << '\n';
    return 1;
}

// classes, structs, and enums ---------
enum class Kind : char {
    name, number, end,
    plus = '+', minus = '-', mul = '*', div = '/', print = ';', assign = '=', lp = '(', rp = ')',
    lshift = '<', rshift = '>', band = '&', bor = '|', bxor = '^', bneg = '~', lit = '\\'
};

struct Token {
    Kind kind;
    string string_val;
    rep_type number_val;
};

class Token_stream {
public:
    Token_stream(istream& instream_ref) : ip{&instream_ref}, owns{false} {}
    Token_stream(istream* instream_pt)  : ip{instream_pt}, owns{true} {}
    Token_stream() { close(); }

    Token get();    // read and return next token
    const Token& current() { return ct; } // most recently read token

    void set_input(istream& instream_ref) { close(); ip = &instream_ref; owns = false; }
    void set_input(istream* instream_pt) { close(); ip = instream_pt; owns = true; }

private:
    void close() { if (owns) delete ip; }

    istream* ip;    // input stream pointer
    bool owns;
    Token ct {Kind::end};   // current token, default value in case of misuse
};

Token Token_stream::get() {
    // read 1 char, decide what kind of token is incoming,
    // appropriately read more char then return Token
    char c = 0;

    do {  // skip all whitespace except newline
        if(!ip->get(c)) return ct = {Kind::end};  // no char can be read from ip
    } while (c != '\n' && isspace(c));

    switch (c) {
        case ';':
        case '\n':
            return ct = {Kind::print};
        case '*':
        case '/':
        case '+':
        case '-':
        case '(':
        case ')':
        case '<':
        case '>':
        case '&':
        case '|':
        case '^':
        case '~':
        case '\\':
        case '=':
            return ct = {static_cast<Kind>(c)};
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            ip->putback(c);
            *ip >> ct.number_val;
            ct.kind = Kind::number;
            return ct;
        default:    // name, name =, or error
            if (isalpha(c)) {
                if (ct.kind == Kind::lit) { // character is a literal rather than a name
                    ct.number_val = static_cast<int>(c);
                    ct.kind = Kind::number;
                    return ct;
                }
                ct.string_val = c;
                while (ip->get(c) && isalnum(c))
                    ct.string_val += c;    // append each letter of name
                ip->putback(c);     // while loop reads 1 extra char
                ct.kind = Kind::name;
                return ct;
            }
            error("bad token");
            return ct = {Kind::print};
    }
}

// symbol table ------------------------
map<string, rep_type> table;

// parsing functions -------------------
// expression hierarchy: expr -> term -> bit_term -> primary
// each parser evaluates its expression and returns the value
rep_type expr(bool);
rep_type term(bool);
rep_type bit_term(bool);
rep_type prim(bool);

// driver to start things -------------
Token_stream ts {cin};

void calculate() {
    while (true) {
        ts.get();
        if (ts.current().kind == Kind::end) break;
        if (ts.current().kind == Kind::print) continue;
        rep_type result = expr(false);
        bitset<bit_num> bin_rep(result);
        cout << "Result: " << bin_rep << '(' << result << ')' << '\n';    // print out binary rep of answer
    }
}

int main(int argc, char* argv[]) {
    switch (argc) {
        case 1:
            break;
        case 2:
            ts.set_input(new istringstream{argv[1]});
            break;
        default:
            error("too many arguments");
            return 1;
    }
    calculate();
    return no_of_errors;
}

// parser definitions ------------------

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
            default: return left;
        }
    }
}

rep_type bit_term (bool need_get) {   // bitwise operations
    rep_type left = prim(need_get);

    while (true) {
        switch (ts.current().kind) {
            case Kind::lshift: left <<= prim(true); break;
            case Kind::rshift: left >>= prim(true); break;
            case Kind::band: left &= prim(true); break;
            case Kind::bor: left |= prim(true); break;
            case Kind::bxor: left ^= prim(true); break;
            case Kind::bneg: left = prim(true); left = ~left; break;
            case Kind::lit: left = static_cast<rep_type>(prim(true)); break;
            default: return left;
        }
    }
}

rep_type prim(bool need_get) {
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
        case Kind::lit: case Kind::bneg: return rep_type{};     // unary operators
        default: return error("primary expected");
    }
}

