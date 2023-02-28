#pragma once

#include <vector>
#include <deque>
#include "const_variables.h"

std::vector<std::vector<bool>> BuildCanonicalHaffmanCode(std::vector<size_t> symbol_codes,
                                                         std::vector<size_t> length_count);
