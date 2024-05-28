#include <cassert>
#include "MutableSegmentedDeque.h"
#include "MutableArraySequence.h"
#include "LinkedList.h"
#include "DynamicArray.h"
#include "Sequence.h"
#include "TestMutableSegmentedDeque.h"


void TestMutableSegmentedDeque::testClass() {
    testConstructors();
    testAssignmentOperator();
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
    testConcat();
    testGetSubsequence();
}

void TestMutableSegmentedDeque::testConstructors() {
    testDefaultConstructor();
    testArrayConstructor();
    testDynamicArrayConstructor();
    testLinkedListConstructor();
    testSequenceConstructor();
    testCopyConstructor();
}

void TestMutableSegmentedDeque::testDefaultConstructor() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    MutableSegmentedDeque<int> deque(bufSize);
    assert(deque.getBufSize() == bufSize);
    assert(deque.getLength() == 0);
}

void TestMutableSegmentedDeque::testArrayConstructor() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    MutableSegmentedDeque<int> deque(m, length, bufSize);
    assert(deque.getBufSize() == bufSize);
    assert(deque.getLength() == length);
    for (int i = 0; i < length; ++i) {
        assert(deque.get(i) == m[i]);
    }
}

void TestMutableSegmentedDeque::testDynamicArrayConstructor() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    DynamicArray<int> dynamicArray(m, length);
    MutableSegmentedDeque<int> deque(dynamicArray, bufSize);
    assert(deque.getBufSize() == bufSize);
    assert(deque.getLength() == length);
    for (int i = 0; i < length; ++i) {
        assert(deque.get(i) == m[i]);
    }
}

void TestMutableSegmentedDeque::testLinkedListConstructor() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    LinkedList<int> linkedList(m, length);
    MutableSegmentedDeque<int> deque(linkedList, bufSize);
    assert(deque.getBufSize() == bufSize);
    assert(deque.getLength() == length);
    for (int i = 0; i < length; ++i) {
        assert(deque.get(i) == m[i]);
    }

}

void TestMutableSegmentedDeque::testSequenceConstructor() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    MutableArraySequence<int> sequence(m, length);
    MutableSegmentedDeque<int> deque(sequence, bufSize);
    assert(deque.getBufSize() == bufSize);
    assert(deque.getLength() == length);
    for (int i = 0; i < length; ++i) {
        assert(deque.get(i) == m[i]);
    }
}

void TestMutableSegmentedDeque::testCopyConstructor() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    MutableSegmentedDeque<int> other(m, length);
    MutableSegmentedDeque<int> deque(other, bufSize);
    assert(deque.getBufSize() == bufSize);
    assert(deque.getLength() == length);
    for (int i = 0; i < length; ++i) {
        assert(deque.get(i) == m[i]);
    }
}

void TestMutableSegmentedDeque::testAssignmentOperator() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    int m2[5] = {0, 1, 2, 3, 4};
    int length2 = 5;
    int bufSize2 = 3;

    MutableSegmentedDeque<int> deque(m, length, bufSize);
    MutableSegmentedDeque<int> other(m2, length2, bufSize2);

    other = deque;
    assert(other.getLength() == deque.getLength());
    assert(other.getBufSize() == deque.getBufSize());
    for (int i = 0; i < length; ++i) {
        assert(other[i] == deque[i]);
    }

    int index = 4;
    int elemBefore = deque[index];
    int elemAfter = 100;
    deque[index] = elemAfter;

    for (int i = 0; i < length; ++i) {
        if (i != index) {
            assert(other[i] == deque[i]);
        } else {
            assert(other[i] == elemBefore);
            assert(deque[i] == elemAfter);
        }
    }
}

void TestMutableSegmentedDeque::testSquareAnkles() {
    testSquareAnklesValidIndex();
    testSquareAnklesInvalidIndex();
}

void TestMutableSegmentedDeque::testSquareAnklesValidIndex() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    MutableSegmentedDeque<int> deque(m + 1, length - 1, bufSize);
    deque.prepend(m[0]);

    for (int i = 0; i < length; ++i) {
        assert(deque[i] == m[i]);
    }

    int elem = 100;
    int index = 2;
    deque[index] = elem;
    assert(deque[index] == elem);
}

