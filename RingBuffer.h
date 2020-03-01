//
// Created by Anxin Guo on 2/25/20.
//

#ifndef MYLIB_RINGBUFFER_H
#define MYLIB_RINGBUFFER_H

#include <iostream>
#include <initializer_list>
#include <vector>

using uint = unsigned int;

///
/// Ring Buffer class
///
template <typename T>
class RingBuffer {
protected:
    /// Fields

    std::vector<T> data_;
    // Size is the number of elements; capacity is the maximum length.
    uint st_{}, size_{}, capacity_{};

    /// Helpers
    void resize() {
        reserve(2 * capacity_ + 1);
    }

public:
    using value_type = T;

    /// Constructors & destroyer

    // Empty and size = 0.
    RingBuffer() {
        st_ = size_ = capacity_ = 0;
    }
    // Empty ring buffer with size n.
    explicit RingBuffer(uint n) {
        data_ = std::vector<T>(n);
        st_ = size_ = 0;
        capacity_ = n;
    }
    // Using iterators.
    template <typename InputIterator> RingBuffer(InputIterator first, InputIterator last) {
        st_ = 0;
        size_ = capacity_ = last - first;
        data_ = std::vector<T>(first, last);
    }
    // Using initializer_list
    RingBuffer(std::initializer_list<T> list) {
        st_ = 0;
        size_ = capacity_ = list.size();
        data_ = std::vector<T>(list.begin(), list.end());
    }

    /// Accessors

    uint st() const { return st_; }
    uint ed() const { return (st_ + size_) % capacity_; }
    uint size() const { return size_; }
    bool empty() const { return size_ == 0; }
    uint capacity() const { return capacity_; }
    T back() const { return data_[(st_ + size_ - 1) % capacity_]; }
    T front() const { return data_[st_]; }
    T operator[](uint ind) const {
        if (ind >= size_)
            throw std::range_error("RingBuffer.operator[]: out of bounds\n");
        return data_[(st_ + ind) % capacity_];
    }

    /// Modifiers

    void push_back(T element) {
        if (size_ == capacity_)
            resize();

        data_[ed()] = element;
        ++size_;
    }
    void pop_back() {
        --size_;
    }
    void push_front(T element) {
        if (size_ == capacity_)
            resize();

        st_ = (st_ + capacity_ - 1) % capacity_;
        data_[st_] = element;
        ++size_;
    }
    void pop_front() {
        st_ = (st_ + 1) % capacity_;
        --size_;
    }
    // Enlarge the size of the array to "size".
    void reserve(uint size) {
        if (size < size_)
            throw std::logic_error("RingBuffer.reserve: size too small\n");

        std::vector<T> temp(size);
        for (uint i = 0; i < size_; i++)
            temp[i] = data_[(st_ + i) % capacity_];
        st_ = 0;
        capacity_ = size;
        data_ = temp;
    }
    void clear() {
        size_ = 0;
    }

    /// Iterator class

    class iterator;
    //friend iterator;

    iterator begin() { return iterator(st_, *this); }
    iterator end() { return iterator(ed(), *this); }

    /// Operators

    bool operator==(RingBuffer<T> other) {
        if (size_ != other.size_)
            return false;
        for (uint i = 0; i < size_; i++) {
            if ((*this)[i] != other[i])
                return false;
        }
        return true;
    }
    bool operator!=(RingBuffer<T> other) {
        return !(*this == other);
    }
};

template <typename T>
class RingBuffer<T>::iterator
        : public std::iterator<std::input_iterator_tag, T> {
private:
    uint current_; // The ACTUAL index number of array.
    RingBuffer<T>& super_; // The containing RingBuffer.
    friend RingBuffer<T>;

// Constructor; points to the current_th entry.
    iterator(uint ind, RingBuffer<T>& rb)
    : current_(ind % rb.capacity())
    , super_(rb)
        { }
public:
    T operator*() const {
        return super_.data_[current_];
    }
    T*operator->() const {
        return &super_.data_[current_];
    }
    iterator& operator++() {
        current_ = (current_ + 1) % super_.capacity_;
        return *this;
    }
    iterator& operator--() {
        current_ = (current_ + capacity_ - 1) % super_.capacity_;
        return *this;
    }
    iterator operator++(int) {
        iterator temp(*this);
        ++*this;
        return temp;
    }
    iterator operator--(int) {
        iterator temp(*this);
        --*this;
        return temp;
    }
    bool operator==(iterator other) const {
        return other.current_ == current_ && other.super_ == super_;
    }
    bool operator!=(iterator other) const {
        return !(*this == other);
    }
};

template <typename T>
std::ostream& operator<<(std::ostream & os, RingBuffer<T> rb) {
    for (uint i = 0; i < rb.size(); i++)
        os << rb[i] << " ";
    return os;
}

#endif //MYLIB_RINGBUFFER_H
