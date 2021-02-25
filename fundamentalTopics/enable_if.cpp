#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <type_traits>
using namespace std;

template <typename T>
void foo1(T t, enable_if_t<is_floating_point<T>::value>* = nullptr) {
	cout << "T is is_floating_point " << t << endl;
}

template <typename T>
void foo1(T t, enable_if_t<!is_floating_point<T>::value>* = nullptr) {
	cout << "T is not is_floating_point " << t << endl;
}

int main() {
	float f = 1.1;
	foo1(f);
	foo1(123);
}