void TestMutableSegmentedDeque::testSquareAnklesInvalidIndex() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    MutableSegmentedDeque<int> deque(m + 1, length - 1, bufSize);
    deque.prepend(m[0]);

    try {
        deque[-1];
        assert(false);
    } catch (std::out_of_range) {}
    try {
        deque[length];
        assert(false);
    } catch (std::out_of_range) {}
}

void TestMutableSegmentedDeque::testGet() {
    testGetValidIndex();
    testGetInvalidIndex();
}

void TestMutableSegmentedDeque::testGetValidIndex() {
    int m[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int length = 13;
    int bufSize = 6;

    MutableSegmentedDeque<int> deque(m + 1, length - 1, bufSize);
    deque.prepend(m[0]);

    for (int i = 0; i < length; ++i) {
        assert(deque.get(i) == m[i]);
    }
}

void TestMutableSegmentedDeque::testGetInvalidIndex() {
    int m[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int length = 13;
    int bufSize = 6;

    MutableSegmentedDeque<int> deque(m + 1, length - 1, bufSize);
    deque.prepend(m[0]);

    try {
        deque.get(-1);
        assert(false);
    } catch (std::out_of_range) {}
    try {
        deque.get(length);
        assert(false);
    } catch (std::out_of_range) {}
}

void TestMutableSegmentedDeque::testSet() {
    testSetValidIndex();
    testSetInvalidIndex();
}

void TestMutableSegmentedDeque::testSetValidIndex() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    MutableSegmentedDeque<int> deque(m + 1, length - 1, bufSize);
    deque.prepend(m[0]);

    int elem = 100;
    for (int i = 0; i < length - 1; ++i) {
        deque.set(i, elem);
    }

    for (int i = 0; i < length - 1; ++i) {
        assert(deque.get(i) == elem);
    }
    assert(deque.get(length - 1) == m[length - 1]); // проверяем, что нетронутый элемент не изменился.
}

void TestMutableSegmentedDeque::testSetInvalidIndex() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    MutableSegmentedDeque<int> deque(m + 1, length - 1, bufSize);
    deque.prepend(m[0]);

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

void TestMutableSegmentedDeque::testGetFirst() {
    testGetFirstInFullDeque();
    testGetFirstInFullDeque();
}

void TestMutableSegmentedDeque::testGetFirstInFullDeque() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    MutableSegmentedDeque<int> deque(m + bufSize, length - bufSize, bufSize);

    int elem = 100;
    assert(deque.getFirst() == m[bufSize]);
    for (int i = bufSize - 1; i >= 0; --i) {
        deque.prepend(elem);
        assert(deque.getFirst() == elem);
        ++elem;
    }
}

void TestMutableSegmentedDeque::testGetFirstInEmptyDeque() {
    int bufSize = 6;
    try {
        MutableSegmentedDeque<int> deque(bufSize);
        deque.getFirst();
        assert(false);
    } catch(std::out_of_range) {}
}

void TestMutableSegmentedDeque::testGetLast() {
    testGetLastInFullDeque();
    testGetLastInEmptyDeque();
}

void TestMutableSegmentedDeque::testGetLastInFullDeque() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    MutableSegmentedDeque<int> deque(m + bufSize, length - bufSize, bufSize);
    assert(deque.getFirst() == m[bufSize]);

    int elem = 100;
    for (int i = bufSize - 1; i >= 0; --i) {
        deque.append(elem);
        assert(deque.getLast() == elem);
        ++elem;
    }
}

void TestMutableSegmentedDeque::testGetLastInEmptyDeque() {
    int bufSize = 6;
    try {
        MutableSegmentedDeque<int> deque(bufSize);
        deque.getLast();
        assert(false);
    } catch(std::out_of_range) {}
}

void TestMutableSegmentedDeque::testAppend() {
    testAppendInFullDeque();
    testAppendInEmptyDeque();
}

void TestMutableSegmentedDeque::testAppendInFullDeque() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    MutableSegmentedDeque<int> deque(m, length, bufSize);
    int newLength = length;

    for (int i = 0; i < length; ++i) {
        deque.append(m[i]);
        assert(deque.getLast() == m[i]);
        assert(deque.getLength() == ++newLength);
    }
}

