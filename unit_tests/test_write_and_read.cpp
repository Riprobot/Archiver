#include "catch/catch.hpp"
#include "../src/file_reader.h"
#include "../src/file_writer.h"

namespace {
size_t NumberFromBinCode(std::string s) {
    size_t ans = 0;
    for (size_t i = s.size(); i > 0; --i) {
        ans *= 2;
        ans += (s[i - 1] - '0');
    }
    return ans;
}
}  // namespace

TEST_CASE("WriteAndRead") {
    std::string data = "0000000011101111";
    {
        FileWriter fw = FileWriter("data");
        BitNum bn = BitNum(NumberFromBinCode(data), 16);
        fw.Write(bn);
    }
    {
        FileReader fr = FileReader("data");
        BitNum bn = BitNum(16);
        fr.Read(bn);
        REQUIRE(bn.GetNumeric() == NumberFromBinCode(data));
    }
    std::string s1 = "00000000";
    std::string s2 = "1";
    std::string s3 = "11";
    std::string s4 = "01111";
    {
        FileWriter fw = FileWriter("data");
        BitNum bn = BitNum(NumberFromBinCode(s1), s1.size());
        fw.Write(bn);
        bn = BitNum(NumberFromBinCode(s2), s2.size());
        fw.Write(bn);
        bn = BitNum(NumberFromBinCode(s3), s3.size());
        fw.Write(bn);
        bn = BitNum(NumberFromBinCode(s4), s4.size());
        fw.Write(bn);
    }
    {
        FileReader fr = FileReader("data");
        BitNum bn = BitNum(s1.size());  // 00000000
        fr.Read(bn);
        REQUIRE(bn.GetNumeric() == NumberFromBinCode(s1));
        bn = BitNum(s2.size());  // 1
        fr.Read(bn);
        REQUIRE(bn.GetNumeric() == NumberFromBinCode(s2));
        bn = BitNum(s3.size());  // 11
        fr.Read(bn);
        REQUIRE(bn.GetNumeric() == NumberFromBinCode(s3));
        bn = BitNum(s4.size());  // 01111
        fr.Read(bn);
        REQUIRE(bn.GetNumeric() == NumberFromBinCode(s4));
    }
}
