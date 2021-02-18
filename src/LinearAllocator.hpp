#include <stdio.h>

using namespace std;

template <class T>
class LinearAllocator {
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

    LinearAllocator(std::size_t count = 5) : offset(nullptr), startAddress(nullptr) {
        cout << "[D] constructor method called" << endl;
        startAddress = (pointer)(operator new(count * sizeof(T)));
        offset       = startAddress;
        endAddress   = startAddress + count;
        print();
    }

    ~LinearAllocator() {
        cout << "[D] destructor method called" << endl;
        clear();
        print();
    }

    template <class U>
    LinearAllocator(const LinearAllocator<U>&) noexcept {}

    void memRealloc() {
        cout << "[D] Reallocate method called" << endl;
        int num = (endAddress - startAddress) * 2;
        delete[] ;    
        startAddress = (pointer)(operator new(num * sizeof(T)));
        offset       = startAddress;
        endAddress   = startAddress + num;
    }

    pointer allocate(value_type count) {
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
bool operator== (const LinearAllocator<T1>&, const LinearAllocator<T2>&) throw() {
    return true;
}

template <class T1, class T2>
bool operator!= (const LinearAllocator<T1>&, const LinearAllocator<T2>&) throw() {
    return false;
}