void TestMutableSegmentedDeque::testAppendInEmptyDeque() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    MutableSegmentedDeque<int> deque(bufSize);
    int newLength = 0;

    for (int i = 0; i < length; ++i) {
        deque.append(m[i]);
        assert(deque.getLast() == m[i]);
        assert(deque.getLength() == ++newLength);
    }
}

void TestMutableSegmentedDeque::testPrepend() {
    testPrependInFullDeque();
    testPrependInEmptyDeque();
}

void TestMutableSegmentedDeque::testPrependInFullDeque() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    MutableSegmentedDeque<int> deque(m, length, bufSize);
    int newLength = length;

    for (int i = 0; i < length; ++i) {
        deque.prepend(m[i]);
        assert(deque.getFirst() == m[i]);
        assert(deque.getLength() == ++newLength);
    }
}

void TestMutableSegmentedDeque::testPrependInEmptyDeque() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    MutableSegmentedDeque<int> deque(bufSize);
    int newLength = 0;

    for (int i = 0; i < length; ++i) {
        deque.prepend(m[i]);
        assert(deque.getFirst() == m[i]);
        assert(deque.getLength() == ++newLength);
    }
}

void TestMutableSegmentedDeque::testInsertAt() {
    testInsertAtBeginningOfSegment();
    testInsertAtEndOfSegment();
    testInsertAtBeginningOfDeque();
    testInsertAtEndOfDeque();
    testInsertAtMiddleOfSegment();
    testInsertAtEmptyDeque();
    testInsertAtInvalidIndex();
}

void TestMutableSegmentedDeque::testInsertAtBeginningOfSegment() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;
    int elem = 100;

    MutableSegmentedDeque<int> deque(m, length, bufSize);
    int index = bufSize;
    deque.insertAt(index, elem);

    assert(deque.getLength() == length + 1);

    int i = 0;
    for (; i < index; ++i) {
        assert(deque[i] == m[i]);
    }
    assert(deque[i++] == elem);
    for (; i < deque.getLength(); ++i) {
        assert(deque[i] == m[i - 1]);
    }
}

void TestMutableSegmentedDeque::testInsertAtEndOfSegment() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;
    int elem = 100;

    MutableSegmentedDeque<int> deque(m, length, bufSize);
    int index = bufSize - 1;
    deque.insertAt(index, elem);

    assert(deque.getLength() == length + 1);

    int i = 0;
    for (; i < index; ++i) {
        assert(deque[i] == m[i]);
    }
    assert(deque[i++] == elem);
    for (; i < deque.getLength(); ++i) {
        assert(deque[i] == m[i - 1]);
    }
}

void TestMutableSegmentedDeque::testInsertAtBeginningOfDeque() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;
    int elem = 100;

    MutableSegmentedDeque<int> deque(m, length, bufSize);
    int index = 0;
    deque.insertAt(index, elem);

    assert(deque.getLength() == length + 1);

    int i = 0;
    assert(deque[i++] == elem);
    for (; i < deque.getLength(); ++i) {
        assert(deque[i] == m[i - 1]);
    }
}

void TestMutableSegmentedDeque::testInsertAtEndOfDeque() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;
    int elem = 100;

    MutableSegmentedDeque<int> deque(m, length, bufSize);
    int index = length;
    deque.insertAt(index, elem);

    assert(deque.getLength() == length + 1);

    int i = 0;
    for (; i < deque.getLength() - 1; ++i) {
        assert(deque[i] == m[i]);
    }
    assert(deque[i] == elem);
}

void TestMutableSegmentedDeque::testInsertAtMiddleOfSegment() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;
    int elem = 100;

    MutableSegmentedDeque<int> deque(m, length, bufSize);
    int index = bufSize / 2;
    deque.insertAt(index, elem);

    assert(deque.getLength() == length + 1);

    int i = 0;
    for (; i < index; ++i) {
        assert(deque[i] == m[i]);
    }
    assert(deque[i++] == elem);
    for (; i < deque.getLength(); ++i) {
        assert(deque[i] == m[i - 1]);
    }
}


void TestMutableSegmentedDeque::testInsertAtEmptyDeque() {
    int bufSize = 6;
    int elem = 100;

    MutableSegmentedDeque<int> deque(bufSize);
    int index = 0;
    deque.insertAt(index, elem);
    assert(deque.getLength() == 1);
    assert(deque[0] == elem);
}

