// #pragma once
#include "header.hpp"
#include "List.hpp"

void pushBackListTest() {
    List<int> x;
    for (int i = 0; i < 10; i++) {
        x.pushBack(i);
    }
    x.printListReverse();
    std::cout << "====================" << std::endl;
    x.printList();
}

void pushFrontListTest() {
    List<int> x;
    for (int i = 10; i >= 0; i--) {
        x.pushFront(i);
    }
    x.printListReverse();
    std::cout << "====================" << std::endl;
    x.printList();
}

void popFrontListTest() {
    List<int> x;
    for (int i = 10; i >= 0; i--) {
        x.pushFront(i);
    }
    for (int i = 10; i >= 0; i--) {
        x.popFront();
    }
    x.printList();
}

void popBackListTest() {
    List<int> x;
    for (int i = 10; i >= 0; i--) {
        x.pushFront(i);
    }
    for (int i = 4; i >= 0; i--) {
        x.popBack();
    }
    x.printList();
}

void frontListTest() {
    List<int> x;
    for (int i = 0; i < 6; i++) {
        x.pushBack(i);
    }
    assert(x.front() == 0);
    x.front() = 123;
    assert(x.front() == 123);
}

void backListTest() {
    List<int> x;
    for (int i = 0; i < 6; i++) {
        x.pushBack(i);
    }
    assert(x.back() == 5);
    x.back() = 123;
    assert(x.back() == 123);
}

void insertListTest() {
    List<int> x;
    x.pushBack(0);
    x.pushBack(1);
    x.pushBack(3);
    x.pushBack(4);
    x.insert(x.begin() + 2, 123);
    assert(*(x.begin() + 2) == 123);
}