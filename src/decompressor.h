#pragma once

#include <string>
#include <vector>
#include <fstream>
#include "compress_algoritm.h"
#include "trie.h"
#include "build_canonical_haffman.h"

class Decompressor {
public:
    class BadArchive : std::exception {};
    explicit Decompressor(std::string archive_name);
    std::vector<std::string> DecompressArchive();

private:
    void CalcTrie(std::vector<std::vector<bool>> haffman_codes);
    std::vector<std::vector<bool>> GetHaffmanCodes();
    std::string ReadFileName();
    void ReadAndWriteFileData(FileWriter& fw);

private:
    bool is_archive_end_ = false;
    std::string archive_name_;
    FileReader fr_;
    Trie trie_;
};
