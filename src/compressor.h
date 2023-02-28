#pragma once

#include <string>
#include <vector>
#include <fstream>
#include "compress_algoritm.h"
#include "parser.h"

class Compressor {
public:
    explicit Compressor(std::vector<std::string> file_names, std::string archive_name);
    void CompressFiles();

private:
    std::string GetName(const std::string file_path);
    void CompressFile(std::string file_name, bool is_last_file);

private:
    std::vector<std::string> file_names_;
    std::string archive_name_;
    FileWriter fw_;
};
