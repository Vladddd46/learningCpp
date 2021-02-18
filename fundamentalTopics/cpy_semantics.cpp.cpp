#include <iostream>

using namespace std;

class A {
private:
	int *x;
	int *y;
public:
	A(int a, int b) {
		cout << "consturctor: " << this << endl; 
		x = new int(a);
		y = new int(b);
	}

	A(const A &other) {
		cout << "copy constructor: " << this << endl;
		x = new int(*other.x);
		y = new int(*other.y);
	}

	void print() {
		cout << *x << endl;
		cout << *y << endl;
	}

	~A() {
		cout << "destructor: " << this << endl;
		delete x;
		delete y;
	}
};

void foo(A o) {
}

int main() {
	A obj(10, 11);
	foo(obj);
	obj.print();
	return 0;
}