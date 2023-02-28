#include "trie.h"

Trie::Node::Node(size_t sons_num) {
    sons.resize(sons_num);
    parent_type = -1;
    parent = nullptr;
    is_terminal = false;
    value = 0;
}

Trie::Trie(size_t sons_num) : sons_num_(sons_num) {
}

Trie::Node* Trie::CreateNewNode() {
    Node* node = new Node(sons_num_);
    all_nodes_.push_back(node);
    return node;
}

Trie::Node* Trie::CreateNewNode(std::initializer_list<Node*> sons) {
    if (sons.size() != sons_num_) {
        throw IncomparableSonsSize();
    }
    Node* node = new Node(sons_num_);
    all_nodes_.push_back(node);
    node->sons = sons;
    size_t id = 0;
    for (auto son : sons) {
        if (son != nullptr) {
            son->parent = node;
            son->parent_type = id;
        }
        id++;
    }
    return node;
}

Trie::Node* Trie::CreateNewNode(Trie::Node* parent, size_t type) {
    if (parent == nullptr) {
        throw NullptrException();
    }
    Node* node = new Node(sons_num_);
    all_nodes_.push_back(node);
    node->parent = parent;
    node->parent_type = type;
    if (parent->sons[type] != nullptr) {
        parent->sons[type]->parent = nullptr;
        parent->sons[type]->parent_type = -1;
    }
    parent->sons[type] = node;
    return node;
}

void Trie::MakeTerminal(Trie::Node* root, size_t value) {
    root->is_terminal = true;
    root->value = value;
}

size_t Trie::GetValue(Trie::Node* ver) {
    if (!ver->is_terminal) {
        throw NotTerminalException();
    }
    return ver->value;
}

Trie::Node* Trie::GetRoot() {
    return root_;
}

Trie::Node* Trie::GetSon(Trie::Node* ver, size_t type) const {
    if (type < 0 || type >= sons_num_) {
        throw OutOfRangeException();
    }
    if (ver == nullptr || ver->sons[type] == nullptr) {
        throw OutOfRangeException();
    }
    return ver->sons[type];
}

void Trie::ChangeRoot(Trie::Node* root) {
    root_ = root;
    if (root_->parent != nullptr) {
        size_t type = root_->parent_type;
        root_->parent->sons[type] = nullptr;
    }
    root_->parent = nullptr;
    root_->parent_type = -1;
}

Trie::~Trie() {
    for (size_t i = 0; i < all_nodes_.size(); ++i) {
        delete all_nodes_[i];
    }
}
