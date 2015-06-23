#ifndef bc_parser_impl
#define bc_parser_impl
#include "consts.h"
#include "parser.h"
#include "error.h"
#include "lexer.h"

namespace Parser {  // implementation interface

rep_type term(bool);
rep_type bit_term(bool);
rep_type unary_term(bool);
rep_type prim(bool);

using namespace Lexer;
using Error::error;

}
#endif
