#pragma once

#include <stdexcept>
#include "Sequence.h"
#include "ImmutableSequence.h"
#include "DynamicArray.h"
#include "LinkedList.h"

template <typename T>
class ImmutableArraySequence: public ImmutableSequence<T> {
private:
    DynamicArray<T>* array;
    ImmutableArraySequence<T>* instance() const {
        return new ImmutableArraySequence<T>(*this);
    }

public:
    ImmutableArraySequence(const T* arrayToCopy, int size): array(new DynamicArray<T>(arrayToCopy, size)) {}
    ImmutableArraySequence(int size): array(new DynamicArray<T>(size)) {}
    ImmutableArraySequence(): array(new DynamicArray<T>(0)) {}
    ImmutableArraySequence(const LinkedList<T>& other): array(new DynamicArray<T>(other)) {}
    ImmutableArraySequence(const DynamicArray<T>& other): array(new DynamicArray<T>(other)) {}
    ImmutableArraySequence(const ImmutableArraySequence<T>& other): array(new DynamicArray<T>(*(other.array))) {}
    ImmutableArraySequence(const Sequence<T>& other): array(new DynamicArray<T>(other)) {}

    ~ImmutableArraySequence() override {
        delete array;
    }

    const T& operator[](int index) const override {
        return (*array)[index];
    }

    const T& getFirst() const override {
        return (*array)[0];
    }

    const T& getLast() const override {
        return (*array)[getLength() - 1];
    }

    const T& get(int index) const override {
        return (*array)[index];
    }

    int getLength() const override {
        return array->getSize();
    }

    ImmutableArraySequence<T>* append(const T& item) const override {
        ImmutableArraySequence<T>* result = new ImmutableArraySequence(getLength() + 1);
        for (int i = 0; i < getLength(); ++i) {
            result->array->set(i, (*this)[i]);
        }
        result->array->set(array->getSize(), item);
        return result;
    }

    ImmutableArraySequence<T>* prepend(const T& item) const override {
        ImmutableArraySequence<T>* result = instance();
        result->array->prepend(item);
        return result;
    }

    ImmutableArraySequence<T>* insertAt(int index, const T& item) const override {
        if (index > getLength() || index < 0) throw std::out_of_range("The entered index is out of range.\n");
        ImmutableArraySequence<T>* result = instance();
        result->array->insertAt(index, item);
        return result;
    }

    ImmutableArraySequence<T>* set(int index, const T& item) const override {
        if (index >= getLength() || index < 0) throw std::out_of_range("The entered index is out of range.\n");
        ImmutableArraySequence<T>* result = instance();
        result->array->set(index, item);
        return result;
    }

    ImmutableArraySequence<T>* getSubsequence(int startIndex, int endIndex) const override {
        if (startIndex < 0 || endIndex >= getLength() || startIndex > endIndex) throw std::out_of_range("Entered indices are out of range.\n");
        ImmutableArraySequence<T>* result = new ImmutableArraySequence<T>(endIndex - startIndex + 1);
        for (int i = startIndex; i <= endIndex; ++i) {
            result->array->set(i - startIndex, get(i));
        }
        return result;
    }

    ImmutableArraySequence<T>* concat(const Sequence<T>& other) const override {
        ImmutableArraySequence<T>* result = new ImmutableArraySequence<T>(getLength() + other.getLength());
        int i = 0;
        for (; i < getLength(); ++i) {
            result->array->set(i, get(i));
        }
        for (; i < result->getLength(); ++i) {
            result->array->set(i, other.get(i - getLength()));
        }
        return result;
    }
};

