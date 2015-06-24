#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include "consts.h"

namespace Bincalc {

using Unary_func = rep_type (*)(rep_type);
// modifies
using Modifier_func = void (*)();

extern std::unordered_map<std::string, rep_type> table;
extern const std::unordered_map<std::string, Unary_func> unary_funcs;
extern const std::unordered_map<std::string, Modifier_func> modifier_funcs;
extern std::vector<rep_type> history;

}

