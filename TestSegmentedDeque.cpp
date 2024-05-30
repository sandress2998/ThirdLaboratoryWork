#include <cassert>
#include <stdexcept>
#include "SegmentedDeque.h"
#include "MutableArraySequence.h"
#include "LinkedList.h"
#include "DynamicArray.h"
#include "Sequence.h"
#include "TestSegmentedDeque.h"


void TestSegmentedDeque::testClass() {
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
}

void TestSegmentedDeque::testConstructors() {
    testDefaultConstructor();
    testArrayConstructor();
    testDynamicArrayConstructor();
    testLinkedListConstructor();
    testSequenceConstructor();
    testCopyConstructor();
}

void TestSegmentedDeque::testDefaultConstructor() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    SegmentedDeque<int> deque(bufSize);
    assert(deque.getBufSize() == bufSize);
    assert(deque.getLength() == 0);
}

void TestSegmentedDeque::testArrayConstructor() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    SegmentedDeque<int> deque(m, length, bufSize);
    assert(deque.getBufSize() == bufSize);
    assert(deque.getLength() == length);
    for (int i = 0; i < length; ++i) {
        assert(deque.get(i) == m[i]);
    }
}

void TestSegmentedDeque::testDynamicArrayConstructor() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    DynamicArray<int> dynamicArray(m, length);
    SegmentedDeque<int> deque(dynamicArray, bufSize);
    assert(deque.getBufSize() == bufSize);
    assert(deque.getLength() == length);
    for (int i = 0; i < length; ++i) {
        assert(deque.get(i) == m[i]);
    }
}

void TestSegmentedDeque::testLinkedListConstructor() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    LinkedList<int> linkedList(m, length);
    SegmentedDeque<int> deque(linkedList, bufSize);
    assert(deque.getBufSize() == bufSize);
    assert(deque.getLength() == length);
    for (int i = 0; i < length; ++i) {
        assert(deque.get(i) == m[i]);
    }

}

void TestSegmentedDeque::testSequenceConstructor() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    MutableArraySequence<int> sequence(m, length);
    SegmentedDeque<int> deque(sequence, bufSize);
    assert(deque.getBufSize() == bufSize);
    assert(deque.getLength() == length);
    for (int i = 0; i < length; ++i) {
        assert(deque.get(i) == m[i]);
    }
}

void TestSegmentedDeque::testCopyConstructor() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    SegmentedDeque<int> other(m, length);
    SegmentedDeque<int> deque(other, bufSize);
    assert(deque.getBufSize() == bufSize);
    assert(deque.getLength() == length);
    for (int i = 0; i < length; ++i) {
        assert(deque.get(i) == m[i]);
    }
}

void TestSegmentedDeque::testAssignmentOperator() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    int m2[5] = {0, 1, 2, 3, 4};
    int length2 = 5;
    int bufSize2 = 3;

    SegmentedDeque<int> deque(m, length, bufSize);
    SegmentedDeque<int> other(m2, length2, bufSize2);

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

void TestSegmentedDeque::testSquareAnkles() {
    testSquareAnklesValidIndex();
    testSquareAnklesInvalidIndex();
}

void TestSegmentedDeque::testSquareAnklesValidIndex() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    SegmentedDeque<int> deque(m + 1, length - 1, bufSize);
    deque.prepend(m[0]);

    for (int i = 0; i < length; ++i) {
        assert(deque[i] == m[i]);
    }

    int elem = 100;
    int index = 2;
    deque[index] = elem;
    assert(deque[index] == elem);
}

void TestSegmentedDeque::testSquareAnklesInvalidIndex() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    SegmentedDeque<int> deque(m + 1, length - 1, bufSize);
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

void TestSegmentedDeque::testGet() {
    testGetValidIndex();
    testGetInvalidIndex();
}

