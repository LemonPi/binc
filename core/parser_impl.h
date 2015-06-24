#pragma once
#include "consts.h"
#include "parser.h"
#include "error.h"
#include "lexer.h"

namespace Bincalc {  // implementation interface

rep_type term(bool);
rep_type bit_term(bool);
rep_type unary_term(bool);
rep_type prim(bool);


}
