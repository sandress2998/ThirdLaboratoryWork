#include <cassert>
#include "ImmutableSegmentedDeque.h"
#include "MutableArraySequence.h"
#include "LinkedList.h"
#include "DynamicArray.h"
#include "Sequence.h"
#include "TestImmutableSegmentedDeque.h"


void TestImmutableSegmentedDeque::testClass() {
    testConstructors();
    testSquareAnkles();
    testGet();
    testSet();
    testGetFirst();
    testGetLast();
    testAppend();
    testPrepend();
    testInsertAt();
    testPopHead();
    testPopTail();
    testRemoveAt();
    testGetSubsequence();
    testConcat();
}

void TestImmutableSegmentedDeque::testConstructors() {
    testDefaultConstructor();
    testArrayConstructor();
    testDynamicArrayConstructor();
    testLinkedListConstructor();
    testSequenceConstructor();
    testCopyConstructor();
}

void TestImmutableSegmentedDeque::testDefaultConstructor() {
    int m[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int length = 13;
    int bufSize = 6;

    ImmutableSegmentedDeque<int> deque(bufSize);
    assert(deque.getBufSize() == bufSize);
    assert(deque.getLength() == 0);
}

void TestImmutableSegmentedDeque::testArrayConstructor() {
    int m[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int length = 13;
    int bufSize = 6;

    ImmutableSegmentedDeque<int> deque(m, length, bufSize);
    assert(deque.getBufSize() == bufSize);
    assert(deque.getLength() == length);
    for (int i = 0; i < length; ++i) {
        assert(deque.get(i) == m[i]);
    }
}

void TestImmutableSegmentedDeque::testDynamicArrayConstructor() {
    int m[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int length = 13;
    int bufSize = 6;

    DynamicArray<int> other(m, length);
    ImmutableSegmentedDeque<int> deque(other, bufSize);
    assert(deque.getBufSize() == bufSize);
    assert(deque.getLength() == length);
    for (int i = 0; i < length; ++i) {
        assert(deque.get(i) == m[i]);
    }
}

void TestImmutableSegmentedDeque::testLinkedListConstructor() {
    int m[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int length = 13;
    int bufSize = 6;

    LinkedList<int> linkedList(m, length);
    ImmutableSegmentedDeque<int> deque(linkedList, bufSize);
    assert(deque.getBufSize() == bufSize);
    assert(deque.getLength() == length);
    for (int i = 0; i < length; ++i) {
        assert(deque.get(i) == m[i]);
    }
}

void TestImmutableSegmentedDeque::testSequenceConstructor() {
    int m[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int length = 13;
    int bufSize = 6;

    MutableArraySequence<int> sequence(m, length);
    ImmutableSegmentedDeque<int> deque(sequence, bufSize);
    assert(deque.getBufSize() == bufSize);
    assert(deque.getLength() == length);
    for (int i = 0; i < length; ++i) {
        assert(deque.get(i) == m[i]);
    }
}

void TestImmutableSegmentedDeque::testCopyConstructor() {
    int m[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int length = 13;
    int bufSize = 6;

    ImmutableSegmentedDeque<int> dynamicArray(m, length);
    ImmutableSegmentedDeque<int> deque(dynamicArray, bufSize);
    assert(deque.getBufSize() == bufSize);
    assert(deque.getLength() == length);
    for (int i = 0; i < length; ++i) {
        assert(deque.get(i) == m[i]);
    }
}

void TestImmutableSegmentedDeque::testSquareAnkles() {
    testSquareAnklesValidIndex();
    testSquareAnklesInvalidIndex();
}

void TestImmutableSegmentedDeque::testSquareAnklesValidIndex() {
    int m[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int length = 13;
    int bufSize = 6;

    ImmutableSegmentedDeque<int> deque(m, length, bufSize);

    for (int i = 0; i < length; ++i) {
        assert(deque[i] == m[i]);
    }
}

void TestImmutableSegmentedDeque::testSquareAnklesInvalidIndex() {
    int m[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int length = 13;
    int bufSize = 6;

    ImmutableSegmentedDeque<int> deque(m, length, bufSize);

    try {
        deque[-1];
        assert(false);
    } catch (std::out_of_range) {}
    try {
        deque[length];
        assert(false);
    } catch (std::out_of_range) {}
}

void TestImmutableSegmentedDeque::testGet() {
    testGetValidIndex();
    testGetInvalidIndex();
}

void TestImmutableSegmentedDeque::testGetValidIndex() {
    int m[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int length = 13;
    int bufSize = 6;

    ImmutableSegmentedDeque<int> deque(m, length, bufSize);

    for (int i = 0; i < length; ++i) {
        assert(deque.get(i) == m[i]);
    }
}

void TestImmutableSegmentedDeque::testGetInvalidIndex() {
    int m[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int length = 13;
    int bufSize = 6;

    ImmutableSegmentedDeque<int> deque(m, length, bufSize);

    try {
        deque.get(-1);
        assert(false);
    } catch (std::out_of_range) {}
    try {
        deque.get(length);
        assert(false);
    } catch (std::out_of_range) {}
}

void TestImmutableSegmentedDeque::testSet() {
    testSetValidIndex();
    testSetInvalidIndex();
}

void TestImmutableSegmentedDeque::testSetValidIndex() {
    int m[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int length = 13;
    int bufSize = 6;

    ImmutableSegmentedDeque<int> deque(m, length, bufSize);

    int elem = 100;
    int index = 5;

    ImmutableSegmentedDeque<int>* deque2 = deque.set(index, elem);

    assert(deque2->getLength() == deque.getLength());
    int i = 0;
    for (; i < index; ++i) {
        assert(deque2->get(i) == m[i]);
    }
    assert(deque2->get(i++) == elem);
    for (; i < deque2->getLength(); ++i) {
        assert(deque2->get(i) == m[i]);
    }
    delete deque2;
}

void TestImmutableSegmentedDeque::testSetInvalidIndex() {
    int m[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int length = 13;
    int bufSize = 6;

    ImmutableSegmentedDeque<int> deque(m, length, bufSize);

    int elem = 100;
    try {
        deque.set(-1, elem);
        assert(false);
    } catch (std::out_of_range) {}
    try {
        deque.set(length, elem);
        assert(false);
    } catch (std::out_of_range) {}
}

void TestImmutableSegmentedDeque::testGetFirst() {
    testGetFirstInFullDeque();
    testGetFirstInEmptyDeque();
}

void TestImmutableSegmentedDeque::testGetFirstInFullDeque() {
    int m[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int length = 13;
    int bufSize = 6;

    ImmutableSegmentedDeque<int> deque(m, length, bufSize);

    assert(deque.getFirst() == m[0]);
}

void TestImmutableSegmentedDeque::testGetFirstInEmptyDeque() {
    int m[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int length = 13;
    int bufSize = 6;

    ImmutableSegmentedDeque<int> deque(m, length, bufSize);

    try {
        ImmutableSegmentedDeque<int> deque2(bufSize);
        deque2.getFirst();
        assert(false);
    } catch(std::out_of_range) {}
}

void TestImmutableSegmentedDeque::testGetLast() {
    testGetLastInFullDeque();
    testGetLastInEmptyDeque();
}

void TestImmutableSegmentedDeque::testGetLastInFullDeque() {
    int m[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int length = 13;
    int bufSize = 6;

    ImmutableSegmentedDeque<int> deque(m, length, bufSize);
    assert(deque.getLast() == m[length - 1]);

    int elem = 100;
    ImmutableSegmentedDeque<int>* deque2 = deque.append(elem);
    assert(deque2->getLast() == elem);
    delete deque2;
}

void TestImmutableSegmentedDeque::testGetLastInEmptyDeque() {
    int bufSize = 6;
    try {
        ImmutableSegmentedDeque<int> deque(bufSize);
        deque.getLast();
        assert(false);
    } catch(std::out_of_range) {}
}

void TestImmutableSegmentedDeque::testAppend() {
    testAppendInFullDeque();
    testAppendInEmptyDeque();
}

void TestImmutableSegmentedDeque::testAppendInFullDeque() {
    int m[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int length = 13;
    int bufSize = 6;
    int elem = 100;

    ImmutableSegmentedDeque<int> deque(m, length, bufSize);

    ImmutableSegmentedDeque<int>* deque2 = deque.append(elem);
    assert(deque2->getLength() == length + 1);
    assert(deque2->getLast() == elem);
    delete deque2;
}

void TestImmutableSegmentedDeque::testAppendInEmptyDeque(){
    int elem = 100;
    ImmutableSegmentedDeque<int> deque;
    ImmutableSegmentedDeque<int>* deque2 = deque.append(elem);
    assert(deque.getLength() == 0);
    assert(deque2->getLength() == 1);
    assert(deque2->getLast() == elem);
    delete deque2;
}

void TestImmutableSegmentedDeque::testPrepend() {
    testPrependInFullDeque();
    testPrependInEmptyDeque();
}

void TestImmutableSegmentedDeque::testPrependInFullDeque() {
    int m[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int length = 13;
    int bufSize = 6;
    int elem = 100;

    ImmutableSegmentedDeque<int> deque(m, length, bufSize);

    ImmutableSegmentedDeque<int>* deque2 = deque.prepend(elem);
    assert(deque2->getLength() == length + 1);
    assert(deque2->getFirst() == elem);
    delete deque2;
}

void TestImmutableSegmentedDeque::testPrependInEmptyDeque() {
    int elem = 100;
    ImmutableSegmentedDeque<int> deque;
    ImmutableSegmentedDeque<int>* deque2 = deque.prepend(elem);
    assert(deque2->getLength() == 1);
    assert(deque2->getFirst() == elem);
    delete deque2;
}

void TestImmutableSegmentedDeque::testInsertAt() {
    testInsertAtBeginningOfSegment();
    testInsertAtEndOfSegment();
    testInsertAtBeginningOfDeque();
    testInsertAtEndOfDeque();
    testInsertAtMiddleOfSegment();
    testInsertAtEmptyDeque();
    testInsertAtInvalidIndex();
}

void TestImmutableSegmentedDeque::testInsertAtBeginningOfSegment() {
    int m[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int length = 13;
    int bufSize = 6;
    int elem = 100;

    ImmutableSegmentedDeque<int> deque(m, length, bufSize);

    int index = bufSize;
    ImmutableSegmentedDeque<int>* deque3 = deque.insertAt(index, elem);
    assert(deque3->getLength() == length + 1);
    assert(deque.getLength() == length);

    int i = 0;
    for (; i < index; ++i) {
        assert(deque3->get(i) == m[i]);
    }
    assert(deque3->get(i++) == elem);
    for (; i < deque3->getLength(); ++i) {
        assert(deque3->get(i) == m[i - 1]);
    }
    delete deque3;
}

void TestImmutableSegmentedDeque::testInsertAtEndOfSegment() {
    int m[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int length = 13;
    int bufSize = 6;
    int elem = 100;

    ImmutableSegmentedDeque<int> deque(m, length, bufSize);

    int index = bufSize - 1;
    ImmutableSegmentedDeque<int>* deque2 = deque.insertAt(index, elem);
    assert(deque2->getLength() == length + 1);
    assert(deque.getLength() == length);

    int i = 0;
    for (; i < index; ++i) {
        assert(deque2->get(i) == m[i]);
    }
    assert(deque2->get(i++) == elem);
    for (; i < deque2->getLength(); ++i) {
        assert(deque2->get(i) == m[i - 1]);
    }
    delete deque2;
}

void TestImmutableSegmentedDeque::testInsertAtBeginningOfDeque() {
    int m[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int length = 13;
    int bufSize = 6;
    int elem = 100;

    ImmutableSegmentedDeque<int> deque(m, length, bufSize);

    int index = 0;
    ImmutableSegmentedDeque<int>* deque2 = deque.insertAt(index, elem);
    assert(deque2->getLength() == length + 1);
    assert(deque.getLength() == length);

    int i = 0;
    assert(deque2->get(i++) == elem);
    for (; i < deque2->getLength(); ++i) {
        assert(deque2->get(i) == m[i - 1]);
    }
    delete deque2;
}

void TestImmutableSegmentedDeque::testInsertAtEndOfDeque() {
    int m[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int length = 13;
    int bufSize = 6;
    int elem = 100;

    ImmutableSegmentedDeque<int> deque(m, length, bufSize);

    int index = length;
    ImmutableSegmentedDeque<int>* deque2 = deque.insertAt(index, elem);
    assert(deque2->getLength() == length + 1);
    assert(deque.getLength() == length);

    int i = 0;
    for (; i < deque2->getLength() - 1; ++i) {
        assert(deque2->get(i) == m[i]);
    }
    assert(deque2->get(i) == elem);
    delete deque2;
}

void TestImmutableSegmentedDeque::testInsertAtMiddleOfSegment() {
    int m[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int length = 13;
    int bufSize = 6;
    int elem = 100;

    ImmutableSegmentedDeque<int> deque(m, length, bufSize);

    int index = bufSize / 2;
    ImmutableSegmentedDeque<int>* deque2 = deque.insertAt(index, elem);

    assert(deque2->getLength() == length + 1);
    assert(deque.getLength() == length);

    int i = 0;
    for (; i < index; ++i) {
        assert(deque.get(i) == m[i]);
    }
    assert(deque2->get(i++) == elem);
    for (; i < deque2->getLength(); ++i) {
        assert(deque2->get(i) == m[i - 1]);
    }
    delete deque2;
}

void TestImmutableSegmentedDeque::testInsertAtEmptyDeque() {
    ImmutableSegmentedDeque<int> deque;

    int index = 0;
    int elem = 100;
    ImmutableSegmentedDeque<int>* deque2 = deque.insertAt(index, elem);
    assert(deque.getLength() == 0);
    assert(deque2->getLength() == 1);
    assert(deque2->get(0) == elem);
    delete deque2;
}

void TestImmutableSegmentedDeque::testInsertAtInvalidIndex() {
    int m[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int length = 13;
    int bufSize = 6;
    int elem = 100;

    ImmutableSegmentedDeque<int> deque(m, length, bufSize);

    try {
        deque.insertAt(-1, elem);
        assert(false);
    } catch (std::out_of_range) {}
    try {
        deque.insertAt(deque.getLength() + 1, elem);
        assert(false);
    } catch (std::out_of_range) {}
}

void TestImmutableSegmentedDeque::testPopHead() {
    testPopHeadFromEmptyDeque();
    testPopHeadExtremeElementInSegment();
    testPopHeadNotExtremeElementInSegment();
}

void TestImmutableSegmentedDeque::testPopHeadExtremeElementInSegment() {
    int m[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int length = 13;
    int bufSize = 6;

    ImmutableSegmentedDeque<int> deque(m, length, bufSize);
    ImmutableSegmentedDeque<int>* deque2 = deque.popHead();

    assert(deque2->getLength() == length - 1);
    assert(deque.getLength() == length);

    for (int i = 0; i < deque2->getLength(); ++i) {
        assert(deque2->get(i) == m[i]);
    }
    delete deque2;
}

void TestImmutableSegmentedDeque::testPopHeadNotExtremeElementInSegment() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    ImmutableSegmentedDeque<int> deque(m, length, bufSize);
    ImmutableSegmentedDeque<int>* deque2 = deque.popHead();

    assert(deque2->getLength() == length - 1);
    assert(deque.getLength() == length);

    for (int i = 0; i < deque2->getLength(); ++i) {
        assert(deque2->get(i) == m[i]);
    }
    delete deque2;
}

void TestImmutableSegmentedDeque::testPopHeadFromEmptyDeque() {
    try {
        ImmutableSegmentedDeque<int> deque;
        deque.popHead();
        assert(false);
    } catch (std::out_of_range) {}
}

void TestImmutableSegmentedDeque::testPopTail() {
    testPopTailFromFullDeque();
    testPopTailFromEmptyDeque();
}

void TestImmutableSegmentedDeque::testPopTailFromFullDeque() {
    int m[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int length = 13;
    int bufSize = 6;

    ImmutableSegmentedDeque<int> deque(m, length, bufSize);
    ImmutableSegmentedDeque<int>* deque2 = deque.popTail();

    assert(deque2->getLength() == length - 1);
    assert(deque.getLength() == length);

    for (int i = 0; i < deque2->getLength(); ++i) {
        assert(deque2->get(i) == m[i + 1]);
    }
    delete deque2;
}

void TestImmutableSegmentedDeque::testPopTailFromEmptyDeque() {
        try {
        ImmutableSegmentedDeque<int> deque;
        deque.popHead();
        assert(false);
    } catch (std::out_of_range) {}
}

void TestImmutableSegmentedDeque::testRemoveAt() {
    testRemoveAtSingleElementAtLastSegment();
    testRemoveAtNotExtremeElement();
    testRemoveAtInvalidIndex();
}

void TestImmutableSegmentedDeque::testRemoveAtSingleElementAtLastSegment() {
    int m[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int length = 13;
    int bufSize = 6;

    ImmutableSegmentedDeque<int> deque(m, length, bufSize);
    ImmutableSegmentedDeque<int>* deque2 = deque.removeAt(length - 1);

    assert(deque2->getLength() == length - 1);
    assert(deque.getLength() == length);

    for (int i = 0; i < deque2->getLength(); ++i) {
        assert(deque2->get(i) == m[i]);
    }
    delete deque2;
}

void TestImmutableSegmentedDeque::testRemoveAtNotExtremeElement() {
    int m[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int length = 13;
    int bufSize = 6;

    ImmutableSegmentedDeque<int> deque(m, length, bufSize);
    int index = length / 2;
    ImmutableSegmentedDeque<int>* deque2 = deque.removeAt(index);

    assert(deque2->getLength() == length - 1);
    assert(deque.getLength() == length);

    int i = 0;
    for (; i < index; ++i) {
        assert(deque2->get(i) == m[i]);
    }
    for (; i < deque2->getLength(); ++i) {
        assert(deque2->get(i) == m[i + 1]);
    }
    delete deque2;

}

void TestImmutableSegmentedDeque::testRemoveAtInvalidIndex() {
    int m[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int length = 13;
    int bufSize = 6;

    ImmutableSegmentedDeque<int> deque(m, length, bufSize);
    try {
        deque.removeAt(-1);
        assert(false);
    } catch (std::out_of_range) {}
    try {
        deque.removeAt(deque.getLength());
        assert(false);
    } catch (std::out_of_range) {}

}

void TestImmutableSegmentedDeque::testGetSubsequence() {
    testGetSubsequenceStartIndexLessThanEndIndex();
    testGetSubsequenceStartIndexEqualWithEndIndex();
    testGetSubsequenceInvalidIndices();
}

void TestImmutableSegmentedDeque::testGetSubsequenceStartIndexLessThanEndIndex() {
int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    ImmutableSegmentedDeque<int> deque(m, length, bufSize);

    int startIndex = 3;
    int endIndex = 7;

    Sequence<int>* result = deque.getSubsequence(startIndex, endIndex);
    assert(result->getLength() == endIndex - startIndex + 1);
    for (int i = startIndex; i < result->getLength(); ++i) {
        assert(result->get(i - startIndex) == m[i]);
    }
    delete result;
}

void TestImmutableSegmentedDeque::testGetSubsequenceStartIndexEqualWithEndIndex() {
int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    ImmutableSegmentedDeque<int> deque(m, length, bufSize);

    int startIndex = 3;
    int endIndex = 3;

    Sequence<int>* result = deque.getSubsequence(startIndex, endIndex);
    assert(result->getLength() == 1);
    delete result;
}

void TestImmutableSegmentedDeque::testGetSubsequenceInvalidIndices() {
int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    ImmutableSegmentedDeque<int> deque(m, length, bufSize);

    int startIndex;
    int endIndex;

    try {
        startIndex = - 1;
        endIndex = 5;
        deque.getSubsequence(startIndex, endIndex);
        assert(false);
    } catch (std::out_of_range) {}

    try {
        startIndex = 0;
        endIndex = length;
        deque.getSubsequence(startIndex, endIndex);
        assert(false);
    } catch (std::out_of_range) {}
    try {
        startIndex = 4;
        endIndex = 3;
        deque.getSubsequence(startIndex, endIndex);
        assert(false);
    } catch (std::out_of_range) {}
}

void TestImmutableSegmentedDeque::testConcat() {
    testConcatFullWithFull();
    testConcatFullWithEmpty();
    testConcatEmptyWithFull();
    testConcatEmptyWithEmpty();
}

void TestImmutableSegmentedDeque::testConcatFullWithFull() {
    int m1[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length1 = 14;
    int bufSize1 = 6;

    int m2[7] = {14, 15, 16, 17, 18, 19, 20};
    int length2 = 7;
    int bufSize2 = 5;

    ImmutableSegmentedDeque<int> deque1(m1, length1, bufSize1);
    ImmutableSegmentedDeque<int> deque2(m2, length2, bufSize2);

    ImmutableSegmentedDeque<int>* result = deque1.concat(deque2);
    assert(result->getLength() == length1 + length2);

    int i = 0;
    for (; i < length1; ++i) {
        assert(result->get(i) == m1[i]);
    }
    for (; i < length2; ++i) {
        assert(result->get(i) == m2[i - length1]);
    }
}

void TestImmutableSegmentedDeque::testConcatFullWithEmpty() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    ImmutableSegmentedDeque<int> deque1(m, length, bufSize);
    ImmutableSegmentedDeque<int> deque2;

    ImmutableSegmentedDeque<int>* result = deque1.concat(deque2);
    assert(result->getLength() == length);

    int i = 0;
    for (; i < length; ++i) {
        assert(result->get(i) == m[i]);
    }
}

void TestImmutableSegmentedDeque::testConcatEmptyWithFull() {
    int m[7] = {14, 15, 16, 17, 18, 19, 20};
    int length = 7;
    int bufSize = 6;

    ImmutableSegmentedDeque<int> deque1;
    ImmutableSegmentedDeque<int> deque2(m, length, bufSize);

    ImmutableSegmentedDeque<int>* result = deque1.concat(deque2);
    assert(result->getLength() == length);

    int i = 0;
    for (; i < length; ++i) {
        assert(result->get(i) == m[i]);
    }
}

void TestImmutableSegmentedDeque::testConcatEmptyWithEmpty() {
    ImmutableSegmentedDeque<int> deque1;
    ImmutableSegmentedDeque<int> deque2;

    ImmutableSegmentedDeque<int>* result = deque1.concat(deque2);
    assert(result->getLength() == 0);
}

