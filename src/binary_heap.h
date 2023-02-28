#include <vector>

template <typename T>
class BinaryHeap {
public:
    BinaryHeap() : heap_nodes_(0) {
    }
    void Add(T element) {
        heap_nodes_.push_back(element);
        SiftUp(heap_nodes_.size() - 1);
    }
    void DelMin() {
        if (heap_nodes_.empty()) {
            throw std::exception();
        }
        heap_nodes_[0] = heap_nodes_.back();
        SiftDown(0);
        heap_nodes_.pop_back();
    }
    size_t GetSize() {
        return heap_nodes_.size();
    }
    T GetTop() {
        return heap_nodes_[0];
    }

private:
    void SiftUp(size_t v) {
        while (v > 0 && heap_nodes_[v] < heap_nodes_[(v - 1) / 2]) {
            std::swap(heap_nodes_[v], heap_nodes_[(v - 1) / 2]);
            v = (v - 1) / 2;
        }
    }
    size_t GetMinSon(size_t v) {
        size_t left = v * 2 + 1;
        size_t right = v * 2 + 2;
        if (right >= heap_nodes_.size() && left >= heap_nodes_.size()) {
            return 0;
        }
        if (right >= heap_nodes_.size()) {
            return left;
        }
        if (heap_nodes_[left] < heap_nodes_[right]) {
            return left;
        } else {
            return right;
        }
    }
    void SiftDown(size_t v) {
        while (GetMinSon(v) != 0) {
            size_t min_son = GetMinSon(v);
            if (heap_nodes_[v] < heap_nodes_[min_son]) {
                return;
            }
            std::swap(heap_nodes_[v], heap_nodes_[min_son]);
            v = min_son;
        }
    }
    std::vector<T> heap_nodes_;
};
