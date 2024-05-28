#include <cassert>
#include "DynamicArray.h"
#include "LinkedList.h"
#include "Sequence.h"
#include "MutableListSequence.h"
#include "TestDynamicArray.h"

void TestDynamicArray::testClass() {
    testConstructors();
    testGet();
    testSquareBrackets();
    testGetSize();
    testSet();
    testResize();
    testAppend();
    testPrepend();
    testInsertAt();
    testAssignmentOperator();
}

void TestDynamicArray::testConstructors() {

    DynamicArray<int> da1(5);
    assert(da1.getSize() == 5);
    try {
        DynamicArray<int> daexcept(-1);
        assert(false);
    } catch (std::out_of_range&) {}

    int m[7] = {0, 1, 2, 3, 4, 5, 6};
    DynamicArray<int> da2(m, 7);
    assert(da2.getSize() == 7);
    for (int i = 0; i < da2.getSize(); ++i) {
        assert(da2.get(i) == m[i]);
    }
    try {
        DynamicArray<int> daexcept(m, -1);
        assert(false);
    } catch (std::out_of_range&) {}

    DynamicArray<int> da3(da2);
    assert(da3.getSize() == da2.getSize());
    for (int i = 0; i < da3.getSize(); ++i) {
        assert(da3.get(i) == da3.get(i));
    }

    MutableListSequence<int> mls(m, 7);
    DynamicArray<int> da4(mls);
    assert(da4.getSize() == mls.getLength());
    for (int i = 0; i < da4.getSize(); ++i) {
        assert(da4.get(i) == mls.get(i));
    }

    LinkedList<int> ll(m, 7);
    DynamicArray<int> da5(ll);
    assert(da5.getSize() == ll.getLength());
    for (int i = 0; i < da5.getSize(); ++i) {
        assert(da5.get(i) == ll.get(i));
    }
}

void TestDynamicArray::testSet() {
    int length = 7;
    int m[7] = {0, 1, 2, 3, 4, 5, 6};
    DynamicArray<int> da(m, length);
    int index1 = 0;
    int index2 = 3;
    int index3 = 6;
    int value = 100;
    da.set(index1, value);
    da.set(index2, value);
    da.set(index3, value);
    assert(da.get(index1) == value && da.get(index2) == value && da.get(index3) == value);
    try {
        da.set(-1, 10);
        assert(false);
    } catch (std::out_of_range&) {}
    try {
        da.set(length, 10);
        assert(false);
    } catch (std::out_of_range&) {}
}

void TestDynamicArray::testGet() {
    int length = 7;
    int m[7] = {0, 1, 2, 3, 4, 5, 6};
    DynamicArray<int> da(m, length);
    for (int i = 0; i < 7; ++i) {
        assert(da.get(i) == m[i]);
    }

    try {
        da.get(-1);
        assert(false);
    } catch (std::out_of_range&) {}
    try {
        da.get(length);
        assert(false);
    } catch (std::out_of_range&) {}
}

void TestDynamicArray::testSquareBrackets() {
    int length = 7;
    int m[7] = {0, 1, 2, 3, 4, 5, 6};
    DynamicArray<int> da(m, length);
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

void TestDynamicArray::testGetSize() {
    int m[7] = {0, 1, 2, 3, 4, 5, 6};
    DynamicArray<int> da(m, 7);
    assert(da.getSize() == 7);
}

void TestDynamicArray::testResize() {
    int length = 7;
    int m[7] = {0, 1, 2, 3, 4, 5, 6};
    DynamicArray<int> da(m, length);
    try {
        da.resize(-1);
        assert(false);
    } catch (std::out_of_range&) {}

    da.resize(10);
    assert(da.getSize() == 10);
    for (int i = 0; i < 7; ++i) {
        assert(da.get(i) == m[i]);
    }
    da.resize(4);
    assert(da.getSize() == 4);
    for (int i = 0; i < 4; ++i) {
        assert(da.get(i) == m[i]);
    }
}


void TestDynamicArray::testAppend() {
    int m[7] = {0, 1, 2, 3, 4, 5, 6};
    DynamicArray<int> da(m, 7);
    int elem = 100;
    da.append(elem);
    assert(da.getSize() == 8);
    for (int i = 0; i < 7; ++i) {
        assert(da.get(i) == m[i]);
    }
    assert(da.get(7) == elem);

    DynamicArray<int> da2(0); // пустой массив
    da2.append(elem);
    assert(da2.get(0) == elem);
}

void TestDynamicArray::testPrepend() {
    int m[7] = {0, 1, 2, 3, 4, 5, 6};
    DynamicArray<int> da(m, 7);
    int elem = 100;
    da.prepend(elem);
    assert(da.getSize() == 8);
    assert(da.get(0) == elem);
    for (int i = 1; i < 8; ++i) {
        assert(da.get(i) == m[i - 1]);
    }

    DynamicArray<int> da2(0); // пустой массив
    da2.prepend(elem);
    assert(da2.get(0) == elem);
}


void TestDynamicArray::testInsertAt() {

    int length = 7;
    int m[7] = {0, 1, 2, 3, 4, 5, 6};
    DynamicArray<int> da(m, 7);
    int elem = 100;
    int index1 = 0; // крайний случай
    int index2 = 3;
    int index3 = 9; // крайний случай
    length += 3;
    da.insertAt(index1, elem);
    da.insertAt(index2, elem);
    da.insertAt(index3, elem);
    assert(da.getSize() == 10);
    int i = 0;
    assert(da.get(i++) == elem);
    for (; i < index2; ++i) {
        assert(da.get(i) == m[i - 1]);
    }
    assert(da.get(i++) == elem);
    for (; i < da.getSize() - 1; ++i) {
        assert(da.get(i) == m[i - 2]);
    }
    assert(da.get(i) == elem);

    try {
        da.insertAt(-1, 10);
        assert(false);
    } catch (std::out_of_range&) {}
    try {
        da.insertAt(length + 1, 10);
        assert(false);
    } catch (std::out_of_range&) {}


    DynamicArray<int> da2(0); // пустой массив
    da2.insertAt(0, elem);
    assert(da2.get(0) == elem);
}

void TestDynamicArray::testAssignmentOperator() {
    int length = 7;
    int m[7] = {0, 1, 2, 3, 4, 5, 6};

    DynamicArray<int> da1(m, length);
    DynamicArray<int> da2(0);
    da2 = da1;
    assert(da2.getSize() == da1.getSize());
    for (int i = 0; i < length; ++i) {
        assert(da2[i] == da1[i]);
    }
    for (int i = 0; i < length; ++i) {
        da1[i] = i * 100;
    }
    for (int i = 0; i < length; ++i) {
        assert(da2[i] == m[i]);
    }
}
