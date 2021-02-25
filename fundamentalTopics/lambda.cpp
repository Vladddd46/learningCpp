#include <iostream>
#include <vector>
#include <string>
#include <functional>
using namespace std;

void doWork(vector<int> &a, function<bool(int)> f) {
	for(int i: a) {
		f(i);
	}
}

int main() {
	vector<int> a = {1,2,3,4,5,6,7,8,9,10};
	doWork(a, [](int elem){
		if (elem % 2 ? false:true) {
			cout << elem << " is even" << endl;
			return true;
		}
		cout << elem << " is odd" << endl;
		return false;
	});
	return 0;
}