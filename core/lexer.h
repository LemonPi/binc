#pragma once
#include <string>
#include <iostream>
#include <memory>   // shared_ptr
#include "consts.h"

namespace Bincalc {

using namespace std;

enum class Kind : char {
    name = 'n', minus = 'm', number = '#', end = '.', oct = '0', hex = 'x',
    plus = '+', mag_neg = '-', mul = '*', div = '/', print = ';', newline = '\n',
    assign = '=', lp = '(', rp = ')', fact = '!', pow = '\'', mod = '%',
    lshift = '<', rshift = '>', band = '&', bor = '|', bxor = '^', bneg = '~', lit = '\\',
    last = '@'
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
    ~Token_stream() {clear();}

    Token get();    // read and return next token
    void end_stream() {ip->setstate(ios_base::eofbit);}
    const Token& current() { return ct; } // most recently read token
    const Token& previous() { return pt; } 

    // closes the previous input stream if owned
    void set_input(istream& instream_ref) {clear(); ip = &instream_ref; owns = false; }
    void set_input(istream* instream_pt) {clear(); ip = instream_pt; owns = true; }

private:
    void clear() {if(owns) delete ip;}

    istream* ip;    // input stream pointer
    bool owns;
    Token ct {Kind::end};   // current token, default value in case of misuse
    Token pt;
};

extern Token_stream ts;
extern ostream& os;

bool isname_punc(char c);

}
