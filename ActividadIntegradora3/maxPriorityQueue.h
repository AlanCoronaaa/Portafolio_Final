#ifndef _MAXHEAP_H_
#define _MAXHEAP_H_

#include "vecCount.h"
#include <iostream>
#include <stdexcept>
#include <vector>

template <class T>
class MaxPriorityQueue {
private:
    std::vector<T> data;
    int currentSize;

    int parent(int k);
    int left(int k);
    int right(int k);

public:
    MaxPriorityQueue();
    void enqueue(const T& obj);
    void dequeue();
    T getTop();
    void print();
    void print10();
    bool isEmpty();
    int size();
};

//O(1)
template <class T>
MaxPriorityQueue<T>::MaxPriorityQueue() {
  currentSize = 0;
}

// O(1)
template <class T>
int MaxPriorityQueue<T>::parent(int k) {
    return (k - 1) / 2;
}
// O(1)
template <class T>
int MaxPriorityQueue<T>::left(int k) {
    return (2 * k + 1);
}
// O(1)
template <class T>
int MaxPriorityQueue<T>::right(int k) {
    return (2 * k + 2);
}

// O(log n)
template <class T>
void MaxPriorityQueue<T>::enqueue(const T& obj) {
    data.push_back(obj);
    currentSize++;
    int k = currentSize - 1; 
    while (k != 0 && data[parent(k)].getCount() < data[k].getCount()) {
        std::swap(data[k], data[parent(k)]);
        k = parent(k);
    }
}
// O(n)
template <class T>
void MaxPriorityQueue<T>::print() {
    if (currentSize == 0) {
        std::cout << "El MaxHeap está vacío." << std::endl;
        return;
    }

    std::cout << "Contenido del MaxHeap:" << std::endl;
    for (int i = 0; i < currentSize; i++) {
        std::cout << "Elemento " << i+1 << ": " << data[i].getIpAd() << ", " << data[i].getCount() << std::endl;
    }
}


// O(n)
template <class T>
void MaxPriorityQueue<T>::print10() {
    if (currentSize == 0) {
        std::cout << "El MaxHeap está vacío." << std::endl;
        return;
    }

    std::cout << "10 IPs con mas accesos:" << std::endl;
    for (int i = 0; i < 10; i++) {
        std::cout << "Elemento " << i+1 << ": " << data[i].getIpAd() << ", " << data[i].getCount() << std::endl;
    }
}

//O(log n)
template <class T>
void MaxPriorityQueue<T>::dequeue() {
    if (currentSize == 0) {
        throw std::out_of_range("Underflow: el maxheap está vacío");
    }
    data[0] = data[currentSize - 1];
    data.pop_back();
    currentSize--;
    int k = 0;
    while (true) {
        int leftChild = left(k);
        int rightChild = right(k);
        int largest = k;
        if (leftChild < currentSize && data[leftChild].getCount() > data[largest].getCount()) {
            largest = leftChild;
        }
        if (rightChild < currentSize && data[rightChild].getCount() > data[largest].getCount()){
            largest = rightChild;
        }
        if (largest != k) {
            std::swap(data[k], data[largest]);
            k = largest;
        } else {
            break;
        }
    }
}

template <class T>
T MaxPriorityQueue<T>::getTop() {
    if (isEmpty()) {
        throw std::out_of_range("La cola de prioridad está vacía");
    }
    return data[0];
}


// O(1)
template <class T>
bool MaxPriorityQueue<T>::isEmpty() {
    return currentSize == 0;
}
// O(1)
template <class T>
int MaxPriorityQueue<T>::size() {
    return currentSize;
}

#endif