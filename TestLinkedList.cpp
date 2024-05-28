#include <cassert>
#include "DynamicArray.h"
#include "LinkedList.h"
#include "Sequence.h"
#include "MutableListSequence.h"
#include "TestLinkedList.h"

void TestLinkedList::testClass() {
    testConstructors();
    testGet();
    testSquareBrackets();
    testGetLength();
    testSet();
    testGetFirst();
    testGetLast();
    testAppend();
    testPrepend();
    testInsertAt();
    testConcat();
    testGetSubsequence();
    testAssignmentOperator();
}

void TestLinkedList::testConstructors() {

    LinkedList<int> ll0;
    assert(ll0.getLength() == 0);

    int m[7] = {0, 1, 2, 3, 4, 5, 6};
    LinkedList<int> ll2(m, 7);
    assert(ll2.getLength() == 7);
    for (int i = 0; i < ll2.getLength(); ++i) {
        assert(ll2.get(i) == m[i]);
    }
    try {
        LinkedList<int> llexcept(m, -1);
        assert(false);
    } catch (std::out_of_range&) {}

    LinkedList<int> ll3(ll2);
    assert(ll3.getLength() == ll2.getLength());
    for (int i = 0; i < ll3.getLength(); ++i) {
        assert(ll3.get(i) == ll3.get(i));
    }

    MutableListSequence<int> mls(m, 7);
    LinkedList<int> ll4(mls);
    assert(ll4.getLength() == mls.getLength());
    for (int i = 0; i < ll4.getLength(); ++i) {
        assert(ll4.get(i) == mls.get(i));
    }

    int length = 5;
    LinkedList<int> ll5(length);
    assert(ll5.getLength() == length);
    try {
        LinkedList<int> llexcept(-1);
        assert(false);
    } catch (std::out_of_range&) {}
}

void TestLinkedList::testSet() {
    int length = 7;
    int m[7] = {0, 1, 2, 3, 4, 5, 6};
    LinkedList<int> ll(m, length);
    int index1 = 0;
    int index2 = 3;
    int index3 = 6;
    int value = 100;
    ll.set(index1, value);
    ll.set(index2, value);
    ll.set(index3, value);
    assert(ll.get(index1) == value && ll.get(index2) == value && ll.get(index3) == value);
    try {
        ll.set(-1, 10);
        assert(false);
    } catch (std::out_of_range&) {}
    try {
        ll.set(length, 10);
        assert(false);
    } catch (std::out_of_range&) {}
}

void TestLinkedList::testGet() {
    int length = 7;
    int m[7] = {0, 1, 2, 3, 4, 5, 6};
    LinkedList<int> ll(m, length);
    for (int i = 0; i < length; ++i) {
        assert(ll.get(i) == m[i]);
    }
    try {
        ll.get(-1);
        assert(false);
    } catch (std::out_of_range&) {}
    try {
        ll.get(length);
        assert(false);
    } catch (std::out_of_range&) {}
}

