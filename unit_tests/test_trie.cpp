#include "catch/catch.hpp"
#include "..\src\trie.h"

TEST_CASE("Trie") {
    Trie tr(2);
    Trie::Node* root = tr.CreateNewNode();
    tr.ChangeRoot(root);
    Trie::Node* a = tr.CreateNewNode(root, 0);
    Trie::Node* b = tr.CreateNewNode(root, 1);
    std::vector<size_t> str1 = {0, 0, 1};
    std::vector<size_t> str2 = {1, 1, 1};
    std::vector<size_t> strA = {0};
    std::vector<size_t> strB = {1};
    Trie::Node* term1 = tr.AddCode(str1);
    Trie::Node* term2 = tr.AddCode(str2);
    tr.MakeTerminal(term1, 1);
    tr.MakeTerminal(term2, 0);
    REQUIRE(str1 == tr.GetCode<size_t>(term1));
    REQUIRE(str2 == tr.GetCode<size_t>(term2));
    REQUIRE(tr.GetValue(term1) == 1);
    REQUIRE(tr.GetValue(term2) == 0);
    REQUIRE(a == tr.AddCode(strA));
    REQUIRE(b == tr.AddCode(strB));
}
