#pragma once

#include <vector>
#include <algorithm>

class Trie {
public:
    class IncomparableSonsSize : std::exception {};
    class NullptrException : std::exception {};
    class NotTerminalException : std::exception {};
    class OutOfRangeException : std::exception {};

    struct Node {
        std::vector<Node*> sons;
        Node* parent;
        size_t parent_type;
        bool is_terminal;
        size_t value;
        explicit Node(size_t sons_num);
    };

    explicit Trie(size_t sons_num);
    Node* CreateNewNode();
    Node* CreateNewNode(std::initializer_list<Node*> sons);
    Node* CreateNewNode(Node* parent, size_t type);
    void MakeTerminal(Node* root, size_t value);
    size_t GetValue(Node* ver);
    Node* GetRoot();
    Node* GetSon(Node* ver, size_t type) const;
    void ChangeRoot(Node* root);
    template <typename T>
    Node* AddCode(std::vector<T> code) {
        if (root_ == nullptr) {
            throw NullptrException();
        }
        Node* now = root_;
        for (size_t i = 0; i < code.size(); i += 1) {
            size_t type = code[i];
            if (type < 0 || type >= sons_num_) {
                throw OutOfRangeException();
            }
            if (now->sons[type] == nullptr) {
                now = CreateNewNode(now, type);
            } else {
                now = now->sons[type];
            }
        }
        return now;
    }
    template <typename T>
    std::vector<T> GetCode(Node* terminal) {
        if (terminal == nullptr) {
            throw NullptrException();
        }
        std::vector<T> code;
        Node* now = terminal;
        while (now->parent != nullptr) {
            code.push_back(now->parent_type);
            now = now->parent;
        }
        std::reverse(code.begin(), code.end());
        return code;
    }
    ~Trie();

private:
    Node* root_ = nullptr;
    size_t sons_num_ = 0;
    std::vector<Node*> all_nodes_;
};
