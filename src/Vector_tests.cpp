// // #pragma once
// #include "header.hpp"
#include "Vector.hpp"

using namespace std::chrono;

void pushBackTest() {
    Vector<int> a;
    for (int i = 0; i < 6; i++) {
        a.pushBack(i);
    }
    assert(a[0] == 0);
    assert(a[1] == 1);
    assert(a[2] == 2);
    assert(a[3] == 3);
    assert(a[4] == 4);
    assert(a[5] == 5);
}

void eraseTest() {
    Vector<int> a;
    for (int i = 0; i < 10; i++) {
        a.pushBack(i);
        a.erase(a.begin());
        assert(a.empty());
    }

    for (int i = 0; i < 10; i++) {
        a.pushBack(i);
    }

    a.erase(a.end() - 1);
    assert(a[a.size() - 1] == 8);

    a.erase(a.begin());
    assert(a[0] == 1);

    a.erase(a.begin() + 3);
    assert(a[3] == 5);
}

void foo(Vector<int> x) {
    x.pushBack(-20);
    x.pushBack(-30);
    x.pushBack(-40);

    for(auto i: x) {
        std::cout << i << std::endl;
    }
}

void copyConstructorTest() {
    Vector<int> a;
    a.pushBack(1);
    a.pushBack(2);
    a.pushBack(3);
    foo(a);
    std::cout << "============" << std::endl;
    for(auto i: a) {
        std::cout << i << std::endl;
    }
}

void pushBackTimeTest() {
    auto start = high_resolution_clock::now(); 
    Vector<int> a;
    for (int i = 0; i < 100000; i++) {
        a.pushBack(i);
    }
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start); 
    std::cout << "[TIME] Time taken by pushBack (100000 iterations used): " << duration.count() << " microseconds" << std::endl; 
}

void insertTimeTest() {
    auto start = high_resolution_clock::now(); 
    Vector<int> a;
    for (int i = 0; i < 100000; i++) {
        a.insert(a.end(), i);
    }
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start); 
    std::cout << "[TIME] Time taken by insert (100000 iterations used): " << duration.count() << " microseconds" << std::endl; 
}
