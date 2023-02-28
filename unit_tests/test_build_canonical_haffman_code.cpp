#include "catch/catch.hpp"
#include "../src/build_canonical_haffman.h"

TEST_CASE("BuildCanonicalHaffman") {
    // B = 0
    // A = 11
    // C = 101
    // D = 100
    std::vector<std::vector<bool>> answer = BuildCanonicalHaffmanCode({1, 0, 2, 3}, {0, 1, 1, 2});
    // B = 0
    // A = 10
    // C = 110
    // D = 111
    std::vector<std::vector<bool>> real_answer(ALF_LEN);
    real_answer[0] = {1, 0};
    real_answer[1] = {0};
    real_answer[2] = {1, 1, 0};
    real_answer[3] = {1, 1, 1};
    REQUIRE(answer == real_answer);
    // D = 00
    // C = 11
    // B = 10
    // A = 01
    answer = BuildCanonicalHaffmanCode({3, 2, 1, 0}, {0, 0, 4});
    // D = 00
    // C = 01
    // B = 10
    // A = 11
    real_answer = std::vector<std::vector<bool>>(ALF_LEN);
    real_answer[3] = {0, 0};
    real_answer[2] = {0, 1};
    real_answer[1] = {1, 0};
    real_answer[0] = {1, 1};
    REQUIRE(answer == real_answer);
}
