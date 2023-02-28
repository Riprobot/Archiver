#include <algorithm>
#include "build_canonical_haffman.h"

std::vector<std::vector<bool>> BuildCanonicalHaffmanCode(std::vector<size_t> symbol_codes,
                                                         std::vector<size_t> length_count) {
    std::vector<std::vector<bool>> haffman_codes(ALF_LEN);
    std::deque<bool> code = {false};
    size_t total_length = 1;
    while (length_count[total_length] == 0) {
        total_length += 1;
        code.push_front(false);
    }
    for (size_t i = 0; i < symbol_codes.size(); i += 1) {
        for (size_t j = 0; j < code.size(); ++j) {
            haffman_codes[symbol_codes[i]].push_back(code[j]);
        }
        std::reverse(haffman_codes[symbol_codes[i]].begin(), haffman_codes[symbol_codes[i]].end());
        size_t id = 0;
        while (id < code.size() && code[id] == 1) {
            id += 1;
        }
        if (id == code.size()) {
            code.push_back(false);
        }
        for (size_t j = 0; j < id; ++j) {
            code[j] = false;
        }
        code[id] = true;
        if (i != symbol_codes.size() - 1) {
            length_count[total_length] -= 1;
            while (length_count[total_length] == 0) {
                total_length += 1;
                code.push_front(false);
            }
        }
    }
    return haffman_codes;
}
