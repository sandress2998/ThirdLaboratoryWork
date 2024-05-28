#pragma once

#include <stdexcept>
#include "MutableSequence.h"
#include "Sequence.h"
#include "LinkedList.h"
#include "DynamicArray.h"

template <typename T>
class MutableListSequence: public MutableSequence<T> {
private:
    LinkedList<T>* list;

public:
    MutableListSequence(const T* items, int size): list(new LinkedList<T>(items, size)) {}
    MutableListSequence(): list(new LinkedList<T>) {}
    MutableListSequence(int size): list(new LinkedList<T>(size)) {}
    MutableListSequence(const MutableListSequence<T>& other): list(new LinkedList<T>(*other.list)) {}
    MutableListSequence(const Sequence<T>& other): list(new LinkedList<T>(other)) {}
    MutableListSequence(const LinkedList<T>& other): list(new LinkedList<T>(other)) {}
    MutableListSequence(const DynamicArray<T>& other): list(new LinkedList<T>) {
        for (int i = 0; i < other.getSize(); ++i) {
            append(other[i]);
        }
    }

    ~MutableListSequence() override {
        delete list;
    }

    T& operator [] (int index) override {
        return (*list)[index];
    }

    const T& operator [] (int index) const override {
        return (*list)[index];
    }

    // Переделано
    MutableListSequence<T>& operator=(const MutableListSequence<T>& other) {
        *list = *other.list;
        return *this;
    }

    const T& getFirst() const override {
        return list->getFirst();
    }

    const T& getLast() const override {
        return list->getLast();
    }

    const T& get(int index) const override {
        return (*list)[index];
    }

    void set(int index, const T& value) override {
        return list->set(index, value);
    }

    int getLength() const override {
        return list->getLength();
    }

    void append(const T& item) override {
        list->append(item);
    }

    void prepend(const T& item) override {
        list->prepend(item);
    }

    void insertAt(int index, const T& item) override {
        list->insertAt(index, item);
    }

    MutableListSequence<T>* getSubsequence(int startIndex, int endIndex) const override {
        if (startIndex > endIndex || startIndex < 0 || endIndex >= this->getLength()) throw std::out_of_range("Entered indices are out of range.\n");
        return new MutableListSequence<T>(*this->list->getSubsequence(startIndex, endIndex));
    }

    MutableListSequence<T>* concat(const Sequence<T>& other) const override {
        LinkedList<T> bufList(other);
        return new MutableListSequence<T>(*list->concat(&bufList));
    }
};
