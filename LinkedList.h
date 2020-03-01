//
// Created by Anxin Guo on 2/18/20.
// Homemade linked lists. Size type is int.
//

#ifndef MYLIB_LINKEDLIST_H
#define MYLIB_LINKEDLIST_H

using uint = unsigned int;

//************************************************************
//Singly linked list
//************************************************************

//Singly linked list's helper struct
template <typename T>
struct SNode {
    SNode(T car, SNode* cdr);

    T car{};
    SNode* cdr{};
};

template<typename T>
SNode<T>::SNode(T car, SNode* cdr) {
    this->car = car;
    this->cdr = cdr;
}

//************************************************************
//Singly linked list. Size variable is unsigned int.
template <typename T> class SLL {
private:
    uint len{0};
    SNode<T> *st{}, *ed{};

public:
    ~SLL<T>();

    uint size();
    T front();
    T back();
    void insert(uint ind, T value);
    void erase(uint ind);
    void push_front(T value);
    void pop_front();
    uint find(T value);
};

template<typename T>
uint SLL<T>::size() {
    return len;
}

template<typename T>
T SLL<T>::front() {
    return &st->car;
}

template<typename T>
T SLL<T>::back() {
    return &ed->car;
}

template<typename T>
void SLL<T>::insert(uint ind, T value) {
    if (!ind) {
        auto* new_node = new SNode<T>(value, st);
        st = new_node;
        if (len == 0)
            ed = st;
    } else if (ind == len) {
        ed->cdr = new SNode<T>(value, nullptr);
    } else {
        auto* cur = st;
        while (ind-- > 1) { cur = cur->cdr; }
        auto* new_node = new SNode<T>(value, cur->cdr);
        cur->cdr = new_node;
    }
    len++;
}


template<typename T>
void SLL<T>::erase(uint ind) {
    if (!ind) {
        auto* temp = st;
        st = st->cdr;
        delete temp;
    } else {
        auto* cur = st;
        while (ind-- > 1) { cur = cur->cdr; }
        auto* temp = cur->cdr;
        cur->cdr = cur->cdr->cdr;
        delete temp;
    }
    len--;
}

template<typename T>
void SLL<T>::push_front(T value) {
    insert(0, value);
}

template<typename T>
void SLL<T>::pop_front() {
    erase(0);
}


template<typename T>
uint SLL<T>::find(T value) {
    uint ind = 0;
    auto* cur = st;
    while (cur != nullptr) {
        if (cur->car == value)
            return ind;
        cur = cur->cdr;
        ind++;
    }
    return ind;
}

template<typename T>
SLL<T>::~SLL<T>() {
    auto* cur = st;
    while (cur != nullptr) {
        auto* temp = cur->cdr;
        delete cur;
        cur = temp;
    }
}

//************************************************************
//Doubly linked list
//************************************************************
//Doubly linked list's helper struct
template <typename T> struct DNode {
    DNode(T car, DNode *prev, DNode *next);

    T car{};
    DNode *prev{}, *next{};
};

template<typename T>
DNode<T>::DNode(T car, DNode *prev, DNode *next) {
    this->car = car;
    this->prev = prev;
    this->next = next;
}

//************************************************************
//Doubly linked list
template <typename T> class DLL {
private:
    uint len{0};

public:
    DNode<T> *st{}, *ed{};

    ~DLL<T>();

    uint size();
    T front();
    T back();
    void insert(uint ind, T value);
    void erase(uint ind);
    void push_front(T value);
    void pop_front();
    void push_back(T value);
    void pop_back();
    uint find(T value);
};

template<typename T>
uint DLL<T>::size() {
    return len;
}

template<typename T>
T DLL<T>::front() {
    return &st->car;
}

template<typename T>
T DLL<T>::back() {
    return &ed->car;
}

//TODO
template<typename T>
void DLL<T>::insert(uint ind, T value) {
    if (!ind) {
        auto* new_node = new DNode<T>(value, nullptr, st);
        if (st) st->prev = new_node;
        st = new_node;
        if (len == 0)
            ed = st;
    } else if (ind == len) {//there's at least one element
        ed->next = new DNode<T>(value, ed, nullptr);
        ed = ed->next;
    } else {
        auto* cur = st;
        while (ind-- > 1) { cur = cur->next; }
        auto* new_node = new DNode<T>(value, cur, cur->next);
        cur->next->prev = new_node;
        cur->next = new_node;
    }
    len++;
}

template<typename T>
void DLL<T>::erase(uint ind) {
    if (!ind) {
        auto* temp = st;
        st = st->next;
        st->prev = nullptr;
        delete temp;
    } else if (ind == len - 1) {
        auto* temp = ed;
        ed = ed->prev;
        ed->next = nullptr;
        delete temp;
    } else {
        auto* cur = st;
        while (ind-- > 1) { cur = cur->next; }
        auto* temp = cur->next;
        cur->next = cur->next->next;
        cur->next->prev = cur;
        delete temp;
    }
    len--;
}

template<typename T>
uint DLL<T>::find(T value) {
    uint ind = 0;
    auto* cur = st;
    while (cur != nullptr) {
        if (cur->car == value)
            return ind;
        cur = cur->next;
        ind++;
    }
    return ind;
}

template<typename T>
DLL<T>::~DLL<T>() {
    auto* cur = st;
    while (cur != nullptr) {
        auto* temp = cur->next;
        delete cur;
        cur = temp;
    }
}

template<typename T>
void DLL<T>::push_front(T value) {
    insert(0, value);
}

template<typename T>
void DLL<T>::pop_front() {
    erase(0);
}

template<typename T>
void DLL<T>::push_back(T value) {
    insert(len - 1, value);
}

template<typename T>
void DLL<T>::pop_back() {
    erase(len - 1);
}

long long euclid(long long x, long long y);

#endif //MYLIB_LINKEDLIST_H
