#include "compressor.h"

Compressor::Compressor(std::vector<std::string> file_names, std::string archive_name)
    : file_names_(file_names), fw_(archive_name) {
}

void Compressor::CompressFiles() {
    for (size_t i = 0; i < file_names_.size(); ++i) {
        CompressFile(file_names_[i], i + 1 == file_names_.size());
    }
}

void Compressor::CompressFile(std::string file_name, bool is_last_file) {
    FileReader fr(file_name);
    CompressAlgoritm ca = CompressAlgoritm(fr, fw_, GetName(file_name));
    ca.Compress(is_last_file);
}

std::string Compressor::GetName(const std::string file_path) {
    std::string ans;
    for (size_t i = 0; i < file_path.size(); i += 1) {
        if (file_path[i] == '\\' || file_path[i] == '/') {
            ans = "";
        } else {
            ans.push_back(file_path[i]);
        }
    }
    return ans;
}