void TestSegmentedDeque::testGetValidIndex() {
    int m[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int length = 13;
    int bufSize = 6;

    SegmentedDeque<int> deque(m + 1, length - 1, bufSize);
    deque.prepend(m[0]);

    for (int i = 0; i < length; ++i) {
        assert(deque.get(i) == m[i]);
    }
}

void TestSegmentedDeque::testGetInvalidIndex() {
    int m[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int length = 13;
    int bufSize = 6;

    SegmentedDeque<int> deque(m + 1, length - 1, bufSize);
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

void TestSegmentedDeque::testSet() {
    testSetValidIndex();
    testSetInvalidIndex();
}

void TestSegmentedDeque::testSetValidIndex() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    SegmentedDeque<int> deque(m + 1, length - 1, bufSize);
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

void TestSegmentedDeque::testSetInvalidIndex() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    SegmentedDeque<int> deque(m + 1, length - 1, bufSize);
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

void TestSegmentedDeque::testGetFirst() {
    testGetFirstInFullDeque();
    testGetFirstInFullDeque();
}

void TestSegmentedDeque::testGetFirstInFullDeque() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    SegmentedDeque<int> deque(m + bufSize, length - bufSize, bufSize);

    int elem = 100;
    assert(deque.getFirst() == m[bufSize]);
    for (int i = bufSize - 1; i >= 0; --i) {
        deque.prepend(elem);
        assert(deque.getFirst() == elem);
        ++elem;
    }
}

void TestSegmentedDeque::testGetFirstInEmptyDeque() {
    int bufSize = 6;
    try {
        SegmentedDeque<int> deque(bufSize);
        deque.getFirst();
        assert(false);
    } catch(std::out_of_range) {}
}

void TestSegmentedDeque::testGetLast() {
    testGetLastInFullDeque();
    testGetLastInEmptyDeque();
}

void TestSegmentedDeque::testGetLastInFullDeque() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    SegmentedDeque<int> deque(m + bufSize, length - bufSize, bufSize);
    assert(deque.getFirst() == m[bufSize]);

    int elem = 100;
    for (int i = bufSize - 1; i >= 0; --i) {
        deque.append(elem);
        assert(deque.getLast() == elem);
        ++elem;
    }
}

void TestSegmentedDeque::testGetLastInEmptyDeque() {
    int bufSize = 6;
    try {
        SegmentedDeque<int> deque(bufSize);
        deque.getLast();
        assert(false);
    } catch(std::out_of_range) {}
}

void TestSegmentedDeque::testAppend() {
    testAppendInFullDeque();
    testAppendInEmptyDeque();
}

void TestSegmentedDeque::testAppendInFullDeque() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    SegmentedDeque<int> deque(m, length, bufSize);
    int newLength = length;

    for (int i = 0; i < length; ++i) {
        deque.append(m[i]);
        assert(deque.getLast() == m[i]);
        assert(deque.getLength() == ++newLength);
    }
}

void TestSegmentedDeque::testAppendInEmptyDeque() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    SegmentedDeque<int> deque(bufSize);
    int newLength = 0;

    for (int i = 0; i < length; ++i) {
        deque.append(m[i]);
        assert(deque.getLast() == m[i]);
        assert(deque.getLength() == ++newLength);
    }
}

void TestSegmentedDeque::testPrepend() {
    testPrependInFullDeque();
    testPrependInEmptyDeque();
}

void TestSegmentedDeque::testPrependInFullDeque() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    SegmentedDeque<int> deque(m, length, bufSize);
    int newLength = length;

    for (int i = 0; i < length; ++i) {
        deque.prepend(m[i]);
        assert(deque.getFirst() == m[i]);
        assert(deque.getLength() == ++newLength);
    }
}

void TestSegmentedDeque::testPrependInEmptyDeque() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    SegmentedDeque<int> deque(bufSize);
    int newLength = 0;

    for (int i = 0; i < length; ++i) {
        deque.prepend(m[i]);
        assert(deque.getFirst() == m[i]);
        assert(deque.getLength() == ++newLength);
    }
}

void TestSegmentedDeque::testInsertAt() {
    testInsertAtBeginningOfSegment();
    testInsertAtEndOfSegment();
    testInsertAtBeginningOfDeque();
    testInsertAtEndOfDeque();
    testInsertAtMiddleOfSegment();
    testInsertAtEmptyDeque();
    testInsertAtInvalidIndex();
}

void TestSegmentedDeque::testInsertAtBeginningOfSegment() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;
    int elem = 100;

    SegmentedDeque<int> deque(m, length, bufSize);
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

void TestSegmentedDeque::testInsertAtEndOfSegment() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;
    int elem = 100;

    SegmentedDeque<int> deque(m, length, bufSize);
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

void TestSegmentedDeque::testInsertAtBeginningOfDeque() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;
    int elem = 100;

    SegmentedDeque<int> deque(m, length, bufSize);
    int index = 0;
    deque.insertAt(index, elem);

    assert(deque.getLength() == length + 1);

    int i = 0;
    assert(deque[i++] == elem);
    for (; i < deque.getLength(); ++i) {
        assert(deque[i] == m[i - 1]);
    }
}

