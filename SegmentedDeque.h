#pragma once

#include <stdexcept>
#include "Sequence.h"
#include "MutableSequence.h"
#include "DynamicArray.h"
#include "LinkedList.h"

template <typename T>
class SegmentedDeque {
private:
    int bufSize; // длина сегмента
    int segmentNumber = 0; // количество сегментов
    int size = 0; // кол-во элементов во всех сегментах
    T** arrayPtr = nullptr; // указатель на массив указателей на сегменты
    int offsetTail = 0; // отступ, чтобы создать новый элемент сзади
    int offsetHead = 0; // отступ, чтобы создать новый элемент спереди

    void increaseHead() {
        // создаем новый сегмент
        T** helpArray = new T*[segmentNumber + 1];
        for (int i = 0; i < segmentNumber; ++i) {
            helpArray[i] = arrayPtr[i];
        }
        delete[] arrayPtr;
        arrayPtr = helpArray;
        ++segmentNumber;
        arrayPtr[segmentNumber - 1] = new T[bufSize];
    }

    void decreaseHead() {
        if (segmentNumber == 0) throw std::out_of_range("You tried to delete element from empty deque.\n");
        T** helpArray = new T*[segmentNumber - 1];
        for (int i = 0; i < segmentNumber - 1; ++i) {
            helpArray[i] = arrayPtr[i];
        }
        delete[] arrayPtr[segmentNumber - 1]; // удаляем последний сегмент
        delete[] arrayPtr; // удаляем массив указателей
        arrayPtr = helpArray;
        --segmentNumber;
        if (segmentNumber == 0) arrayPtr = nullptr;
    }

    void increaseTail() {
        T** helpArray = new T*[segmentNumber + 1];
        for (int i = 0; i < segmentNumber; ++i) {
            helpArray[i + 1] = arrayPtr[i];
        }
        delete[] arrayPtr;
        arrayPtr = helpArray;
        ++segmentNumber;
        arrayPtr[0] = new T[bufSize];
    }

    void decreaseTail() {
        if (segmentNumber == 0) throw std::out_of_range("You tried to delete element from empty deque.\n");
        T** helpArray = new T*[segmentNumber - 1];
        for (int i = 1; i < segmentNumber; ++i) {
            helpArray[i - 1] = arrayPtr[i];
        }
        delete[] arrayPtr[0]; // удаляем последний сегмент
        delete[] arrayPtr; // удаляем массив указателей
        arrayPtr = helpArray;
        --segmentNumber;
        if (segmentNumber == 0) arrayPtr = nullptr;
    }

    // const - метод, так как используется в [] const
    T& getPrivate(int index) const {
        if (index < 0 || index >= size) throw std::out_of_range("Entered index is out of range.\n");
        int segmentIndex = index / bufSize;
        index %= bufSize;
        if (offsetTail == 0) return arrayPtr[segmentIndex][index - offsetTail];
        if (offsetTail < index + 1) return arrayPtr[segmentIndex + 1][index - offsetTail];
        return arrayPtr[segmentIndex][(bufSize - offsetTail + index) % bufSize];
    }

public:
    SegmentedDeque(int bufSize = 4): bufSize(bufSize) {}

    SegmentedDeque(const Sequence<T>& other, int bufSize = 4): bufSize(bufSize) {
        for (int i = 0; i < other.getLength(); ++i) {
            append(other.get(i));
        }
    }

    SegmentedDeque(T* array, int size, int bufSize = 4): bufSize(bufSize) {
        for (int i = 0; i < size; ++i) {
            append(array[i]);
        }
    }

    SegmentedDeque(const LinkedList<T>& other, int bufSize = 4): bufSize(bufSize) {
        for (int i = 0; i < other.getLength(); ++i) {
            append(other.get(i));
        }
    }

    SegmentedDeque(const DynamicArray<T>& other, int bufSize = 4): bufSize(bufSize) {
        for (int i = 0; i < other.getSize(); ++i) {
            append(other.get(i));
        }
    }

