#include <iostream>

using namespace std;

class Point {
    private:
        int x;
        int y;
    public:
        Point(int x, int y) {
            this->x = x;
            this->y = y;
        }

        int get_x() {
            return x;
        }
        int get_y() {
            return y;
        }

        Point operator +(const Point &other) {
            Point tmp = Point(other.x + this->x, other.y + this->y);
            return tmp;
        }
};

int main() {
    Point p(0,0);
    Point p1(2,2);
    Point p2 = p + p1;
    cout << p2.get_y() << endl;
}