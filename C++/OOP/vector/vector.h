#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>
#include <limits>

template <class T>
void SwapArrays (T*& a, T*& b) {
    T* swap = a;
    a = b;
    b = swap;
    swap = nullptr;
}

template <class T>
void SwapValues (T& a, T& b) {
    T c(a);
    a = b;
    b = c;
}

template <class T>
void CopyArray(T* begin, T* end, T* to) {
    for (T* j = begin; j != end; ++j) {
        *to = *j;
        ++to;
    }
}

template <class T>
void FillArray(T* begin, T* end, T val) {
    for (T* j = begin; j != end; ++j) {
        *j = val;
    }
}

template <class T>
class Vector {
    T* buffer_;
    size_t size_;
    size_t maxSize_ =  std::numeric_limits<size_t>::max();
    size_t capacity_;
    void Realloc(size_t newSize);
public:
    Vector();
    Vector(size_t size, T val = T());
    Vector(const Vector& other);
    Vector(const Vector&& other);
    ~Vector();
    size_t Size() const;
    size_t Capacity() const;
    size_t MaxSize() const;
    void Print();
    void ShrinkToFit();
    bool Empty() const;
    void Reserve(size_t size);
    void Resize(size_t size, const T& val = T());
    T At(size_t idx) const;
    T& At(size_t idx);
    T Front() const;
    T& Front();
    T Back() const;
    T& Back();
    T* Data() const;
    void Assign(size_t size, const T& val);
    void PushBack(const T& val);
    void PopBack();
    void Insert(size_t position, const T& val, size_t size = 1);
    void Erase(size_t idx);
    void Erase(size_t first, size_t last);
    void Swap(Vector& other);
    void Clear();

    Vector operator=(const Vector& other) {
        if (this != &other) {
            delete[] buffer_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            try {
                buffer_ = new T[capacity_];
            } catch (std::bad_alloc& er) {
                std::cout << er.what() << std::endl;
            }
            CopyArray(other.buffer_, other.buffer_ + size_, buffer_);
        }
        return *this;
    }
    
