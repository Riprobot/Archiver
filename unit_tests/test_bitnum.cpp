#include "catch/catch.hpp"
#include "../src/bit_num.h"

TEST_CASE("BitNum") {
    BitNum bn = BitNum(2);
    bn.SetBit(0, 1);
    bn.SetBit(1, 0);
    REQUIRE(bn.GetNumeric() == 1);
    bn.SetBit(1, 1);
    REQUIRE(bn.GetNumeric() == 3);
    bn = BitNum(30);
    bn.SetBit(29, 1);
    REQUIRE(bn.GetNumeric() == (1 << 29));
    REQUIRE(bn.GetBit(0) == 0);
    REQUIRE(bn.GetBit(29) == 1);
    bn = BitNum(1);
    bn.SetBit(0, 1);
    REQUIRE(bn.GetBit(0) == 1);
    bn.SetBit(0, 0);
    REQUIRE(bn.GetNumeric() == 0);
}
