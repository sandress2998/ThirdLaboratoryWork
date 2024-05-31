#include "UI.h"
#include "Sequence.h" // для функции printSubsequence
#include "MutableArraySequence.h"
#include "MutableSegmentedDeque.h"
#include "Complex.h"
#include "Person.h"
#include <string>
#include <iostream>
#include <stdexcept>

template <typename T>
class UserSequence {

private:

    MutableArraySequence<T>* sequence = new MutableArraySequence<T>;

public:

    ~UserSequence() {
        delete sequence;
    }

    UserSequence() = default;

    void setValue() {
        int index;
        std::cout << "Enter the index of element: ";
        std::cin >> index;
        std::cout << "Enter the value of element number " << index << ": ";
        try {
            std::cin >> (*sequence)[index];
        } catch (const std::out_of_range& ex) {
            std::cout << ex.what();
        }
    }

    void printValue() {
        int index;
        std::cout << "Enter the index of element: ";
        std::cin >> index;
        try {
            std::cout << sequence->get(index) << std::endl;
        } catch (const std::out_of_range& ex) {
            std::cout << ex.what();
        }
    }
    void insertValue() {
        int index;
        std::cout << "Enter the index of element: ";
        std::cin >> index;
        std::cout << "Enter the value of element number " << index << ": ";
        try {
            T item;
            std::cin >> item;
            sequence->insertAt(index, item);
            std::cout << "The element was inserted at sequence.\n";
        } catch (const std::out_of_range& ex) {
            std::cout << ex.what();
        }
    }

    void appendValue() {
        std::cout << "Enter the value of element: ";
        T item;
        std::cin >> item;
        sequence->append(item);
    }

    void prependValue() {
        std::cout << "Enter the value of element: ";
        T item;
        std::cin >> item;
        sequence->prepend(item);
    }

    void printFirst() {
        try {
            std::cout << sequence->getFirst();
        } catch(std::out_of_range& ex) {
            std::cout << ex.what();
        }
    }

    void printLast() {
        try {
            std::cout << sequence->getLast();
        } catch(std::out_of_range& ex) {
            std::cout << ex.what();
        }
    }

    void printSequence() {
        if (sequence->getLength() == 0) {
            std::cout << "Sequence is empty.\n";
            return;
        }
        std::cout << (*sequence);
    }

    void printSubsequence() {
        int start;
        int end;
        std::cout << "Enter start and end indices of your subsequence: ";
        try {
            std::cin >> start >> end;
            Sequence<T>* subsequence = sequence->getSubsequence(start, end);
            std::cout << (*subsequence);
            delete subsequence;
        } catch (std::out_of_range& ex) {
            std::cout << ex.what();
        }
    }
};

template <typename T>
class SequenceUI {

private:

    void startSequence() {
        UserSequence<T> userSequence;

        std::cout << "\nNow you can select what to do with your array:\n"
        << "print_array,\n"
        << "print_element,\n"
        << "set,\n"
        << "insert,\n"
        << "append,\n"
        << "prepend,\n"
        << "print_first,\n"
        << "print_last,\n"
        << "print_subsequence,\n"
        << "delete.\n\n";

        std::string action;
        while (true) {
            std::cout << "Enter the action: ";
            std::cin >> action;
            if (action == "print_array") userSequence.printSequence();
            else if (action == "print_element") userSequence.printValue();
            else if (action == "set") userSequence.setValue();
            else if (action == "insert") userSequence.insertValue();
            else if (action == "append") userSequence.appendValue();
            else if (action == "prepend") userSequence.prependValue();
            else if (action == "print_first") userSequence.printFirst();
            else if (action == "print_last") userSequence.printLast();
            else if (action == "print_subsequence") userSequence.printSubsequence();
            else if (action == "delete") break;
        }
        // после этого удаляется userSequence и срабатывает его деконструктор.
    }

public:

