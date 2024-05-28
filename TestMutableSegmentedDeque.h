#pragma once
class TestMutableSegmentedDeque {
public:
    /*
    void testClass();
    void testConstructors();
    void testAssignmentOperator();
    void testSquareAnkles();
    void testGet();
    void testGetFirst();
    void testGetLast();
    void testSet();
    void testAppend();
    void testPrepend();
    void testInsertAt();
    void testPopHead();
    void testPopTail();
    void testRemoveAt();
    void testConcat();
    void testGetSubsequence();
    */
    void testClass();

    void testConstructors();
    void testDefaultConstructor();
    void testArrayConstructor();
    void testDynamicArrayConstructor();
    void testLinkedListConstructor();
    void testSequenceConstructor();
    void testCopyConstructor();

    void testAssignmentOperator();

    void testSquareAnkles();
    void testSquareAnklesValidIndex();
    void testSquareAnklesInvalidIndex();

    void testGet();
    void testGetValidIndex();
    void testGetInvalidIndex();

    void testSet();
    void testSetValidIndex();
    void testSetInvalidIndex();

    void testGetFirst();
    void testGetFirstInFullDeque();
    void testGetFirstInEmptyDeque();

    void testGetLast();
    void testGetLastInFullDeque();
    void testGetLastInEmptyDeque();

    void testAppend();
    void testAppendInFullDeque();
    void testAppendInEmptyDeque();

    void testPrepend();
    void testPrependInFullDeque();
    void testPrependInEmptyDeque();

    void testInsertAt();
    void testInsertAtBeginningOfSegment();
    void testInsertAtEndOfSegment();
    void testInsertAtBeginningOfDeque();
    void testInsertAtEndOfDeque();
    void testInsertAtMiddleOfSegment();
    void testInsertAtEmptyDeque();
    void testInsertAtInvalidIndex();

    void testPopHead();
    void testPopHeadExtremeElementInSegment();
    void testPopHeadNotExtremeElementInSegment();
    void testPopHeadFromEmptyDeque();

    void testPopTail();
    void testPopTailExtremeElementInSegment();
    void testPopTailNotExtremeElementInSegment();
    void testPopTailFromEmptyDeque();

    void testRemoveAt();
    void testRemoveAtSingleElementAtFirstSegment();
    void testRemoveAtSingleElementAtLastSegment();
    void testRemoveAtNotExtremeElement();
    void testRemoveAtInvalidIndex();

    void testGetSubsequence();
    void testGetSubsequenceStartIndexLessThanEndIndex();
    void testGetSubsequenceStartIndexEqualWithEndIndex();
    void testGetSubsequenceInvalidIndices();

    void testConcat();
    void testConcatFullWithFull();
    void testConcatFullWithEmpty();
    void testConcatEmptyWithFull();
    void testConcatEmptyWithEmpty();
};
