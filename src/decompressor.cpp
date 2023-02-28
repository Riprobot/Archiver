#include "decompressor.h"

Decompressor::Decompressor(std::string archive_name) : is_archive_end_(false), fr_(archive_name), trie_(2) {
}

std::vector<std::string> Decompressor::DecompressArchive() {
    std::vector<std::string> file_names;
    while (!is_archive_end_) {
        std::vector<std::vector<bool>> haffman_codes = GetHaffmanCodes();
        CalcTrie(haffman_codes);
        std::string file_name = ReadFileName();
        FileWriter fw = FileWriter(file_name);
        ReadAndWriteFileData(fw);
        file_names.push_back(file_name);
    }
    return file_names;
}

void Decompressor::CalcTrie(std::vector<std::vector<bool>> haffman_codes) {
    // making trie
    Trie::Node* root = trie_.CreateNewNode();
    trie_.ChangeRoot(root);
    std::vector<Trie::Node*> terminal(haffman_codes.size());
    for (size_t i = 0; i < haffman_codes.size(); ++i) {
        if (!haffman_codes[i].empty()) {
            trie_.MakeTerminal(trie_.AddCode(haffman_codes[i]), i);
        }
    }
}

std::vector<std::vector<bool>> Decompressor::GetHaffmanCodes() {
    // reading data
    BitNum b9 = BitNum(BIT_NUMBER);
    fr_.Read(b9);
    size_t symbols_count = b9.GetNumeric();
    std::vector<size_t> symbol_codes;
    for (size_t i = 0; i < symbols_count; ++i) {
        fr_.Read(b9);
        symbol_codes.push_back(b9.GetNumeric());
    }
    std::vector<size_t> length_count;
    length_count.push_back(0);
    size_t sum = 0;
    while (sum < symbols_count) {
        fr_.Read(b9);
        size_t cnt = b9.GetNumeric();
        length_count.push_back(cnt);
        sum += cnt;
    }
    if (sum != symbols_count) {
        throw BadArchive();
    }
    // making_haffman_codes
    return BuildCanonicalHaffmanCode(symbol_codes, length_count);
}

std::string Decompressor::ReadFileName() {
    std::string ans;
    BitNum b1 = BitNum(1);
    Trie::Node* root = trie_.GetRoot();
    while (fr_.Read(b1)) {
        root = trie_.GetSon(root, b1.GetNumeric());
        if (root->is_terminal) {
            size_t symbol_code = trie_.GetValue(root);
            if (symbol_code == FILENAME_END) {
                break;
            }
            ans.push_back(static_cast<char>(static_cast<unsigned char>(symbol_code)));
            root = trie_.GetRoot();
        }
    }
    return ans;
}

void Decompressor::ReadAndWriteFileData(FileWriter& fw) {
    BitNum b1 = BitNum(1);
    Trie::Node* root = trie_.GetRoot();
    while (fr_.Read(b1)) {
        root = trie_.GetSon(root, b1.GetNumeric());
        if (root->is_terminal) {
            size_t symbol_code = trie_.GetValue(root);
            if (symbol_code == ONE_MORE_FILE || symbol_code == ARCHIVE_END) {
                if (symbol_code == ARCHIVE_END) {
                    is_archive_end_ = true;
                }
                break;
            }
            fw.Write(BitNum(symbol_code, CHAR_BIT));
            root = trie_.GetRoot();
        }
    }
}
