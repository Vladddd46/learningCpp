#include <iostream>

using namespace std;


class A {
	private:
		int a = 1222535322;
	public:
		friend class B;
};

class B {
	public:
		void print(A obj) {
			cout << obj.a << endl;
		}
};



int main() {
	A obj = A();
	B obj2 = B();

	obj2.print(obj);
}
