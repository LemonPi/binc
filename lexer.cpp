#include <cctype>
#include "error.h"
#include "lexer.h"

Lexer::Token_stream Lexer::ts {cin};

Lexer::Token Lexer::Token_stream::get() {
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
        case '-':
            if (ct.kind != Kind::number && ct.kind != Kind::name) return ct = {Kind::mag_neg};
        case '*':
        case '/':
        case '+':
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
            if (isalnum(ip->peek())) // else use 0 as number
                return ct = {Kind::oct};
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
            if (ct.kind == Kind::hex) { int tmp; *ip >> hex >> tmp; ct.number_val = static_cast<rep_type>(tmp); }
            else if (ct.kind == Kind::oct) { int tmp; *ip >> oct >> tmp; ct.number_val = static_cast<rep_type>(tmp); }
            else *ip >> ct.number_val;
            ct.kind = Kind::number;
            return ct;
        case 'x':
            if (ct.kind == Kind::oct)   // fall down to default otherwise
                return ct = {Kind::hex};
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
            Error::error("bad token");
            return ct = {Kind::print};
    }
}

