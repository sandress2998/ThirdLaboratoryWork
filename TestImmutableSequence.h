#pragma once

#include <cassert>
#include "DynamicArray.h"
#include "LinkedList.h"
#include "Sequence.h"
#include "MutableArraySequence.h"


// !!! Здесь используются шаблоны, поэтому методы класса в файле .h

template<template<class> class ImmutableSequence>
class TestImmutableSequence {
public:
    void testClass() {
        testConstructors();
        testGet();
        testSquareBrackets();
        testGetLength();
        testAppend();
        testPrepend();
        testInsertAt();
        testConcat();
        testSet();
        testGetSubsequence();
        testGetFirst();
        testGetLast();
    }

    void testConstructors() {
        int length = 5;
        ImmutableSequence<int> immutSeq1(length);
        assert(immutSeq1.getLength() == length);
        try {
            ImmutableSequence<int> immutSeqexcept(-1);
            assert(false);
        } catch (std::out_of_range&) {}

        int m[7] = {0, 1, 2, 3, 4, 5, 6};
        ImmutableSequence<int> immutSeq2(m, 7);
        assert(immutSeq2.getLength() == 7);
        for (int i = 0; i < immutSeq2.getLength(); ++i) {
            assert(immutSeq2.get(i) == m[i]);
        }
        try {
            ImmutableSequence<int> immutSeqexcept(m, -1);
            assert(false);
        } catch (std::out_of_range&) {}

        ImmutableSequence<int> immutSeq3(immutSeq2);
        assert(immutSeq3.getLength() == immutSeq2.getLength());
        for (int i = 0; i < immutSeq3.getLength(); ++i) {
            assert(immutSeq3.get(i) == immutSeq3.get(i));
        }

        LinkedList<int> ll(m, 7);
        ImmutableSequence<int> immutSeq4(ll);
        assert(immutSeq4.getLength() == ll.getLength());
        for (int i = 0; i < immutSeq4.getLength(); ++i) {
            assert(immutSeq4.get(i) == ll.get(i));
        }

        DynamicArray<int> da(m,7);
        ImmutableSequence<int> immutSeq5(ll);
        assert(immutSeq5.getLength() == da.getSize());
        for (int i = 0; i < immutSeq5.getLength(); ++i) {
            assert(immutSeq5.get(i) == da.get(i));
        }

        ImmutableSequence<int> immutSeq6;
        assert(immutSeq6.getLength() == 0);

        MutableArraySequence<int> mutArrSeq(m ,7);
        ImmutableSequence<int> immutSeq7(mutArrSeq);
        assert(immutSeq7.getLength() == mutArrSeq.getLength());
        for (int i = 0; i < 7; ++i) {
            assert(immutSeq7.get(i) == mutArrSeq.get(i));
        }
    }

    void testGet() {
        int length = 7;
        int m[7] = {0, 1, 2, 3, 4, 5, 6};
        ImmutableSequence<int> immutSeq(m, length);
        for (int i = 0; i < 7; ++i) {
            assert(immutSeq.get(i) == m[i]);
        }
        try {
            immutSeq.get(-1);
            assert(false);
        } catch (std::out_of_range&) {}
        try {
            immutSeq.get(length);
            assert(false);
        } catch (std::out_of_range&) {}
    }

    void testSquareBrackets() {
        int length = 7;
        int m[7] = {0, 1, 2, 3, 4, 5, 6};
        ImmutableSequence<int> da(m, length);
        for (int i = 0; i < 7; ++i) {
            assert(da[i] == m[i]);
        }

        try {
            da[-1];
            assert(false);
        } catch (std::out_of_range&) {}
        try {
            da[length];
            assert(false);
        } catch (std::out_of_range&) {}
    }

    void testGetFirst() {
        int length = 7;
        int m[7] = {0, 1, 2, 3, 4, 5, 6};
        ImmutableSequence<int> immutSeq(m, length);
        assert(immutSeq.getFirst() == 0);
        try {
            ImmutableSequence<int> immutSeqexcept;
            immutSeqexcept.getFirst();
            assert(false);
        } catch (std::out_of_range&) {}
    }

    void testGetLast() {
        int length = 7;
        int m[7] = {0, 1, 2, 3, 4, 5, 6};
        ImmutableSequence<int> immutSeq(m, length);
        assert(immutSeq.getLast() == 6);
        try {
            ImmutableSequence<int> immutSeqexcept;
            immutSeqexcept.getLast();
            assert(false);
        } catch (std::out_of_range&) {}
    }

    void testGetLength() {
        int length = 7;
        int m[7] = {0, 1, 2, 3, 4, 5, 6};
        ImmutableSequence<int> immutSeq(m, length);
        assert(immutSeq.getLength() == 7);
    }

    void testAppend() {
        int length = 7;
        int m[7] = {0, 1, 2, 3, 4, 5, 6};
        ImmutableSequence<int> immutSeq(m, length);
        int elem = 100;
        Sequence<int>* immutSeq2 = immutSeq.append(elem);
        assert(immutSeq2->getLength() == 8);
        assert(immutSeq.getLength() == 7);
        for (int i = 0; i < immutSeq.getLength(); ++i) {
            assert(immutSeq.get(i) == m[i]);
            assert(immutSeq2->get(i) == m[i]);
        }
        assert(immutSeq2->get(7) == elem);
        delete immutSeq2;

        ImmutableSequence<int> immutSeq3; // пустая последовательность
        ImmutableSequence<int>* immutSeq4 = immutSeq3.append(elem);
        assert(immutSeq4->get(0) == elem);
        delete immutSeq4;
    }

