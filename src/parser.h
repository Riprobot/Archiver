#pragma once

#include <string>
#include <vector>

class Parser {
public:
    class WrongFormatException : public std::exception {};
    enum Mode { Compress, Decompress, Help, None };
    Parser(unsigned int argc, char** argv);
    Mode GetMode() const;
    const std::string GetArchiveName() const;
    std::vector<std::string> GetFileNames() const;
    void Parse();

private:
    unsigned int argc_ = 0;
    char** argv_ = nullptr;
    Mode mode_ = Mode::None;
    char* archive_name_ = nullptr;
    std::vector<std::string> file_names_;
};
