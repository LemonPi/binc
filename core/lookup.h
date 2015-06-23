#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include "consts.h"


namespace Lookup {

using Unary_func = rep_type (*)(rep_type);

extern std::unordered_map<std::string, rep_type> table;
extern std::unordered_map<std::string, Unary_func> unary_funcs;
extern std::vector<rep_type> history;

}