    void testPrepend() {
        int length = 7;
        int m[7] = {0, 1, 2, 3, 4, 5, 6};
        ImmutableSequence<int> immutSeq(m, length);
        int elem = 100;
        Sequence<int>* immutSeq2 = immutSeq.prepend(elem);
        assert(immutSeq.getLength() == 7);
        assert(immutSeq2->getLength() == 8);
        assert(immutSeq2->get(0) == elem);
        for (int i = 1; i < 8; ++i) {
            assert(immutSeq.get(i - 1) == m[i - 1]);
            assert(immutSeq2->get(i) == m[i - 1]);
        }
        delete immutSeq2;

        ImmutableSequence<int> immutSeq3; // пустая последовательность
        ImmutableSequence<int>* immutSeq4 = immutSeq3.prepend(elem);
        assert(immutSeq4->get(0) == elem);
        delete immutSeq4;
    }

    void testInsertAt() {
        int length = 7;
        int m[7] = {0, 1, 2, 3, 4, 5, 6};
        ImmutableSequence<int> immutSeq(m, length);

        Sequence<int>* immutSeq2;
        int elem = 100;
        int index = 3;
        immutSeq2 = immutSeq.insertAt(index, elem);
        assert(immutSeq.getLength() == 7);
        assert(immutSeq2->getLength() == 8);
        int i = 0;
        for (; i < index; ++i) {
            assert(immutSeq2->get(i) == m[i]);
            assert(immutSeq.get(i) == m[i]);
        }
        assert(immutSeq2->get(i++) == elem);
        for (; i < immutSeq2->getLength(); ++i) {
            assert(immutSeq2->get(i) == m[i - 1]);
            assert(immutSeq.get(i - 1) == m[i - 1]);
        }
        delete immutSeq2;

        // крайний случай
        elem = 100;
        index = 0;
        immutSeq2 = immutSeq.insertAt(index, elem);
        assert(immutSeq.getLength() == 7);
        assert(immutSeq2->getLength() == 8);
        i = 0;
        assert(immutSeq2->get(i++) == elem);
        for (; i < immutSeq2->getLength(); ++i) {
            assert(immutSeq2->get(i) == m[i - 1]);
            assert(immutSeq.get(i - 1) == m[i - 1]);
        }
        delete immutSeq2;

        // крайний случай
        elem = 100;
        index = 7;
        immutSeq2 = immutSeq.insertAt(index, elem);
        assert(immutSeq.getLength() == 7);
        assert(immutSeq2->getLength() == 8);
        i = 0;
        for (; i < index; ++i) {
            assert(immutSeq2->get(i) == m[i]);
            assert(immutSeq.get(i) == m[i]);
        }
        assert(immutSeq2->get(i++) == elem);
        delete immutSeq2;

        try {
            immutSeq.insertAt(-1, elem);
            assert(false);
        } catch (std::out_of_range&) {}

        try {
            immutSeq.insertAt(length + 1, elem);
            assert(false);
        } catch (std::out_of_range&) {}


        ImmutableSequence<int> immutSeq3; // пустая последовательность
        ImmutableSequence<int>* immutSeq4 = immutSeq3.insertAt(0, elem);
        assert(immutSeq4->get(0) == elem);
        delete immutSeq4;
    }

    void testSet() {
        int length = 7;
        int m[7] = {0, 1, 2, 3, 4, 5, 6};
        ImmutableSequence<int> immutSeq(m, length);

        int index = 3;
        int elem = 100;
        ImmutableSequence<int>* immutSeq2 = immutSeq.set(index, elem);
        assert(immutSeq.getLength() == length);
        assert(immutSeq2->getLength() == length);
        for (int i = 0; i < length; ++i) {
            if (i != index) {
                assert(immutSeq[i] == (*immutSeq2)[i]);
            } else {
                assert(immutSeq[i] == m[i]);
                assert((*immutSeq2)[i] == elem);
            }
        }
        delete immutSeq2;

        try {
            immutSeq2 = immutSeq.set(-1, elem);
            assert(false);
        } catch (std::out_of_range) {}
        try {
            immutSeq2 = immutSeq.set(length, elem);
            assert(false);
        } catch (std::out_of_range) {}
    }

    void testGetSubsequence() {
        int length = 7;
        int m[7] = {0, 1, 2, 3, 4, 5, 6};
        ImmutableSequence<int> immutSeq(m, length);
        int startIndex = 2;
        int endIndex = 5;
        Sequence<int>* result = immutSeq.getSubsequence(startIndex, endIndex);
        for (int i = startIndex; i <= endIndex; ++i) {
            assert(result->get(i - startIndex) == m[i]);
        }
        try {
            immutSeq.getSubsequence(0, length);
            assert(false);
        } catch (std::out_of_range) {}
        try {
            immutSeq.getSubsequence(-1, 0);
            assert(false);
        } catch (std::out_of_range) {}
        try {
            immutSeq.getSubsequence(1, 0);
            assert(false);
        } catch (std::out_of_range&) {}
    }

    void testConcat() {
        int m1[7] = {0, 1, 2, 3, 4, 5, 6};
        ImmutableSequence<int> immutSeq1(m1, 7);
        int m2[3] = {7, 8, 9};
        ImmutableSequence<int> immutSeq2(m2, 3);
        Sequence<int>* result = immutSeq1.concat(immutSeq2);
        int i = 0;
        for (; i < 7; ++i) {
            assert(result->get(i) == m1[i]);
        }
        for (; i < 10; ++i) {
            assert(result->get(i) == m2[i - 7]);
        }
    }
};
