#include <iostream>

using namespace std;

class A {
private:
	int *a;
public:
	A(int a) {
		cout << "constructor: " << this << endl;
		this->a = new int(a);
	}

	A(const A &other) {
		cout << "copy constructor: " << this << endl;
		this->a = new int(*other.a);
	}

	void print() {
		cout << *a << endl;
	}

	A(A &&other) {
		cout << "move semantics: " << this << endl;
		this->a = new int(*other.a);
		delete other.a;
		other.a = nullptr;
	}

	~A() {
		cout << "destructor: " << this << endl;
		delete a;
	}
};



int main() {
	A obj(123);
	obj.print();
	A obj2 = move(obj);
	// obj.print(); // error
	return 0;
}