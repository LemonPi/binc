#include <cctype>
#include <bitset>
#include "error.h"
#include "lexer.h"

namespace Lexer {


Token_stream ts {nullptr};

Token Token_stream::get() {
    // read 1 char, decide what kind of token is incoming,
    // appropriately read more char then return Token
    char c = 0;

    // skip all whitespace except newline
    do {  
        if(!ip->get(c)) return ct = {Kind::end};  // no char can be read from ip
    } while (c != '\n' && isspace(c));

    switch (c) {
        case ';':
        case '\n':
            return ct = {Kind::print};
        case '!':
            if (ct.kind == Kind::number || ct.kind == Kind::name) { ct.kind = Kind::fact; return ct; }
        case '*':
            if (ip->peek() == '*') { ip->get(); return ct = {Kind::pow}; }
            else return ct = {Kind::mul};
        case '-':
            if (ct.kind == Kind::number || ct.kind == Kind::name || ct.kind == Kind::rp) return ct = {Kind::minus};
        case '%':
        case '(':
        case ')':
        case '+':
        case '/':
        case '&':
        case '|':
        case '^':
        case '~':
        case '\\':
        case '=':
            return ct = {static_cast<Kind>(c)}; // operators
        case '>':
        case '<':
        	if (ip->peek() == c) ip->get(); // get >> and <<
        	return ct = {static_cast<Kind>(c)}; 
        case '0':
            if (isalnum(ip->peek())) { // else use 0 as number
                if (ip->peek() == 'x') ct = {Kind::hex};
                else ct = {Kind::oct};
            }   // automatically drop down to number treatment
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '.':
            ip->putback(c);
            if (ct.kind == Kind::hex) { int tmp; *ip >> hex >> tmp; ct.number_val = static_cast<rep_type>(tmp); }
            else if (ct.kind == Kind::oct) { int tmp; *ip >> oct >> tmp; ct.number_val = static_cast<rep_type>(tmp); }
            else *ip >> ct.number_val;
            ct.kind = Kind::number;
            return ct;
        case '@': {
            size_t from_last {1};
            while (ip->peek() == '@') {
                ip->get(c);
                ++from_last;
            }
            ct.number_val = from_last;
            ct.kind = Kind::last;
            return ct; 
        }
		case 'b': 	// binary
            if (ip->peek() == '0' || ip->peek() == '1') {
                bitset<bit_num> bits;
                *ip >> bits;
                ct.number_val = static_cast<rep_type>(bits.to_ulong());
                ct.kind = Kind::number;
                return ct;
            }
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


}   // end namespace Lexer