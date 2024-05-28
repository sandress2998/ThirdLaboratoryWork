#pragma once

#include <stdexcept>
#include "ImmutableSequence.h"
#include "Sequence.h"
#include "LinkedList.h"
#include "DynamicArray.h"

template <typename T>
class ImmutableListSequence: public ImmutableSequence<T> {
private:
    LinkedList<T>* list;
    ImmutableListSequence<T>* instance() const {
        return new ImmutableListSequence<T>(*this);
    }

public:
    ImmutableListSequence(const T* items, int size): list(new LinkedList<T>(items, size)) {}
    ImmutableListSequence(): list(new LinkedList<T>) {}
    ImmutableListSequence(int size): list(new LinkedList<T>(size)) {}
    ImmutableListSequence(const ImmutableListSequence<T>& other): list(new LinkedList<T>(*other.list)) {}
    ImmutableListSequence(const Sequence<T>& other): list(new LinkedList<T>(other)) {}
    ImmutableListSequence(const LinkedList<T>& other): list(new LinkedList<T>(other)) {}
    ImmutableListSequence(const DynamicArray<T>& other) {
        for (int i = 0; i < other.getLength(); ++i) {
            list->append(other.get(i));
        }
    }

    ~ImmutableListSequence() override {
        delete list;
    }

    const T& operator[] (int index) const override {
        return (*list)[index];
    }

    ImmutableListSequence<T>& operator=(const ImmutableListSequence<T>& other) {
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

    int getLength() const override {
        return list->getLength();
    }

    ImmutableListSequence<T>* append(const T& item) const override {
        ImmutableListSequence<T>* result = instance();
        result->list->append(item);
        return result;
    }

    ImmutableListSequence<T>* prepend(const T& item) const override {
        ImmutableListSequence<T>* result = instance();
        result->list->prepend(item);
        return result;
    }

    ImmutableListSequence<T>* insertAt(int index, const T& item) const override {
        if (index > getLength() || index < 0) throw std::out_of_range("The entered index is out of range.\n");
        ImmutableListSequence<T>* result = instance();
        result->list->insertAt(index, item);
        return result;
    }

    ImmutableListSequence<T>* set(int index, const T& item) const override {
        if (index >= getLength() || index < 0) throw std::out_of_range("The entered index is out of range.\n");
        ImmutableListSequence<T>* result = instance();
        result->list->set(index, item);
        return result;
    }

    ImmutableListSequence<T>* getSubsequence(int startIndex, int endIndex) const override {
        if (startIndex > endIndex || startIndex < 0 || endIndex >= this->getLength()) throw std::out_of_range("Entered indices are out of range.\n");
        ImmutableListSequence<T>* result = new ImmutableListSequence<T>;
        for (int i = startIndex; i <= endIndex; ++i) {
            result->list->append(get(i));
        }
        return result;
    }

    ImmutableListSequence<T>* concat(const Sequence<T>& other) const override {
        ImmutableListSequence<T>* result = instance();
        for (int i = 0; i < other.getLength(); ++i) {
            result->list->append(other.get(i));
        }
        return result;
    }
};


