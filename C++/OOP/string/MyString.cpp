#include "MyString.h"

#include <iostream>
#include <cstddef>

typedef std::size_t size_t;

void MyString::CopyArray(const char * from, char * to) {
    if (from == nullptr) {
        return;
    }
    for (int j = 0; j < std::strlen(from); ++j) {
        to[j] = from[j];
    }
}

MyString::MyString() {
    buffer_ = nullptr;
    size_ = 0;
}

MyString::MyString(const int n,
                   const char symbol) {
    size_ = n;
    buffer_ = new char[n+1];
    for (int j = 0; j < n; ++j) {
        buffer_[j] = symbol;
    }
    buffer_[n]='\0';
}

MyString::MyString(const char * other) {
    
    if (other != nullptr) {
        buffer_ = new char[std::strlen(other)+1];
        CopyArray(other, buffer_);
        size_ = std::strlen(other);
        buffer_ [size_]='\0';
    } else {
        size_ = 0;
        buffer_ = nullptr;
    }
}

MyString::MyString(const MyString & other) {
    size_ = other.size_;
    buffer_ = new char[other.size_ + 1];
    CopyArray(other.buffer_, buffer_);
}

MyString::~MyString() {
    delete[] buffer_;
    buffer_ = nullptr;
    size_ = 0;
}

size_t MyString::Size() const {
    return size_;
}

bool MyString::Compare(const MyString & other) const {
    return strcmp(buffer_, other.buffer_) < 0;
}

void MyString::ToUpper() {
    for (int j = 0; j < size_; ++j) {
        buffer_[j] = std::toupper(buffer_[j]);
    }
}

void MyString::ToLower() {
    for (int j = 0; j < size_; ++j) {
        buffer_[j] = std::tolower(buffer_[j]);
    }
}

void MyString::Capitalize() {
    ToLower();
    buffer_[0] = std::toupper(buffer_[0]);
    for (int j = 1; j < size_; ++j) {
        if (buffer_[j - 1] == ' ') {
            buffer_[j] = std::toupper(buffer_[j]);
        }
    }
}

bool MyString::IsSubstring(const MyString & other) const {
    if (other.size_ < size_) {
        return false;
    }
    for (int startPosInOther = 0; startPosInOther < other.size_ - size_ + 1; ++startPosInOther) {
        bool otherContainsThis = true;
        for (int charIndexInThis = 0; charIndexInThis < size_; ++charIndexInThis) {
            if (other.buffer_[startPosInOther + charIndexInThis] != buffer_[charIndexInThis]) {
                otherContainsThis = false;
            }
        }
        if (otherContainsThis) {
            return true;
        }
    }
    return false;
}

void MyString::Print() const {
    std::cout << ((buffer_ == nullptr) ? "" : buffer_) << std::endl;
}

void MyString::Read() {
    int inputSize = 256;
    char * data = new char[inputSize];
    std::cin.getline(data, inputSize+1);
    delete[] buffer_;
    buffer_ = new char[std::strlen(data)+1];
    CopyArray(data, buffer_);
    size_ = std::strlen(data);
    buffer_[size_] = '\0';
}

char & MyString::At(const int index) const {
    if (index >= size_) {
        std::cout << "error" << std::endl;
    }
    return buffer_[index];
}

void MyString::Reverse() {
    for (int j = 0; j < size_ / 2; ++j) {
        char temp = buffer_[j];
        buffer_[j] = buffer_[size_ - j - 1];
        buffer_[size_ - j - 1] = temp;
    }
}

void MyString::Clear() {
    delete[] buffer_;
    buffer_ = nullptr;
    size_ = 0;
}

void MyString::Append(const MyString & other) {
    char * temp = new char [size_ + 1];
    CopyArray(buffer_, temp);
    delete[] buffer_;
    buffer_ = new char [size_ + other.size_ + 1];
    CopyArray(temp, buffer_);
    for (int j = size_; j < other.size_ + size_; ++j) {
        buffer_[j] = other.buffer_[j - size_];
    }
    size_ += other.size_;
    buffer_[size_]='\0';
    delete[] temp;
}

void MyString::PushBack(const char symbol) {
    char * temp = new char [size_ + 1];
    CopyArray(buffer_, temp);
    delete[] buffer_;
    buffer_ = new char [size_ + 1 + 1];
    CopyArray(temp, buffer_);
    buffer_[size_] = symbol;
    ++size_;
    buffer_[size_]='\0';
    delete[] temp;
}

MyString MyString::Concatenate(const MyString & first,
                               const MyString & second) {
    MyString s = first;
    s.Append(second);
    return s;
}
