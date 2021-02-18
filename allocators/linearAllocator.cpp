#include <limits>
#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

template <class T>
class MyAlloc {
public:
    typedef T              value_type;
    typedef T*             pointer;
    typedef const T*       const_pointer;
    typedef T&             reference;
    typedef const T&       const_reference;
    typedef std::size_t    size_type;
    typedef std::ptrdiff_t difference_type;

    void print() {
        cout << "startAddress=" << startAddress << " offset=" << offset << " endAddress=" << endAddress << endl << endl;
    }

    MyAlloc(std::size_t count = 5) : offset(nullptr), startAddress(nullptr) {
        cout << "[D] constructor method called" << endl;
        startAddress = (pointer)(operator new(count * sizeof(T)));
        offset       = startAddress;
        endAddress   = startAddress + count;
        print();
    }

    ~MyAlloc() {
        cout << "[D] destructor method called" << endl;
        clear();
        print();
    }

    template <class U>
    MyAlloc(const MyAlloc<U>&) noexcept {}

    void memRealloc() {
        cout << "[D] Reallocate method called" << endl;
        int num = (endAddress - startAddress) * 2;
        // delete[] startAddress;    
        startAddress = (pointer)(operator new(num * sizeof(T)));
        offset       = startAddress;
        endAddress   = startAddress + num;
    }

    pointer allocate(size_type count) {
        cout << "[D] allocate method called" << endl;
       
        if (offset != nullptr && offset + count > endAddress) {
            memRealloc(); // !!!!!!!!!!!!!
        }
        pointer res = offset;
        offset  +=  count;
        print();
        return res;
    }

    void deallocate(pointer p, size_type count) noexcept {
        cout << "[D] deallocate method called" << endl;

        if (offset != nullptr && offset > endAddress) {
            clear();
        }
        print();
    }

    void destroy(T *p) {
        p->~T();
    }

    void clear() {
        cout << "[D] clear method called" << endl;
        if (startAddress != nullptr){
            delete[] startAddress;
            startAddress = nullptr;
        }
        offset = nullptr;
        print();
    }
private:
    pointer    startAddress = nullptr;
    pointer    endAddress   = nullptr;
    pointer    offset       = nullptr;
};

// return that all specializations of this allocator are interchangeable
template <class T1, class T2>
bool operator== (const MyAlloc<T1>&, const MyAlloc<T2>&) throw() {
    return true;
}

template <class T1, class T2>
bool operator!= (const MyAlloc<T1>&, const MyAlloc<T2>&) throw() {
    return false;
}


int main() {
    // create a vector, using MyAlloc<> as allocator
    vector<int, MyAlloc<int>> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    for (auto i: v) {
        cout << i << endl;
    }
}
