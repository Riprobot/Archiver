#pragma once

#include <fstream>
#include <tuple>
#include "file_reader.h"
#include "file_writer.h"
#include "trie.h"
#include "build_canonical_haffman.h"

struct Symbol {
    size_t frequency;
    size_t symbol_code;
    Trie::Node* node;
    bool operator<(Symbol other) const;
};

struct CanonicalCode {
    std::vector<bool> code;
    size_t symbol_code;
    bool operator<(CanonicalCode other) const;
};
class CompressAlgoritm {
    using Byte = unsigned char;

public:
    CompressAlgoritm(FileReader& fr, FileWriter& fw, std::string file_name);
    void Compress(bool is_last_file);

private:
    void WriteHaffmanCode(const std::vector<bool>& code);
    std::vector<size_t> CalcSymbolsFrequency();
    std::vector<std::vector<bool>> GetHaffmanCodes(std::vector<size_t> frequency);

private:
    FileReader& fr_;
    FileWriter& fw_;
    std::string file_name_;
};