void TestMutableSegmentedDeque::testInsertAtInvalidIndex() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;
    int elem = 100;

    MutableSegmentedDeque<int> deque(m, length, bufSize);
    int index = bufSize - 1;
    deque.insertAt(index, elem);

    assert(deque.getLength() == length + 1);

    try {
        deque.insertAt(-1, elem);
        assert(false);
    } catch (std::out_of_range) {}
    try {
        deque.insertAt(deque.getLength() + 1, elem);
        assert(false);
    } catch (std::out_of_range) {}
}

void TestMutableSegmentedDeque::testPopHead() {
    testPopHeadExtremeElementInSegment();
    testPopHeadNotExtremeElementInSegment();
    testPopHeadFromEmptyDeque();
}

void TestMutableSegmentedDeque::testPopHeadExtremeElementInSegment() {
    int m[7] = {0, 1, 2, 3, 4, 5, 6};
    int length = 7;
    int bufSize = 6;

    MutableSegmentedDeque<int> deque(m, length, bufSize);

    deque.popHead();
    assert(deque.getLength() == length - 1);
    for (int i = 0; i < deque.getLength(); ++i) {
        deque[i] = m[i];
    }
}

void TestMutableSegmentedDeque::testPopHeadNotExtremeElementInSegment() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    MutableSegmentedDeque<int> deque(m, length, bufSize);

    deque.popHead();
    assert(deque.getLength() == length - 1);
    for (int i = 0; i < deque.getLength(); ++i) {
        deque[i] = m[i];
    }
}

void TestMutableSegmentedDeque::testPopHeadFromEmptyDeque() {
    try {
        MutableSegmentedDeque<int> deque;
        deque.popHead();
        assert(false);
    } catch (std::out_of_range) {}
}

void TestMutableSegmentedDeque::testPopTail() {
    testPopTailExtremeElementInSegment();
    testPopTailNotExtremeElementInSegment();
    testPopTailFromEmptyDeque();
}

void TestMutableSegmentedDeque::testPopTailExtremeElementInSegment() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    MutableSegmentedDeque<int> deque(m + 1, length - 1, bufSize);
    deque.prepend(m[0]);

    // удаление последнего элемента в сегменте
    deque.popTail();
    assert(deque.getLength() == length - 1);
    for (int i = 0; i < deque.getLength(); ++i) {
        deque[i] = m[i + 1];
    }
}

void TestMutableSegmentedDeque::testPopTailNotExtremeElementInSegment() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    MutableSegmentedDeque<int> deque(m, length, bufSize);

    deque.popTail();
    assert(deque.getLength() == length - 1);
    for (int i = 0; i < deque.getLength(); ++i) {
        deque[i] = m[i + 1];
    }
}

void TestMutableSegmentedDeque::testPopTailFromEmptyDeque() {
    try {
        MutableSegmentedDeque<int> deque;
        deque.popTail();
        assert(false);
    } catch (std::out_of_range) {}
}

void TestMutableSegmentedDeque::testRemoveAt() {
    testRemoveAtSingleElementAtFirstSegment();
    testRemoveAtSingleElementAtLastSegment();
    testRemoveAtNotExtremeElement();
    testRemoveAtInvalidIndex();
}

void TestMutableSegmentedDeque::testRemoveAtSingleElementAtLastSegment() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    MutableSegmentedDeque<int> deque(m + 1, length - 1, bufSize);
    deque.prepend(m[0]);

    deque.removeAt(length - 1);
    assert(deque.getLength() == length - 1);
    for (int i = 0; i < deque.getLength(); ++i) {
        assert(deque[i] == m[i]);
    }
}

void TestMutableSegmentedDeque::testRemoveAtSingleElementAtFirstSegment() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    MutableSegmentedDeque<int> deque(m + 1, length - 1, bufSize);
    deque.prepend(m[0]);

    deque.removeAt(0);
    assert(deque.getLength() == length - 1);
    for (int i = 0; i < deque.getLength(); ++i) {
        assert(deque[i] == m[i + 1]);
    }
}

