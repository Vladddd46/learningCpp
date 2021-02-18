#include <iostream>

using namespace std;


template <typename T>
class MyClass {
    public :
        MyClass(T value) {
            this->value = value;
        }

        void DataTypeSize() {
            cout << sizeof(value) << endl;
        }

    private:
        T value;
};


int main() {
    MyClass<int> a(1);
    MyClass<string> b("string");
    MyClass<char> c('c');
    a.DataTypeSize();
    b.DataTypeSize();
    c.DataTypeSize();
}