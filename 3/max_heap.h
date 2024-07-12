#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#include <vector>
#include <stdexcept>
#include <iostream>

template <typename T>
class MaxHeap {
public:
    MaxHeap() {}

    void Insert(const T& element) {
        heap.push_back(element);
        HeapifyUp(heap.size() - 1);
    }

    T DeleteMax() {
        if (IsEmpty()) throw std::runtime_error("Heap is empty");
        T maxElement = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        HeapifyDown(0);
        return maxElement;
    }

    bool IsEmpty() const {
        return heap.empty();
    }

private:
    std::vector<T> heap;

    void HeapifyUp(int index) {
        while (index > 0 && heap[Parent(index)] < heap[index]) {
            std::swap(heap[index], heap[Parent(index)]);
            index = Parent(index);
        }
    }

    void HeapifyDown(int index) {
        int left = LeftChild(index);
        int right = RightChild(index);
        int largest = index;

        if (left < heap.size() && heap[left] > heap[largest]) {
            largest = left;
        }

        if (right < heap.size() && heap[right] > heap[largest]) {
            largest = right;
        }

        if (largest != index) {
            std::swap(heap[index], heap[largest]);
            HeapifyDown(largest);
        }
    }

    int Parent(int index) const {
        return (index - 1) / 2;
    }

    int LeftChild(int index) const {
        return 2 * index + 1;
    }

    int RightChild(int index) const {
        return 2 * index + 2;
    }
};

#endif // MAX_HEAP_H
