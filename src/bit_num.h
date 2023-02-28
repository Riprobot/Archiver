#pragma once

#include <vector>
#include "const_variables.h"

class BitNum {
    using Byte = unsigned char;

public:
    explicit BitNum(int bit_number);
    BitNum();
    BitNum(const std::initializer_list<Byte> bytes, int bit_number);
    BitNum(size_t x, int bit_number);
    BitNum(BitNum b, int bit_number);
    size_t GetNumeric();
    size_t BytesSize() const;
    bool GetBit(size_t pos);
    void SetBit(size_t pos, bool bit);
    void Clear();
    int bit_number_ = BITS_IN_BYTE;
    std::vector<Byte> bytes_;
};
