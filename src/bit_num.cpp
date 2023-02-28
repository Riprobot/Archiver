#include "bit_num.h"

BitNum::BitNum(int bit_number) : bit_number_(bit_number), bytes_((bit_number_ + BITS_IN_BYTE - 1) / BITS_IN_BYTE) {
}

BitNum::BitNum() : BitNum(BITS_IN_BYTE) {
}

BitNum::BitNum(const std::initializer_list<Byte> bytes, int bit_number) : BitNum(bit_number) {
    size_t ind = 0;
    for (Byte b : bytes) {
        bytes_[ind++] = b;
        if (ind == bytes_.size()) {
            break;
        }
    }
}

BitNum::BitNum(size_t x, int bit_number) : BitNum(bit_number) {
    for (size_t i = 0; i < BytesSize(); ++i) {
        bytes_[i] = (x & ((1 << BITS_IN_BYTE) - 1));
        x >>= BITS_IN_BYTE;
    }
}

BitNum::BitNum(BitNum b, int bit_number) : bit_number_(bit_number), bytes_(b.bytes_) {
    bytes_.resize((bit_number_ + BITS_IN_BYTE - 1) / BITS_IN_BYTE);
}

size_t BitNum::GetNumeric() {
    size_t x = 0;
    for (size_t i = bytes_.size(); i > 0; --i) {
        int shift = std::min(BITS_IN_BYTE, bit_number_ - static_cast<int>(i - 1) * BITS_IN_BYTE);
        x = ((x << shift) + (bytes_[i - 1] & ((1 << shift) - 1)));
    }
    return x;
}

size_t BitNum::BytesSize() const {
    return bytes_.size();
}

bool BitNum::GetBit(size_t pos) {
    return (bytes_[pos / BITS_IN_BYTE] & (1 << (pos % BITS_IN_BYTE)));
}

void BitNum::SetBit(size_t pos, bool bit) {
    if (GetBit(pos) == bit) {
        return;
    }
    if (bit == 1) {
        bytes_[pos / BITS_IN_BYTE] += (1 << (pos % BITS_IN_BYTE));
    } else {
        bytes_[pos / BITS_IN_BYTE] -= (1 << (pos % BITS_IN_BYTE));
    }
}

void BitNum::Clear() {
    bytes_.clear();
    bytes_.resize((bit_number_ + BITS_IN_BYTE - 1) / BITS_IN_BYTE);
}