    Vector operator=(const Vector&& other) {
        if (this != &other) {
            delete[] buffer_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            buffer_ = other.buffer_;
            other.buffer_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }
    
    T operator[](size_t idx) const;
    T& operator[](size_t idx);
    
    bool operator==(const Vector& other) const;
    bool operator!=(const Vector& other) const;
    bool operator<(const Vector& other) const;
    bool operator>(const Vector& other) const;
    bool operator>=(const Vector& other) const;
    bool operator<=(const Vector& other) const;
};

template <class T>
void Vector<T>::Realloc(size_t size) {
    if (size >= maxSize_) {
        throw std::length_error("");
    } else {
        T* new_buffer;
        try {
            new_buffer = new T[size];
        } catch (std::bad_alloc& er) {
            std::cout << er.what() << std::endl;
        }
        CopyArray(buffer_, buffer_ + size_, new_buffer);
        T* swap = buffer_;
        buffer_ = new_buffer;
        new_buffer = nullptr;
        delete[] swap;
    }
    capacity_ = size;
}


template <class T>
Vector<T>::Vector() {
    buffer_ = nullptr;
    size_= 0;
    capacity_ = 0;
}

template <class T>
Vector<T>::Vector(size_t size, T val) {
    size_= size;
    capacity_ = 2 * size_;
    try {
        buffer_ = new T[capacity_];
    } catch (std::bad_alloc& er) {
        std::cout << er.what() << std::endl;
    }
    FillArray(buffer_, buffer_ + size_, val);
}

template <class T>
Vector<T>::Vector(const Vector& other) {
    capacity_ = other.capacity_;
    size_= other.size_;
    try {
        buffer_ = new T[capacity_];
    } catch (std::bad_alloc& er) {
        std::cout << er.what() << std::endl;
    }
    CopyArray(other.buffer_, other.buffer_ + size_, buffer_);
}

template <class T>
Vector<T>::Vector(const Vector&& other) {
    capacity_ = other.capacity_;
    size_= other.size_;
    buffer_ = other.buffer_;
    other.buffer_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

template <class T>
Vector<T>::~Vector() {
    delete[] buffer_;
    buffer_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}

template <class T>
size_t Vector<T>::Size() const {
    return size_;
}

template <class T>
size_t Vector<T>::Capacity() const {
    return capacity_;
}

template <class T>
size_t Vector<T>::MaxSize() const {
    return maxSize_;
}

template <class T>
void Vector<T>::ShrinkToFit() {
    Realloc(size_);
}

template <class T>
bool Vector<T>::Empty() const {
    return size_ == 0;
}

template <class T>
void Vector<T>::Reserve(size_t size) {
    if (size > capacity_) {
        Realloc(size);
    }
}

template <class T>
void Vector<T>::Resize(size_t size, const T& val) {
    if (size > size_) {
        if (size > capacity_) {
            Realloc(size);
        }
        FillArray(buffer_ + size_, buffer_ + size, val);
        size_ = size;
    } else if (size < size_) {
        size_ = size;
    }
}

template <class T>
T Vector<T>::operator[](size_t idx) const {
    return buffer_[idx];
}

template <class T>
T& Vector<T>::operator[](size_t idx) {
    return buffer_[idx];
}

template <class T>
T Vector<T>::At(size_t idx) const {
    if (idx >= size_) {
        throw std::out_of_range("");
    }
    return buffer_[idx];
}

template <class T>
T& Vector<T>::At(size_t idx) {
    if (idx >= size_) {
        throw std::out_of_range("");
    }
    return buffer_[idx];
}

template <class T>
T Vector<T>::Front() const {
    return buffer_[0];
}

template <class T>
T& Vector<T>::Front() {
    return buffer_[0];
}

template <class T>
T Vector<T>::Back() const {
    return buffer_[size_ - 1];
}

template <class T>
T& Vector<T>::Back() {
    return buffer_[size_ - 1];
}

template <class T>
T* Vector<T>::Data() const {
    return buffer_;
}

template <class T>
void Vector<T>::Assign(size_t size, const T& val) {
    if (size > capacity_) {
        Realloc(size);
    }
    delete[] buffer_;
    try {
        buffer_ = new T[capacity_];
    } catch (std::bad_alloc& er) {
        std::cout << er.what() << std::endl;
    }
    size_ = size;
    FillArray(buffer_, buffer_ + size, val);
}

template <class T>
void Vector<T>::PushBack(const T& val) {
    if (size_ + 1 > capacity_) {
        Realloc(size_ * 2);
    }
    buffer_[size_] = val;
    ++size_;
}

template <class T>
void Vector<T>::PopBack() {
    if (size_ != 0) {
        --size_;
    }
}

template <class T>
void Vector<T>::Insert(size_t position, const T& val, size_t size) {
    if (size_ + size > capacity_) {
        Realloc(2 * (size_ > size ? size_ : size));
    }
    if (position == size_) {
         FillArray(buffer_ + position, buffer_ + size + position, val);
    } else {
        T* temp;
        try {
            temp = new T[size_ - position];
        } catch (std::bad_alloc& er) {
            std::cout << er.what() << std::endl;
        }
        CopyArray(buffer_ + position, buffer_ + size_, temp);
        FillArray(buffer_ + position, buffer_ + position + size, val);
        CopyArray(temp, temp + (size_ - position), buffer_ + position + size);
        delete[] temp;
    }
    size_ += size;
}

template <class T>
void Vector<T>::Erase(size_t idx) {
    if (idx == size_ - 1) {
        --size_;
    } else {
        T* temp;
        try {
            temp = new T[size_ - idx - 1];
        } catch (std::bad_alloc& er) {
            std::cout << er.what() << std::endl;
        }
        CopyArray(buffer_ + idx + 1, buffer_ + size_, temp);
        CopyArray(temp, temp + (size_ - idx - 1), buffer_ + idx);
        delete[] temp;
        --size_;
    }
}

template <class T>
void Vector<T>::Erase(size_t first, size_t last) {
    if (last == size_) {
        size_ -= (size_ - first);
    } else {
        T* temp;
        try {
            temp = new T[size_ - last + 1];
        } catch (std::bad_alloc& er) {
            std::cout << er.what() << std::endl;
        }
        CopyArray(buffer_ + last, buffer_ + size_, temp);
        CopyArray(temp, temp + (size_ - last + 1), buffer_ + first);
        delete[] temp;
        size_ -= (last - first);
    }
}

template <class T>
void Vector<T>::Swap(Vector& other) {
    SwapValues(size_, other.size_);
    SwapValues(capacity_, other.capacity_);
    SwapArrays(buffer_, other.buffer_);
}

template <class T>
void Vector<T>::Clear() {
    delete[] buffer_;
    try {
        buffer_ = new T[capacity_];
    } catch (std::bad_alloc& er) {
        std::cout << er.what() << std::endl;
    }
    size_ = 0;
}

template <class T>
void Vector<T>::Print() {
    if (size_ == 0) {
        std::cout << "\n";
    } else {
        for (int i = 0; i < size_; ++i) {
            std::cout << buffer_[i] << " ";
        }
        std::cout << std::endl;
    }
}

template <class T>
bool Vector<T>::operator==(const Vector<T>& other) const {
    if (size_ != other.size_) {
        return false;
    }
    for (int i = 0; i < size_; ++i) {
        if (buffer_[i] != other[i]) {
            return false;
        }
    }
    return true;
}

template <class T>
bool Vector<T>::operator!=(const Vector<T>& other) const {
    return !(*this == other);
}

template <class T>
bool Vector<T>::operator<(const Vector<T>& other) const {
    size_t size = size_ < other.size_ ? size_ : other.size_;
    for (int i = 0; i < size; ++i) {
        if (buffer_[i] != other[i]) {
            return buffer_[i] < other[i];
        }
    }
    return false;
}

template <class T>
bool Vector<T>::operator>(const Vector<T>& other) const {
    return other < *this;
}

template <class T>
bool Vector<T>::operator>=(const Vector<T>& other) const {
    return !(*this < other);
}


template <class T>
bool Vector<T>::operator<=(const Vector<T>& other) const {
    return !(*this > other);
}

#endif

