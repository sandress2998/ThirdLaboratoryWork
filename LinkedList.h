#pragma once

#include <iostream>
#include <stdexcept>
#include "Sequence.h"
/// Functionally complements ListSequence

template <typename T>
class DynamicArray;

template <typename T>
class Node {
public:
    Node* next;
    T value;
    Node(): next(nullptr) {}
    Node(T value): next(nullptr), value(value) {}
};

template <typename T>
class LinkedList {
private:
    int size = 0;
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;

    // метод для получения полного доступа к i-ому Node. Метод константный, так как используется в константной функции []
    Node<T>& getNode(int index) const {
        if (index < 0 || index >= size) throw std::out_of_range("The entered index is out of range.\n");
        if (head == nullptr) throw std::out_of_range("There was a request to get an element from the empty collection.\n");
        Node<T>* bufNode = head;
        for (int i = 0; i < index; ++i) {
            bufNode = bufNode->next;
        }
        return *bufNode;
    }

    void deleteList() {
        Node<T>* bufNode = head;
        while (bufNode != nullptr) {
            bufNode = bufNode->next;
            delete head;
            head = bufNode;
        }
        delete head;
    }

public:
    LinkedList(const T* items, int size) {
        if (size < 0) throw std::out_of_range("Entered invalid size.\n");
        for (int i = 0; i < size; ++i){
            append(items[i]);
        }
    }

    LinkedList(const Sequence<T>& other) {
        for (int i = 0; i < other.getLength(); ++i) {
            append(other.get(i));
        }
    }

    LinkedList() {}

    LinkedList(const LinkedList<T>& other) {
        for (int i = 0; i < other.getLength(); ++i) {
            append(other[i]);
        }
    }

    LinkedList(int size) {
        if (size < 0) throw std::out_of_range("Entered invalid size.\n");
        if (size > 0) {
            head = new Node<T>;
            tail = head;
        }
        for (int i = 1; i < size; ++i) {
            tail->next = new Node<T>;
            tail = tail->next;
        }
        this->size = size;
    }

    // сделать конструктор LinkedList(const DynamicArray<T>& other) не получится, т.к. файлы LinkedList.h и DynamicArray.h будут содержать друг друга

    ~LinkedList() {
        deleteList();
    }

    int getLength() const {
        return size;
    }

    T& operator[](int index) {
        // getNode(index) выбросит исключение
        return getNode(index).value;
    }

    const T& operator[](int index) const {
        // getNode(index) выбросит исключение
        return  getNode(index).value;
    }

    // Переделано
    LinkedList<T>& operator=(const LinkedList<T>& other) {
        // сначала удаляем все элементы
        deleteList();
        // заново создаем все элементы
        head = nullptr;
        tail = nullptr;
        size = 0;
        Node<T>* bufNode;
        if (other.getLength() != 0) {
            bufNode = &other.getNode(0);
        }
        for (int i = 0; i < other.getLength(); ++i) {
            this->append(bufNode->value);
            bufNode = bufNode->next;
        }
        return (*this);
    }

    const T& getFirst() const {
        if (head == nullptr) throw std::out_of_range("There was a request to get an element from the empty collection.\n");
        return head->value;
    }

    const T& getLast() const {
        if (head == nullptr) throw std::out_of_range("There was a request to get an element from the empty collection.\n");
        return tail->value;
    }

    const T& get(int index) const {
        return (*this)[index];
    }

    void set(int index, const T& value) {
        // конструкция (*this)[index] выбросывает исключение
        (*this)[index] = value;
    }

    void append(const T& item) {
        if (size == 0) {
            head = new Node<T>(item);
            tail = head;
        } else {
            tail->next = new Node<T>(item);
            tail = tail->next;
        }
        ++size;
    }

    void prepend(const T& item) { // добавляет элемент в начало списка
        if (size == 0) {
            head = new Node<T>(item);
            tail = head;
        } else {
            Node<T>* nodeBuf = head;
            head = new Node<T>(item);
            head->next = nodeBuf;
        }
        ++size;
    }

    void insertAt(int index, const T& item) { // вставляет элемент в заданную позицию
        if (index < 0 || index > size) throw std::out_of_range("The entered index is out of range.\n");
        if (index == 0) {
            prepend(item);
        } else if (index == size) {
            append(item);
        } else {
            Node<T>* bufNode = new Node<T>(item);
            bufNode->next = &getNode(index);
            getNode(index - 1).next = bufNode;
            ++size;
        }
    }

    LinkedList<T>* concat(const LinkedList<T>* other) const { // сцепляет два списка
        LinkedList<T>* result = new LinkedList<T>;
        Node<T>* bufNode;
        if (getLength() != 0) {
            bufNode = &getNode(0);
        }
        for (int i = 0; i < getLength(); ++i) {
            result->append(bufNode->value);
            bufNode = bufNode->next;
        }
        if (other->getLength() != 0) {
            bufNode = &other->getNode(0);
        }
        for (int j = 0; j < other->getLength(); ++j) {
            result->append(bufNode->value);
            bufNode = bufNode->next;
        }
        return result;
    }

    LinkedList<T>* getSubsequence(int startIndex, int endIndex) const {
        if (startIndex > endIndex || startIndex < 0 || endIndex >= this->getLength()) throw std::out_of_range("Entered indices are out of range.\n");
        LinkedList<T>* result = new LinkedList<T>;
        Node<T>* bufNode = &getNode(startIndex);
        for (int i = startIndex; i <= endIndex; ++i) {
            result->append(bufNode->value);
            bufNode = bufNode->next;
        }
        return result;
    }

    friend std::ostream& operator << (std::ostream& os, const LinkedList<T>& other) {
        int i = 0;
        Node<T>* bufNode;
        if (other.getLength() != 0) {
            bufNode = &other.getNode(0);
        }
        for (; i < other.getLength(); ++i) {
            os << bufNode->value << " ";
            bufNode = bufNode->next;
        }
        os << "\n";
        return os;
    }
};
