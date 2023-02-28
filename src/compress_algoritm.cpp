#include "compress_algoritm.h"
#include "binary_heap.h"
bool Symbol::operator<(Symbol other) const {
    return std::tie(frequency, symbol_code) < std::tie(other.frequency, other.symbol_code);
}

bool CanonicalCode::operator<(CanonicalCode other) const {
    if (code.size() == other.code.size()) {
        return symbol_code < other.symbol_code;
    }
    return code.size() < other.code.size();
}

CompressAlgoritm::CompressAlgoritm(FileReader& fr, FileWriter& fw, std::string file_name)
    : fr_(fr), fw_(fw), file_name_(file_name) {
}

void CompressAlgoritm::Compress(bool is_last_file) {
    std::vector<std::vector<bool>> haffman_codes = GetHaffmanCodes(CalcSymbolsFrequency());
    size_t max_symbol_code_size = 0;
    for (size_t i = 0; i < haffman_codes.size(); ++i) {
        max_symbol_code_size = std::max(haffman_codes[i].size(), max_symbol_code_size);
    }
    std::vector<size_t> length_count(max_symbol_code_size + 1);
    for (size_t i = 0; i < haffman_codes.size(); ++i) {
        length_count[haffman_codes[i].size()] += 1;
    }
    std::vector<CanonicalCode> can_codes;
    for (size_t i = 0; i < haffman_codes.size(); ++i) {
        if (!haffman_codes[i].empty()) {
            can_codes.push_back(CanonicalCode{haffman_codes[i], i});
        }
    }
    std::sort(can_codes.begin(), can_codes.end());
    std::vector<size_t> symbol_codes;
    for (size_t i = 0; i < can_codes.size(); ++i) {
        symbol_codes.push_back(can_codes[i].symbol_code);
    }
    haffman_codes = BuildCanonicalHaffmanCode(symbol_codes, length_count);
    size_t symbols_count = symbol_codes.size();
    fw_.Write(BitNum(symbols_count, BIT_NUMBER));
    for (size_t i = 0; i < symbol_codes.size(); ++i) {
        fw_.Write(BitNum(symbol_codes[i], BIT_NUMBER));
    }
    for (size_t i = 1; i <= max_symbol_code_size; ++i) {
        fw_.Write(BitNum(length_count[i], BIT_NUMBER));
    }
    for (Byte b : file_name_) {
        WriteHaffmanCode(haffman_codes[static_cast<size_t>(b)]);
    }
    WriteHaffmanCode(haffman_codes[FILENAME_END]);
    fr_.Reset();
    BitNum b8 = BitNum(BITS_IN_BYTE);
    while (fr_.Read(b8)) {
        BitNum b9 = BitNum(b8, BIT_NUMBER);
        size_t symbol_code = b9.GetNumeric();
        WriteHaffmanCode(haffman_codes[symbol_code]);
    }
    if (is_last_file) {
        WriteHaffmanCode(haffman_codes[ARCHIVE_END]);
    } else {
        WriteHaffmanCode(haffman_codes[ONE_MORE_FILE]);
    }
}

void CompressAlgoritm::WriteHaffmanCode(const std::vector<bool>& code) {
    for (auto b : code) {
        fw_.Write(BitNum(b, 1));
    }
}

std::vector<size_t> CompressAlgoritm::CalcSymbolsFrequency() {
    std::vector<size_t> frequency(ALF_LEN);
    frequency[FILENAME_END] = 1;
    frequency[ONE_MORE_FILE] = 1;
    frequency[ARCHIVE_END] = 1;

    for (Byte b : file_name_) {
        BitNum b9({b}, BIT_NUMBER);
        frequency[b9.GetNumeric()] += 1;
    }
    BitNum b8 = BitNum(BITS_IN_BYTE);
    while (fr_.Read(b8)) {
        BitNum b9 = BitNum(b8, BIT_NUMBER);
        frequency[b9.GetNumeric()] += 1;
    }
    return frequency;
}

std::vector<std::vector<bool>> CompressAlgoritm::GetHaffmanCodes(std::vector<size_t> frequency) {
    std::vector<std::vector<bool>> haffman_codes(ALF_LEN);
    Trie t = Trie(2);
    std::vector<Trie::Node*> terminal(ALF_LEN);
    for (size_t i = 0; i < ALF_LEN; ++i) {
        if (frequency[i] > 0) {
            terminal[i] = t.CreateNewNode();
        }
    }
    BinaryHeap<Symbol> pq;
    for (size_t i = 0; i < ALF_LEN; ++i) {
        if (frequency[i] > 0) {
            Symbol s = Symbol{frequency[i], i, terminal[i]};
            pq.Add(s);
        }
    }

    while (pq.GetSize() > 1) {
        Symbol a = pq.GetTop();
        pq.DelMin();
        Symbol b = pq.GetTop();
        pq.DelMin();
        Trie::Node* c_node = t.CreateNewNode({a.node, b.node});
        size_t c_code = std::min(a.symbol_code, b.symbol_code);
        size_t c_freq = a.frequency + b.frequency;
        pq.Add(Symbol{c_freq, c_code, c_node});
    }
    Trie::Node* root = pq.GetTop().node;
    t.ChangeRoot(root);
    for (size_t i = 0; i < ALF_LEN; ++i) {
        if (frequency[i] > 0) {
            haffman_codes[i] = t.GetCode<bool>(terminal[i]);
        }
    }
    return haffman_codes;
}