void TestMutableSegmentedDeque::testRemoveAtNotExtremeElement() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    MutableSegmentedDeque<int> deque(m + 1, length - 1, bufSize);
    deque.prepend(m[0]);

    int index = 5;
    deque.removeAt(index);
    assert(deque.getLength() == length - 1);
    int i = 0;
    for (; i < index; ++i) {
        assert(deque[i] == m[i]);
    }
    for (; i < deque.getLength(); ++i) {
        assert(deque[i] == m[i + 1]);
    }
}

void TestMutableSegmentedDeque::testRemoveAtInvalidIndex() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    MutableSegmentedDeque<int> deque(m + 1, length - 1, bufSize);
    deque.prepend(m[0]);

    try {
        deque.removeAt(-1);
        assert(false);
    } catch (std::out_of_range) {}
    try {
        deque.removeAt(deque.getLength());
        assert(false);
    } catch (std::out_of_range) {}
}

void TestMutableSegmentedDeque::testGetSubsequence() {
    testGetSubsequenceStartIndexLessThanEndIndex();
    testGetSubsequenceStartIndexEqualWithEndIndex();
    testGetSubsequenceInvalidIndices();
}

void TestMutableSegmentedDeque::testGetSubsequenceStartIndexLessThanEndIndex() {
int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    MutableSegmentedDeque<int> deque(m, length, bufSize);

    int startIndex = 3;
    int endIndex = 7;

    Sequence<int>* result = deque.getSubsequence(startIndex, endIndex);
    assert(result->getLength() == endIndex - startIndex + 1);
    for (int i = startIndex; i < result->getLength(); ++i) {
        assert(result->get(i - startIndex) == m[i]);
    }
    delete result;
}

void TestMutableSegmentedDeque::testGetSubsequenceStartIndexEqualWithEndIndex() {
int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    MutableSegmentedDeque<int> deque(m, length, bufSize);

    int startIndex = 3;
    int endIndex = 3;

    Sequence<int>* result = deque.getSubsequence(startIndex, endIndex);
    assert(result->getLength() == 1);
    delete result;
}

void TestMutableSegmentedDeque::testGetSubsequenceInvalidIndices() {
int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    MutableSegmentedDeque<int> deque(m, length, bufSize);

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

void TestMutableSegmentedDeque::testConcat() {
    testConcatFullWithFull();
    testConcatFullWithEmpty();
    testConcatEmptyWithFull();
    testConcatEmptyWithEmpty();
}

void TestMutableSegmentedDeque::testConcatFullWithFull() {
    int m1[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length1 = 14;
    int bufSize1 = 6;

    int m2[7] = {14, 15, 16, 17, 18, 19, 20};
    int length2 = 7;
    int bufSize2 = 5;

    MutableSegmentedDeque<int> deque1(m1, length1, bufSize1);
    MutableSegmentedDeque<int> deque2(m2, length2, bufSize2);

    MutableSegmentedDeque<int>* result = deque1.concat(deque2);
    assert(result->getLength() == length1 + length2);

    int i = 0;
    for (; i < length1; ++i) {
        assert(result->get(i) == m1[i]);
    }
    for (; i < length2; ++i) {
        assert(result->get(i) == m2[i - length1]);
    }
}

void TestMutableSegmentedDeque::testConcatFullWithEmpty() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    MutableSegmentedDeque<int> deque1(m, length, bufSize);
    MutableSegmentedDeque<int> deque2;

    MutableSegmentedDeque<int>* result = deque1.concat(deque2);
    assert(result->getLength() == length);

    int i = 0;
    for (; i < length; ++i) {
        assert(result->get(i) == m[i]);
    }
}

void TestMutableSegmentedDeque::testConcatEmptyWithFull() {
    int m[7] = {14, 15, 16, 17, 18, 19, 20};
    int length = 7;
    int bufSize = 6;

    MutableSegmentedDeque<int> deque1;
    MutableSegmentedDeque<int> deque2(m, length, bufSize);

    MutableSegmentedDeque<int>* result = deque1.concat(deque2);
    assert(result->getLength() == length);

    int i = 0;
    for (; i < length; ++i) {
        assert(result->get(i) == m[i]);
    }
}

void TestMutableSegmentedDeque::testConcatEmptyWithEmpty() {
    MutableSegmentedDeque<int> deque1;
    MutableSegmentedDeque<int> deque2;

    MutableSegmentedDeque<int>* result = deque1.concat(deque2);
    assert(result->getLength() == 0);
}