    std::string start() {
        std::string action;
        startSequence();
        std::cout << "If you want to end the program --> end.\n" << "If you want to start again --> again.\n";
        std::cin >> action;
        return action;
    }
};

template <typename T>
class UserDeque {

private:

    MutableSegmentedDeque<T>* deque = new MutableSegmentedDeque<T>;

public:

    ~UserDeque() {
        delete deque;
    }

    UserDeque() = default;

    void setValue() {
        int index;
        std::cout << "Enter the index of element: ";
        std::cin >> index;
        std::cout << "Enter the value of element number " << index << ": ";
        try {
            std::cin >> (*deque)[index];
        } catch (const std::out_of_range& ex) {
            std::cout << ex.what();
        }
        std::cin.ignore();
    }

    void printValue() {
        int index;
        std::cout << "Enter the index of element: ";
        std::cin >> index;
        try {
            std::cout << deque->get(index) << std::endl;
        } catch (const std::out_of_range& ex) {
            std::cout << ex.what();
        }
        std::cin.ignore();
    }
    void insertValue() {
        int index;
        std::cout << "Enter the index of element: ";
        std::cin >> index;
        std::cout << "Enter the value of element number " << index << ": ";
        try {
            T item;
            std::cin >> item;
            deque->insertAt(index, item);
            std::cout << "The element was inserted at deque.\n";
        } catch (const std::out_of_range& ex) {
            std::cout << ex.what();
        }
        std::cin.ignore();
    }

    void appendValue() {
        std::cout << "Enter the value of element: ";
        T item;
        std::cin >> item;
        deque->append(item);
        std::cin.ignore();
    }

    void prependValue() {
        std::cout << "Enter the value of element: ";
        T item;
        std::cin >> item;
        deque->prepend(item);
        std::cin.ignore();
    }

    void popHead() {
        try {
            deque->popHead();
            std::cout << "You removed last element.\n";
        } catch (std::out_of_range& ex) {
            std::cout << ex.what();
        }
    }

    void popTail() {
        try {
            deque->popTail();
            std::cout << "You removed first element.\n";
        } catch (std::out_of_range& ex) {
            std::cout << ex.what();
        }
    }

    void removeAt() {
        int index;
        std::cout << "Enter index of element to remove: ";
        std::cin >> index;
        try {
            deque->removeAt(index);
            std::cout << "You removed element with index " << index << ".\n";
        } catch (std::out_of_range& ex) {
            std::cout << ex.what();
        }
        std::cin.ignore();
    }

    void printFirst() {
        try {
            std::cout << deque->getFirst() << "\n";
        } catch(std::out_of_range& ex) {
            std::cout << ex.what();
        }
    }

    void printLast() {
        try {
            std::cout << deque->getLast() << "\n";
        } catch(std::out_of_range& ex) {
            std::cout << ex.what();
        }
    }

    void printDeque() {
        if (deque->getLength() == 0) {
            std::cout << "Deque is empty.\n";
            return;
        }
        std::cout << (*deque);
    }

    void printSubsequence() {
        int start;
        int end;
        std::cout << "Enter start and end indices of your subdeque: ";
        try {
            std::cin >> start >> end;
            Sequence<T>* subSequence = deque->getSubsequence(start, end);
            std::cout << (*subSequence);
            delete subSequence;
        } catch (std::out_of_range& ex) {
            std::cout << ex.what();
        }
        std::cin.ignore();
    }
};

template <typename T>
class DequeUI {

private:

