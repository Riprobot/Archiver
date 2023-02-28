#include "parser.h"

void Parser::Parse() {
    if (argc_ >= 1) {
        if (std::string(argv_[1]) == "-c") {
            mode_ = Compress;
        } else if (std::string(argv_[1]) == "-d") {
            mode_ = Decompress;
        } else if (std::string(argv_[1]) == "-h") {
            mode_ = Help;
            if (argc_ != 2) {
                throw WrongFormatException();
            }
            return;
        } else {
            throw WrongFormatException();
        }
    } else {
        throw WrongFormatException();
    }
    if (argc_ < 3 || (mode_ == Decompress && argc_ != 3)) {
        throw WrongFormatException();
    }
    archive_name_ = argv_[2];
    if (mode_ == Compress) {
        for (size_t i = 3; i < static_cast<size_t>(argc_); ++i) {
            file_names_.push_back(argv_[i]);
        }
    }
}

Parser::Parser(unsigned int argc, char **argv) : argc_(argc), argv_(argv), mode_(None) {
}
Parser::Mode Parser::GetMode() const {
    return mode_;
}
const std::string Parser::GetArchiveName() const {
    return archive_name_;
}
std::vector<std::string> Parser::GetFileNames() const {
    return file_names_;
}