    SegmentedDeque(const SegmentedDeque<T>& other, int bufSize = 4): bufSize(bufSize) {
        for (int i = 0; i < other.getLength(); ++i) {
            append(other.get(i));
        }
    }

    ~SegmentedDeque() {
        for (int i = 0; i < segmentNumber; ++i) {
            delete[] arrayPtr[i];
        }
        delete[] arrayPtr;
    }

    T& operator[](int index) {
        return getPrivate(index);
    }

    const T& operator[](int index) const {
        return getPrivate(index);
    }

    SegmentedDeque<T>& operator=(const SegmentedDeque<T>& other) {
        // удаляем текущий дек
        for (int i = 0; i < segmentNumber; ++i) {
            delete[] arrayPtr[i];
        }
        delete[] arrayPtr;
        segmentNumber = 0;
        size = 0;
        arrayPtr = nullptr;
        offsetTail = 0;
        offsetHead = 0;
        bufSize = other.bufSize;

        // копируем элементы
        for (int i = 0; i < other.getLength(); ++i) {
            append(other.get(i));
        }
        return *this;
    }

    int getLength() const {
        return size;
    }

    T get(int index) const {
        // если index вне допустимых значений, то (*this)[index] выбросит исключение
        return (*this)[index];
    }

    T getFirst() const {
        if (size == 0) throw std::out_of_range("You tried to get value from the empty SegmentedDeque.\n");
        //return arrayPtr[0][(bufSize - offsetTail) % bufSize];
        return (*this)[0];
    }

    T getLast() const {
        if (size == 0) throw std::out_of_range("You tried to get value from the empty SegmentedDeque.\n");
        //return arrayPtr[segmentNumber - 1][(offsetHead + bufSize - 1) % bufSize];
        return (*this)[size - 1];
    }

    void set(int index, const T& item) {
        (*this)[index] = item;
    }

    void append(const T& item) {
        if (offsetHead == 0) { // добавляем сегмент в конец
            increaseHead();
            arrayPtr[segmentNumber - 1][offsetHead] = item;
            offsetHead = 1;
        } else { // не добавляем сегмент
            arrayPtr[segmentNumber - 1][offsetHead] = item;
            offsetHead = (offsetHead + 1) % bufSize;
        }
        ++size;
    }

    void prepend(const T& item) {
        if (offsetTail == 0) { // добавляем сегмент в начало
            increaseTail();
            arrayPtr[0][bufSize - 1] = item;
            ++offsetTail;
        } else { // не добавляем сегмент
            arrayPtr[0][bufSize - offsetTail - 1] = item;
            offsetTail = (offsetTail + 1) % bufSize;
        }
        ++size;
    }

    void insertAt(int index, const T& item) {
        if (index < 0 || index > size) throw std::out_of_range("Entered index is out of range.\n");
        if (index == size) {
            append(item);
            return;
        }
        prepend(item);
        for (int i = 1; i <= index; ++i) {
            (*this)[i - 1] = (*this)[i];
        }
        (*this)[index] = item;
    }

    void popHead() {
        if (size == 0) throw std::out_of_range("You tried to pop element from the empty deque.\n");
        if (offsetHead == 1) { // удаляем последний сегмент
            decreaseHead();
            offsetHead = 0;
        } else { // не удаляем последний сегмент
            if (offsetHead == 0) {
                offsetHead = bufSize;
            }
            --offsetHead;
        }
        --size;
    }

    void popTail() {
        if (size == 0) throw std::out_of_range("You tried to pop element from the empty deque.\n");
        if (offsetTail == 1) { // удаляем первый сегмент
            decreaseTail();
            offsetTail = 0;
            --segmentNumber;
        } else { // не удаляем сегмент
            if (offsetTail == 0) {
                offsetTail = bufSize;
            }
            --offsetTail;
        }
        --size;
    }

    void removeAt(int index) {
        if (index < 0 || index >= size) throw std::out_of_range("You tried to delete element from the empty deque.\n");
        for (int i = index + 1; i < size; ++i) {
            (*this)[i - 1] = (*this)[i];
        }
        popHead();
    }

    int getBufSize() const {
        return bufSize;
    }
};