void TestSegmentedDeque::testInsertAtEndOfDeque() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;
    int elem = 100;

    SegmentedDeque<int> deque(m, length, bufSize);
    int index = length;
    deque.insertAt(index, elem);

    assert(deque.getLength() == length + 1);

    int i = 0;
    for (; i < deque.getLength() - 1; ++i) {
        assert(deque[i] == m[i]);
    }
    assert(deque[i] == elem);
}

void TestSegmentedDeque::testInsertAtMiddleOfSegment() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;
    int elem = 100;

    SegmentedDeque<int> deque(m, length, bufSize);
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


void TestSegmentedDeque::testInsertAtEmptyDeque() {
    int bufSize = 6;
    int elem = 100;

    SegmentedDeque<int> deque(bufSize);
    int index = 0;
    deque.insertAt(index, elem);
    assert(deque.getLength() == 1);
    assert(deque[0] == elem);
}

void TestSegmentedDeque::testInsertAtInvalidIndex() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;
    int elem = 100;

    SegmentedDeque<int> deque(m, length, bufSize);
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

void TestSegmentedDeque::testPopHead() {
    testPopHeadExtremeElementInSegment();
    testPopHeadNotExtremeElementInSegment();
    testPopHeadFromEmptyDeque();
}

void TestSegmentedDeque::testPopHeadExtremeElementInSegment() {
    int m[7] = {0, 1, 2, 3, 4, 5, 6};
    int length = 7;
    int bufSize = 6;

    SegmentedDeque<int> deque(m, length, bufSize);

    deque.popHead();
    assert(deque.getLength() == length - 1);
    for (int i = 0; i < deque.getLength(); ++i) {
        deque[i] = m[i];
    }
}

void TestSegmentedDeque::testPopHeadNotExtremeElementInSegment() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    SegmentedDeque<int> deque(m, length, bufSize);

    deque.popHead();
    assert(deque.getLength() == length - 1);
    for (int i = 0; i < deque.getLength(); ++i) {
        deque[i] = m[i];
    }
}

void TestSegmentedDeque::testPopHeadFromEmptyDeque() {
    try {
        SegmentedDeque<int> deque;
        deque.popHead();
        assert(false);
    } catch (std::out_of_range) {}
}

void TestSegmentedDeque::testPopTail() {
    testPopTailExtremeElementInSegment();
    testPopTailNotExtremeElementInSegment();
    testPopTailFromEmptyDeque();
}

void TestSegmentedDeque::testPopTailExtremeElementInSegment() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    SegmentedDeque<int> deque(m + 1, length - 1, bufSize);
    deque.prepend(m[0]);

    // удаление последнего элемента в сегменте
    deque.popTail();
    assert(deque.getLength() == length - 1);
    for (int i = 0; i < deque.getLength(); ++i) {
        deque[i] = m[i + 1];
    }
}

void TestSegmentedDeque::testPopTailNotExtremeElementInSegment() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    SegmentedDeque<int> deque(m, length, bufSize);

    deque.popTail();
    assert(deque.getLength() == length - 1);
    for (int i = 0; i < deque.getLength(); ++i) {
        deque[i] = m[i + 1];
    }
}

void TestSegmentedDeque::testPopTailFromEmptyDeque() {
    try {
        SegmentedDeque<int> deque;
        deque.popTail();
        assert(false);
    } catch (std::out_of_range) {}
}

void TestSegmentedDeque::testRemoveAt() {
    testRemoveAtSingleElementAtFirstSegment();
    testRemoveAtSingleElementAtLastSegment();
    testRemoveAtNotExtremeElement();
    testRemoveAtInvalidIndex();
}

void TestSegmentedDeque::testRemoveAtSingleElementAtLastSegment() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    SegmentedDeque<int> deque(m + 1, length - 1, bufSize);
    deque.prepend(m[0]);

    deque.removeAt(length - 1);
    assert(deque.getLength() == length - 1);
    for (int i = 0; i < deque.getLength(); ++i) {
        assert(deque[i] == m[i]);
    }
}

void TestSegmentedDeque::testRemoveAtSingleElementAtFirstSegment() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    SegmentedDeque<int> deque(m + 1, length - 1, bufSize);
    deque.prepend(m[0]);

    deque.removeAt(0);
    assert(deque.getLength() == length - 1);
    for (int i = 0; i < deque.getLength(); ++i) {
        assert(deque[i] == m[i + 1]);
    }
}

void TestSegmentedDeque::testRemoveAtNotExtremeElement() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    SegmentedDeque<int> deque(m + 1, length - 1, bufSize);
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

void TestSegmentedDeque::testRemoveAtInvalidIndex() {
    int m[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int bufSize = 6;

    SegmentedDeque<int> deque(m + 1, length - 1, bufSize);
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

