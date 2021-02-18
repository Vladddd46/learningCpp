#include <iostream>
#include <memory> // для std::unique_ptr

using namespace std;

class Item {
    public:
	    Item() { std::cout << "Item acquired\n"; }
	    ~Item() { std::cout << "Item destroyed\n"; }
};
 
int main() {
	std::unique_ptr<Item> item1 = make_unique<Item>(); // выделение Item
	std::unique_ptr<Item> item2; // присваивается значение nullptr
    
    std::cout << "item1 is " << (static_cast<bool>(item1) ? "not null\n" : "null\n");
    std::cout << "item2 is " << (static_cast<bool>(item2) ? "not null\n" : "null\n");
    
    std::cout << std::endl << std::endl;
	// item2 = item1; // не скомпилируется: семантика копирования отключена
	item2 = std::move(item1); // item2 теперь владеет item1, а для item1 присваивается значение null
    std::cout << "item1 is " << (static_cast<bool>(item1) ? "not null\n" : "null\n");
    std::cout << "item2 is " << (static_cast<bool>(item2) ? "not null\n" : "null\n");
	return 0;
}
