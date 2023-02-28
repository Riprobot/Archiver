#include "catch/catch.hpp"
#include "..\src\binary_heap.h"

TEST_CASE("Heap") {
    BinaryHeap<int> pq;
    pq.Add(0);
    REQUIRE(pq.GetTop() == 0);
    pq.Add(100);
    pq.Add(99);
    pq.DelMin();
    REQUIRE(pq.GetTop() == 99);
    REQUIRE(pq.GetSize() == 2);
    pq.Add(100);
    pq.DelMin();
    REQUIRE(pq.GetTop() == 100);
    REQUIRE(pq.GetSize() == 2);
    pq.DelMin();
    REQUIRE(pq.GetSize() == 1);
    REQUIRE(pq.GetTop() == 100);
    pq.DelMin();
    REQUIRE(pq.GetSize() == 0);
}
