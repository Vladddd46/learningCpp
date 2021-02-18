#include <iostream>
#include <string>

using namespace std;

struct Student {
	string Name;
	int x;

	void print() {
		cout << Name << " " << x << endl;
	}

	~Student() {
		cout << "Destructor" << endl;
	}
};

int main() {
	// {
	// 	Student *x = new Student{"Alex", 12};
	// 	x->print();
	// 	delete x;
	// }
	// {
	// 	void *buf = operator new(sizeof(Student) * 2);
	// 	Student *s = new(buf + sizeof(Student))Student{"Alex", 11};
	// 	s->print();
	// 	s->~Student();
	// 	operator delete(buf);
	// }
	// {
	// 	Student s;
	// 	s.~Student();
	// 	new (&s) Student{"x", 10};
	// 	s.print();
	// }
	{
		uint8_t *ptr = new uint8_t[sizeof(int) * 10];
		for (int i = 0; i < 10; i++) {
			if (i != 8)
				new(ptr + (sizeof(int) * i))int(70);
			else {
				new(ptr + (sizeof(int) * i))int(90);
			}
		}

		*(ptr + (1 * sizeof(int))) = *(ptr + (8 * sizeof(int)));
		for (int i = 0; i < 10; i++) {
			cout << *(int *)(ptr + (sizeof(int) * i)) << endl;
		}
	}
}