    void startDeque() {
        UserDeque<T> userDeque;

        std::cout << "\nNow you can select what to do with your deque:\n"
        << "print_deque,\n"
        << "print_element,\n"
        << "set,\n"
        << "insert,\n"
        << "append,\n"
        << "prepend,\n"
        << "pop_head,\n"
        << "pop_tail,\n"
        << "remove,\n"
        << "print_first,\n"
        << "print_last,\n"
        << "print_subsequence\n"
        << "delete\n\n";

        std::string action;
        while (true) {
            std::cout << "Enter the action: ";
            std::cin >> action;
            //std::cout << "action = " << action;
            if (action == "print_deque") userDeque.printDeque();
            else if (action == "print_element") userDeque.printValue();
            else if (action == "set") userDeque.setValue();
            else if (action == "insert") userDeque.insertValue();
            else if (action == "append") userDeque.appendValue();
            else if (action == "prepend") userDeque.prependValue();
            else if (action == "pop_head") userDeque.popHead();
            else if (action == "pop_tail") userDeque.popTail();
            else if (action == "remove") userDeque.removeAt();
            else if (action == "print_first") userDeque.printFirst();
            else if (action == "print_last") userDeque.printLast();
            else if (action == "print_subsequence") userDeque.printSubsequence();
            else if (action == "delete") break;
        }
        // после этого удаляется userDeque и срабатывает его деконструктор.
    }

public:

    std::string start() {
        std::string action;
        startDeque();
        std::cout << "If you want to end the program --> end.\n" << "If you want to start again --> again.\n";
        std::cin >> action;
        return action;
    }
};


std::string selectElementType() {
    std::cout << "Select the type of elements in sequence:\n"
        << "int --> int,\n"
        << "double --> double,\n"
        << "char --> char.\n"
        << "Complex --> complex.\n"
        << "Person --> person.\n";
    std::string elementType;
    std::cin >> elementType;
    while (elementType != "int" && elementType != "double" && elementType != "char" && elementType != "complex" && elementType != "person") {
        std::cout << "You entered the invalid command. Try again.\n";
        std::cin >> elementType;
    }
    return elementType;
}

std::string selectSequenceType() {
    std::cout << "Select the type of sequence:\n"
        << "Deque --> deque,\n"
        << "Array --> array,\n";
    std::string sequenceType;
    std::cin >> sequenceType;
    while (sequenceType != "deque" && sequenceType != "array") {
        std::cout << "You entered the invalid command. Try again.\n";
        std::cin >> sequenceType;
    }
    return sequenceType;
}

void startUI() {
    std::cout << "This is the program to work with the deque. Let's start!\n\n\n";
    std::string sequenceType;
    std::string elementType;
    std::string doNext;
    while (true){
        sequenceType = selectSequenceType();
        elementType = selectElementType();
        if (sequenceType == "deque" && elementType == "int") {
            DequeUI<int> ui;
            doNext = ui.start();
        } else if (sequenceType == "deque" && elementType == "double") {
            DequeUI<double> ui;
            doNext = ui.start();
        } else if (sequenceType == "deque" && elementType == "char") {
            DequeUI<char> ui;
            doNext = ui.start();
        } else if (sequenceType == "deque" && elementType == "complex") {
            DequeUI<Complex> ui;
            doNext = ui.start();
        } else if (sequenceType == "deque" && elementType == "person") {
            DequeUI<Person> ui;
            doNext = ui.start();
        } else if (sequenceType == "array" && elementType == "int") {
            SequenceUI<int> ui;
            doNext = ui.start();
        } else if (sequenceType == "array" && elementType == "double") {
            SequenceUI<double> ui;
            doNext = ui.start();
        } else if (sequenceType == "array" && elementType == "char") {
            SequenceUI<char> ui;
            doNext = ui.start();
        } else if (sequenceType == "array" && elementType == "complex") {
            SequenceUI<Complex> ui;
            doNext = ui.start();
        } else if (sequenceType == "array" && elementType == "person") {
            SequenceUI<Person> ui;
            doNext = ui.start();
        }
        while (doNext != "again" && doNext != "end") {
            std::cout << "Incorrect input. Try again.\n";
            std::cin >> doNext;
        }
        if (doNext == "end") break;
    }
    std::cout << "\nThe end of program.\n";
}


