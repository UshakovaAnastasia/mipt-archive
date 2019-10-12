#include "MyString.h"

#include <iostream>
#include <algorithm>
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

size_t MyString::Max(const size_t a, const size_t b) const {
    size_t result = std::max(a, b);
    return result;
}

MyString::MyString() {
    buffer_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}

MyString::MyString(MyString && other) {
    buffer_ = other.buffer_;
    size_ = other.size_;
    other.size_ = 0;
    capacity_ = other.capacity_;
    other.capacity_ = 0;
    other.buffer_ = nullptr;
} 

MyString::MyString(const int n,
                   const char symbol) {
    size_ = n;
    capacity_ = n * 2;
    buffer_ = new char[n * 2];
    for (int j = 0; j < n; ++j) {
        buffer_[j] = symbol;
    }
    buffer_[n]='\0';
}

MyString::MyString(const char * other) {
    
    if (other != nullptr) {
        size_ = std::strlen(other);
        capacity_ = 2 * size_;
        buffer_ = new char[capacity_];
        CopyArray(other, buffer_);
        buffer_ [size_]='\0';
    } else {
        size_ = 0;
        buffer_ = nullptr;
        capacity_ = 0;
    }
}

MyString::MyString(const MyString & other) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    buffer_ = new char[capacity_];
    CopyArray(other.buffer_, buffer_);
}

MyString::~MyString() {
    Clear();
}

size_t MyString::Size() const {
    return size_;
}

int MyString::Capacity() const {
    return capacity_;
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
    std::cin.getline(data, inputSize + 1);
    delete[] buffer_;
    size_ = std::strlen(data);
    capacity_ = 2 * std::strlen(data);
    buffer_ = new char[capacity_];
    CopyArray(data, buffer_);
    buffer_[size_] = '\0';
    delete[] data;
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
    capacity_ = 0;
}

void MyString::Append(const MyString & other) {
    if (capacity_ <= size_ + other.size_) {
        Realloc(2 * Max(size_, other.size_));
        capacity_ = 2 * Max(size_, other.size_);
    }
    for (int j = size_; j < other.size_ + size_; ++j) {
        buffer_[j] = other.buffer_[j - size_];
    }
    size_ += other.size_;
    buffer_[size_]='\0';
}

void MyString::PushBack(const char symbol) {
    if (capacity_ < size_ + 1) {
        Realloc(2 * Max(size_, 1));
        capacity_ = 2 * Max(size_, 1);
    }
    buffer_[size_] = symbol;
    ++size_;
    buffer_[size_]='\0';
}

MyString MyString::Concatenate(const MyString & first,
                               const MyString & second) {
    MyString s = first;
    s.Append(second);
    return s;
}

void MyString::ShrinkToFit() {
    Realloc(size_ + 1);
}

void MyString::Realloc(size_t size) {
    if (size <= size_) {
        std::cout << "not enough capacity" << std::endl;
    } else {
        char * temp = new char[size_ + 1];
        CopyArray(buffer_, temp);
        delete[] buffer_;
        buffer_ = new char[size];
        CopyArray(temp, buffer_);
        delete[] temp;
    }
    buffer_[size_] = '\0';
    capacity_ = size;
}

void operator+=(MyString & lhs, const MyString & rhs) {
    lhs.Append(rhs);
}

MyString operator*(const MyString & string, const int multiplier) {
    MyString s = string;
    for (int j = 1; j < multiplier; ++j) {
        if (std::strlen(s.buffer_) + s.size_ >= s.capacity_) {
            s.capacity_ *= 2;
            s.Realloc(s.capacity_);
        }
        for (int i = j * s.size_; i < s.size_ + j * s.size_; ++i) {
            s.buffer_[i] = s.buffer_[i - j * s.size_];
        }
    }
    s.size_ *= multiplier;
    
    return s;
}

bool operator==(const MyString & lhs, const MyString & rhs) {
    return strcmp(lhs.buffer_, rhs.buffer_) == 0;
}

bool operator<(const MyString & lhs, const MyString & rhs) {
    return lhs.Compare(rhs);
}

bool operator<=(const MyString & lhs, const MyString & rhs) {
    return ((lhs.Compare(rhs)) || (strcmp(lhs.buffer_, rhs.buffer_) == 0));
}

bool operator>(const MyString & lhs, const MyString & rhs) {
    return !(lhs.Compare(rhs) || (strcmp(lhs.buffer_, rhs.buffer_) == 0));
}

bool operator>=(const MyString & lhs, const MyString & rhs) {
    return ((!lhs.Compare(rhs)) || (strcmp(lhs.buffer_, rhs.buffer_) == 0));
}


std::istream& operator>>(std::istream& is, MyString& string) {
    int inputSize = 256;
    char * data = new char[inputSize];
    is.getline(data, inputSize + 1);
    delete[] string.buffer_;
    string.size_ = std::strlen(data);
    string.capacity_ = 2 * std::strlen(data);
    string.buffer_ = new char[string.capacity_];
    string.CopyArray(data, string.buffer_);
    string.buffer_[string.size_]='\0';
    delete[] data;
    return is;
}

std::ostream& operator<<(std::ostream& os, const MyString& string) {
    os << (string.buffer_ == nullptr ? "" : string.buffer_);
    return os;
}

MyString operator*(const int multiplier, const MyString& string) {
    return string * multiplier;
}

MyString operator+(const MyString& lhs, const MyString& rhs) {
    return MyString::Concatenate(lhs, rhs);
}

