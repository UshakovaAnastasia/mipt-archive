#ifndef STACK_ARRAY_H
#define STACK_ARRAY_H

#include <iostream>

template <class T>
class Stack {
private:
    const int MAX_SIZE = 100000;
    struct Node {
        T value;
        T min;
        T max;
    };
    Node * buffer_;
    int size_;
    
public:
    Stack();
    Stack(int n,
          const T & value);
    const T & Top();
    bool Empty();
    void Push(const T & value);
    void Pop();
    int Size();
    const T & Min();
    const T & Max();
    void Clear();
};

template <class T>
Stack<T>::Stack() {
    buffer_ = nullptr;
    size_ = 0;
}

template <class T>
Stack<T>::Stack(int n,
                const T & data) {
    size_ = 0;
    if (n <= MAX_SIZE) {
        buffer_ = new Node[MAX_SIZE];
        for (int i = 0; i <n; ++i) {
            buffer_[i].value = data;
            buffer_[i].max = data;
            buffer_[i].min = data;
            ++size_;
        }
    } else {
        std::cout << "Stack Overflow" <<std::endl;
    }
}

template <class T>
void Stack<T>::Clear() {
    size_ = 0;
    delete[] buffer_;
    buffer_ = nullptr;
}

template <class T>
void Stack<T>::Push(const T & data) {
    if (buffer_ == nullptr) {
        buffer_ = new Node[MAX_SIZE];
    }
    if (size_>= MAX_SIZE) {
        std::cout << "Stack Overflow" <<std::endl;
    } else {
        ++size_;
        buffer_[size_ - 1].value = data;
        if (size_ - 1 == 0) {
            buffer_[size_ - 1].max = data;
            buffer_[size_ - 1].min = data;
        } else {
            if (data>= buffer_[size_ - 2].max) {
                buffer_[size_ - 1].max = data;
            } else {
                buffer_[size_ - 1].max = buffer_[size_ - 2].max;
            }
            if (data <= buffer_[size_ - 2].min) {
                buffer_[size_ - 1].min = data;
            } else {
                buffer_[size_ - 1].min = buffer_[size_ - 2].min;
            }
        }
    }
}

template <class T>
const T & Stack<T>::Top() {
    if (size_ == 0) {
        return NULL;
    } else {
        return buffer_[size_ - 1].value;
    }
}

template <class T>
void Stack<T>::Pop() {
    if (size_ != 0) {
        --size_;
    } else {
        std::cout << "Empty stack" <<std::endl;
    }
}

template <class T>
int Stack<T>::Size() {
    return size_;
}

template <class T>
const T & Stack<T>::Min() {
    return buffer_[size_ - 1].min;
}

template <class T>
const T & Stack<T>::Max() {
    return buffer_[size_ - 1].max;
}

template <class T>
bool Stack<T>::Empty() {
    return size_ == 0;
}

#endif
