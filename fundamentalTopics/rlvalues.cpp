#include <iostream>

using namespace std;

int global = 10;

int &setValue() {
	return global;
}

int main() {
	setValue() = 3;
	cout << global << endl;
}