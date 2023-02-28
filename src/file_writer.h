#pragma once

#include <queue>
#include <fstream>
#include "bit_num.h"
#include "const_variables.h"

class FileWriter {
    using Byte = unsigned char;

public:
    class FileOpenException : std::exception {};
    explicit FileWriter(std::string file_name);
    void Write(BitNum b);
    void Reset();
    ~FileWriter();

private:
    void CloseFile();
    void WriteFromQueue();

private:
    std::deque<Byte> output_;
    int empty_at_back_ = 0;
    std::ofstream out_;
    std::string file_name_;
};
