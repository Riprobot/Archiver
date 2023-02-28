#pragma once

#include <queue>
#include <fstream>
#include "bit_num.h"

class FileReader {
    using Byte = unsigned char;

public:
    class FileOpenException : std::exception {};
    explicit FileReader(std::string file_name);
    bool Read(BitNum& b);
    void Reset();
    ~FileReader();

private:
    void CloseFile();
    bool ReadToQueue();

private:
    std::deque<Byte> input_;
    int used_at_front_ = 0;
    std::ifstream in_;
    std::string file_name_;
};
