#include <iostream>
#include <memory>
 

class Item {
    public:
        Item()  {std::cout << "Item acquired\n";}
        ~Item() {std::cout << "Item destroyed\n";}
};
 
int main() {
	std::shared_ptr<Item> ptr1 = std::make_shared<Item>();
    {
		std::shared_ptr<Item> ptr2(ptr1);
		std::cout << "Killing one shared pointer\n";
	} 
	std::cout << "Killing another shared pointer\n";
	return 0;
} 