void TestLinkedList::testSquareBrackets() {
    int length = 7;
    int m[7] = {0, 1, 2, 3, 4, 5, 6};
    LinkedList<int> da(m, length);
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

void TestLinkedList::testGetLength() {
    int m[7] = {0, 1, 2, 3, 4, 5, 6};
    LinkedList<int> ll(m, 7);
    assert(ll.getLength() == 7);
}

void TestLinkedList::testGetFirst() {
    int length = 7;
    int m[7] = {0, 1, 2, 3, 4, 5, 6};
    LinkedList<int> ll(m, length);
    assert(ll.getFirst() == m[0]);

    LinkedList<int> llexcept;
    try {
        llexcept.getFirst();
        assert(false);
    } catch (std::out_of_range&) {}
}

void TestLinkedList::testGetLast() {
    int length = 7;
    int m[7] = {0, 1, 2, 3, 4, 5, 6};
    LinkedList<int> ll(m, length);
    assert(ll.getLast() == m[6]);

    LinkedList<int> llexcept;
    try {
        llexcept.getFirst();
        assert(false);
    } catch (std::out_of_range&) {}
}

void TestLinkedList::testAppend() {
    int m[7] = {0, 1, 2, 3, 4, 5, 6};
    LinkedList<int> ll(m, 7);
    int elem = 100;
    ll.append(elem);
    assert(ll.getLength() == 8);
    for (int i = 0; i < 7; ++i) {
        assert(ll.get(i) == m[i]);
    }
    assert(ll.get(7) == elem);

    LinkedList<int> ll2; // пустой список
    ll2.append(elem);
    assert(ll2.get(0) == elem);
}

void TestLinkedList::testPrepend() {
    int m[7] = {0, 1, 2, 3, 4, 5, 6};
    LinkedList<int> ll(m, 7);
    int elem = 100;
    ll.prepend(elem);
    assert(ll.getLength() == 8);
    assert(ll.get(0) == elem);
    for (int i = 1; i < 8; ++i) {
        assert(ll.get(i) == m[i - 1]);
    }

    LinkedList<int> ll2; // пустой список
    ll2.prepend(elem);
    assert(ll2.get(0) == elem);
}

void TestLinkedList::testInsertAt() {
    int length = 7;
    int m[7] = {0, 1, 2, 3, 4, 5, 6};
    LinkedList<int> ll(m, 7);
    int elem = 100;
    int index1 = 0; // крайний случай
    int index2 = 3;
    int index3 = 9; // крайний случай
    length += 3;
    ll.insertAt(index1, elem);
    ll.insertAt(index2, elem);
    ll.insertAt(index3, elem);
    assert(ll.getLength() == 10);
    int i = 0;
    assert(ll.get(i++) == elem);
    for (; i < index2; ++i) {
        assert(ll.get(i) == m[i - 1]);
    }
    assert(ll.get(i++) == elem);
    for (; i < ll.getLength() - 1; ++i) {
        assert(ll.get(i) == m[i - 2]);
    }
    assert(ll.get(i) == elem);

    try {
        ll.insertAt(-1, 10);
        assert(false);
    } catch (std::out_of_range&) {}
    try {
        ll.insertAt(length + 1, 10);
        assert(false);
    } catch (std::out_of_range&) {}


    LinkedList<int> ll2; // пустой список
    ll2.insertAt(0, elem);
    assert(ll2.get(0) == elem);
}

void TestLinkedList::testGetSubsequence() {
    int length = 7;
    int m[7] = {0, 1, 2, 3, 4, 5, 6};
    LinkedList<int> ll(m, length);
    int startIndex = 2;
    int endIndex = 5;
    LinkedList<int>* result = ll.getSubsequence(startIndex, endIndex);
    for (int i = startIndex; i <= endIndex; ++i) {
        assert(result->get(i - startIndex) == m[i]);
    }

    try {
        ll.getSubsequence(0, length);
        assert(false);
    } catch (std::out_of_range&) {}
    try {
        ll.getSubsequence(-1, 0);
        assert(false);
    } catch (std::out_of_range&) {}
    try {
        ll.getSubsequence(1, 0);
        assert(false);
    } catch (std::out_of_range&) {}

}

void TestLinkedList::testConcat() {
    int m_1[7] = {0, 1, 2, 3, 4, 5, 6};
    LinkedList<int> ll1(m_1, 7);
    int m_2[3] = {7, 8, 9};
    LinkedList<int> ll2(m_2, 3);
    LinkedList<int>* result = ll1.concat(&ll2);
    int i = 0;
    for (; i < 7; ++i) {
        assert(result->get(i) == m_1[i]);
    }
    for (; i < 10; ++i) {
        assert(result->get(i) == m_2[i - 7]);
    }
}

void TestLinkedList::testAssignmentOperator() {
    int length = 7;
    int m[7] = {0, 1, 2, 3, 4, 5, 6};

    LinkedList<int> ll1(m, length);
    LinkedList<int> ll2(0);
    ll2 = ll1;
    assert(ll2.getLength() == ll1.getLength());
    for (int i = 0; i < length; ++i) {
        assert(ll2[i] == ll1[i]);
    }
    for (int i = 0; i < length; ++i) {
        ll1[i] = i * 100;
    }
    for (int i = 0; i < length; ++i) {
        assert(ll2[i] == m[i]);
    }
}

