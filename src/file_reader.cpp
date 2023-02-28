#include "file_reader.h"

FileReader::FileReader(std::string file_name)
    : used_at_front_(0), in_(file_name, std::fstream::binary), file_name_(file_name) {
    if (!in_.is_open()) {
        throw FileOpenException();
    }
}

bool FileReader::Read(BitNum& b) {
    b.Clear();
    int bits_number = b.bit_number_;
    int total_bit = bits_number - 1;
    while (total_bit != -1) {
        if (input_.empty()) {
            if (!ReadToQueue()) {
                return false;
            }
            used_at_front_ = 0;
        }
        b.SetBit(total_bit, (input_.back() & (1 << (BITS_IN_BYTE - 1 - used_at_front_))));
        used_at_front_ += 1;
        if (used_at_front_ == BITS_IN_BYTE) {
            input_.pop_front();
        }
        total_bit--;
    }
    return true;
}

void FileReader::Reset() {
    CloseFile();
    input_.clear();
    used_at_front_ = 0;
    in_ = std::ifstream(file_name_, std::fstream::binary);
}

FileReader::~FileReader() {
    CloseFile();
}

void FileReader::CloseFile() {
    in_.close();
}

bool FileReader::ReadToQueue() {
    char x = 0;
    in_.read(&x, 1);
    Byte new_byte = x;
    if (in_.eof()) {
        return false;
    }
    input_.push_back(new_byte);
    return true;
}
