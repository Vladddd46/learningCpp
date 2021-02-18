#include <iostream>

using namespace std;

template <typename T>
T max_templ(T a, T b) {
    if (a > b) {
        return a;
    }
    else {
        return b;
    }
}

int main() {
    auto x_string = max_templ("aaaaa","xxxxxx");
    auto x_int    = max_templ(1,2);
    cout << x_string << endl;
    cout << x_int << endl;
}