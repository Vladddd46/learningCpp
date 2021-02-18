#include <iostream>

using namespace std;

template <typename T>
void f(T x) {
	cout << x << " ";
}

template <typename T, typename ...Ts>
void f(T x, Ts ...y) {
	f(x);
	f(y...);
}

int main() {
	f(1,2,3,4,5,6,7,8,9,10, 11, 12, 13, 14, 15, 16);
	cout << endl;
	f("a", "b", "c", 1.0, 199, 'c');
}