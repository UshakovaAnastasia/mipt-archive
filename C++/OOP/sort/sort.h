#ifndef SORT_H
#define SORT_H

#include <iostream>
#include <iterator>

template <class T>
void swap_values(T& a, T& b) {
    T c(a);
    a = b;
    b = c;
}

template<class RandIt>
RandIt partition(RandIt left, RandIt right, std::random_access_iterator_tag) {
    RandIt from_left_to_right = left - 1;
    RandIt from_right_to_left = right;
    for(;;) {
        for(;;) {
            ++from_left_to_right;
            if (!(*from_left_to_right < *left)) {
                break;
            }
        }
        for(;;) {
            --from_right_to_left;
            if (!(*from_right_to_left > *left)) {
                break;
            }
        }
        if (from_left_to_right >= from_right_to_left) {
            return from_right_to_left;
        }
        swap_values(*from_left_to_right, *from_right_to_left);
    }
}

template<class RandIt>
void Sort(RandIt begin, RandIt end, std::random_access_iterator_tag) {
    if (begin < end - 1) {
        RandIt split = partition<RandIt>(begin, end, typename std::iterator_traits<RandIt>::iterator_category());
        Sort<RandIt>(begin, split + 1, typename std::iterator_traits<RandIt>::iterator_category());
        Sort<RandIt>(split + 1, end, typename std::iterator_traits<RandIt>::iterator_category());
    }
}

template<class BidirectIt>
BidirectIt partition(BidirectIt left, BidirectIt right, std::bidirectional_iterator_tag) {
    BidirectIt from_left_to_right = --left;
    ++left;
    BidirectIt from_right_to_left = right;
    for(;;) {
        for(;;) {
            ++from_left_to_right;
            if (!(*from_left_to_right < *left)) {
                break;
            }
        }
        for(;;) {
            --from_right_to_left;
            if (!(*from_right_to_left > *left)) {
                break;
            }
        }
        if (from_left_to_right == from_right_to_left) {
            return from_right_to_left;
        }
        ++from_right_to_left;
        if (from_left_to_right == from_right_to_left) {
            return --from_right_to_left;
        }
        --from_right_to_left;
        swap_values(*from_left_to_right, *from_right_to_left);
    }
}

template<class BidirectIt>
void Sort(BidirectIt begin, BidirectIt end, std::bidirectional_iterator_tag) {
    if (++begin != end) {
        BidirectIt split = partition<BidirectIt>(--begin, end, typename std::iterator_traits<BidirectIt>::iterator_category());
        Sort<BidirectIt>(begin, ++split, typename std::iterator_traits<BidirectIt>::iterator_category());
        Sort<BidirectIt>(split, end, typename std::iterator_traits<BidirectIt>::iterator_category());
    }
}


template<class It>
void Sort(It begin, It end, std::forward_iterator_tag) {
    bool swap = false;
    if (begin == end) {
        return;
    }
    It start = begin;
    while (start != end) {
        It next = start;
        ++next;
        if (next != end && *start > *next) {
            std::swap(*start, *next);
            swap = true;
        }
        ++start;
        if (start == end && swap) {
            swap = false;
            start = begin;
        }
    }
}

template<class It>
void Sort(It begin, It end, std::output_iterator_tag) {
    bool swap = false;
    if (begin == end) {
        return;
    }
    It start = begin;
    while (start != end) {
        It next = start;
        ++next;
        if (next != end && *start > *next) {
            std::swap(*start, *next);
            swap = true;
        }
        ++start;
        if (start == end && swap) {
            swap = false;
            start = begin;
        }
    }
}

template<class It>
void Sort(It begin, It end, std::input_iterator_tag) {
    bool swap = false;
    if (begin == end) {
        return;
    }
    It start = begin;
    while (start != end) {
        It next = start;
        ++next;
        if (next != end && *start > *next) {
            std::swap(*start, *next);
            swap = true;
        }
        ++start;
        if (start == end && swap) {
            swap = false;
            start = begin;
        }
    }
}

template<class Iterator>
void Sort(Iterator begin, Iterator end) {
    Sort<Iterator>(begin, end, typename std::iterator_traits<Iterator>::iterator_category());
}

#endif




