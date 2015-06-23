#pragma once
#include <string>
#include <iostream>
#include <memory>   // shared_ptr
#include "consts.h"

namespace Lexer {

using namespace std;
enum class Kind : char {
    name, minus, number = '#', end, oct = '0', hex = 'x',
    plus = '+', mag_neg = '-', mul = '*', div = '/', print = ';', assign = '=', lp = '(', rp = ')',
    fact = '!', pow = '\'', mod = '%',
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

    Token get();    // read and return next token
    const Token& current() { return ct; } // most recently read token

    void set_input(istream& instream_ref) { ip = shared_ptr<istream>(&instream_ref); owns = false; }
    void set_input(istream* instream_pt) { ip = shared_ptr<istream>(instream_pt); owns = true; }

private:
    shared_ptr<istream> ip;    // input stream pointer
    bool owns;
    Token ct {Kind::end};   // current token, default value in case of misuse
};

extern Token_stream ts;

bool isname_punc(char c);

}
