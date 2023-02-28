#include "file_writer.h"

FileWriter::FileWriter(std::string file_name)
    : empty_at_back_(0), out_(file_name, std::fstream::binary), file_name_(file_name) {
    if (!out_.is_open()) {
        throw FileOpenException();
    }
}

void FileWriter::Write(BitNum b) {
    int bits_number = b.bit_number_;
    int total_bit = bits_number - 1;
    while (total_bit != -1) {
        if (empty_at_back_ == 0) {
            output_.push_back(0);
            empty_at_back_ = BITS_IN_BYTE;
        }
        output_.back() += b.GetBit(total_bit) * (1 << (empty_at_back_ - 1));
        empty_at_back_--;
        total_bit--;
    }
    WriteFromQueue();
}

void FileWriter::Reset() {
    CloseFile();
    output_.clear();
    empty_at_back_ = 0;
    out_ = std::ofstream(file_name_, std::fstream::binary);
}

FileWriter::~FileWriter() {
    CloseFile();
}

void FileWriter::CloseFile() {
    while (!output_.empty()) {
        out_ << output_.front();
        output_.pop_front();
    }
    out_.close();
}

void FileWriter::WriteFromQueue() {
    while (output_.size() > 1 || (empty_at_back_ == 0 && !output_.empty())) {
        out_ << output_.front();
        output_.pop_front();
    }
}
