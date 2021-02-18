// #pragma once
#include "header.hpp"

using namespace std;
using namespace std::chrono;

// void BinaryTreeTimeTest() {
//     BinaryTree<int> bt;
//     bt.add(0);
//     bt.add(1);
//     bt.add(2);
//     bt.add(3);
//     bt.add(4);
//     bt.add(-2);
//     bt.add(-3);
//     bt.add(-4);
//     bt.add(-5);
//     bt.add(5);
//     bt.add(6);
//     bt.add(7);
//     auto start1 = high_resolution_clock::now(); 
//     bt.printBfsIterative();
//     auto stop1  = high_resolution_clock::now(); 
//     auto duration1 = duration_cast<microseconds>(stop1 - start1); 
//     auto start2 = high_resolution_clock::now(); 
//     bt.printBfsRecusrive();
//     auto stop2  = high_resolution_clock::now(); 
//     auto duration2 = duration_cast<microseconds>(stop2 - start2); 
//     auto start3 = high_resolution_clock::now(); 
//     bt.printDfsIterative();
//     auto stop3  = high_resolution_clock::now(); 
//     auto duration3 = duration_cast<microseconds>(stop3 - start3); 
//     auto start4 = high_resolution_clock::now(); 
//     bt.printDfsRecursive();
//     auto stop4  = high_resolution_clock::now(); 
//     auto duration4 = duration_cast<microseconds>(stop4 - start4);
//     std::cout << "[TIME] Time taken by Iterative bfs: " << duration1.count() << " microseconds" << std::endl; 
//     std::cout << "[TIME] Time taken by Recursive bfs: " << duration2.count() << " microseconds" << std::endl; 
//     std::cout << "[TIME] Time taken by Iterative dfs: " << duration3.count() << " microseconds" << std::endl; 
//     std::cout << "[TIME] Time taken by Recursive dfs: " << duration4.count() << " microseconds" << std::endl; 
// }


class A {
public:
	weakPtr<A> a;

	A() {
		cout << "Constructor called: " << this << endl;
	}

	~A() {
		cout << "Destructor called: " << this << endl;
	}

	void makeFriend(sharedPtr<A> f) {
		a  = f;
	}
};

int main() {
    // @brief: Vector tests
    // pushBackTest();
    // eraseTest();
    // copyConstructorTest();
    // pushBackTimeTest();
    // insertTimeTest();

    // @brief: List tests
    // pushBackListTest();
    // pushFrontListTest();
    // popFrontListTest();
    // popBackListTest();
    // insertListTest();

    // @brief binary tree time test.
    // BinaryTreeTimeTest();

    // // @brief Shared pointer test.
    // sharedPtr<A> ptr1;
    // {
    //     sharedPtr<A> ptr2(new A());
    //     ptr1 = ptr2;
    //     std::cout << "destructor will not be called because obj has 2 shared pointers: " << ptr2.useCount() << std::endl;
    // }
    //  std::cout << "destructor will be called after this expression: " << ptr1.useCount() << std::endl;

    // // @brief weakPtr test.
    // sharedPtr<A> a1(new A());
	// sharedPtr<A> a2(new A());
	// a1->makeFriend(a2);
	// a2->makeFriend(a1);

    // // @brief lock() test.
    // sharedPtr<int> foo0(new int(123));
    // cout << foo0.useCount() << endl;
    // weakPtr<int> w(foo0);
    // cout << foo0.useCount() << endl;
    // sharedPtr<int> foo1 = w.lock();
    // cout << foo0.useCount() << endl;

    // sharedPtr<int> foo0(new int(123));
    // cout << foo0.useCount() << endl;
    // sharedPtr<int> foo1(foo0);
    // cout << foo0.useCount() << endl;
    // sharedPtr<int> foo2(foo0);
    // cout << foo0.useCount() << endl;

    // // @brief makeShared
    // sharedPtr<int> ptr = makeShared<int>(123);
    // cout << ptr.useCount() << endl;
    return 0;
}