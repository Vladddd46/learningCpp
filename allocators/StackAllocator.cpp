#include <limits>
#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

template <class T>
class StackAllocator {
public:
    typedef T              value_type;
    typedef T*             pointer;
    typedef const T*       const_pointer;
    typedef T&             reference;
    typedef const T&       const_reference;
    typedef std::size_t    size_type;
    typedef std::ptrdiff_t difference_type;

    void print() {
        cout << "startAddress=" << startAddress 
        << " offset=" << offset << " endAddress=" 
        << endAddress << endl << endl;
    }

    StackAllocator(std::size_t count = 100) {
        cout << "[D] constructor method called" << endl;
        startAddress = (pointer)(operator new(count * sizeof(T)));
        offset       = startAddress;
        endAddress   = startAddress + count;
        print();
    }

    ~StackAllocator() {
        cout << "[D] destructor method called" << endl;
        clear();
        print();
    }

    template <class U>
    StackAllocator(const StackAllocator<U>&) noexcept {}

    void memRealloc() {
        cout << "[D] Reallocate method called" << endl;
        int num = (endAddress - startAddress) * 2;
        delete[] startAddress;  // !!!!! attention
        startAddress = (pointer)(operator new(num * sizeof(T)));
        offset       = startAddress;
        endAddress   = startAddress + num;
    }

    pointer allocate(size_type count) {
        cout << "[D] allocate method called" << endl;
        new(offset)header_s(prevHdr, count);
        if (offset + count > endAddress) {
            // memRealloc(); // !!!!! attention
        }
        prevHdr = offset;
        pointer ret = offset + (sizeof(header_s)/sizeof(T));
        offset = ret + count;
        print();
        return ret;
    }

    void deallocate(pointer p, size_type count) noexcept {
        cout << "[D] deallocate method called" << endl;
        offset = prevHdr;
        if (prevHdr != nullptr) {
            header_s *tmp = (header_s *)prevHdr; 
            prevHdr = tmp->prev;
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
    pointer startAddress = nullptr;
    pointer endAddress   = nullptr;
    pointer offset       = nullptr;
    pointer prevHdr      = nullptr;

    struct header_s {
        pointer   prev;
        size_type allocBlockSize;

        header_s(pointer prev, size_type allocBlockSize) {
            this->prev = prev;
            this->allocBlockSize = allocBlockSize;
        }
    };
};

// return that all specializations of this allocator are interchangeable
template <class T1, class T2>
bool operator== (const StackAllocator<T1>&, const StackAllocator<T2>&) throw() {
    return true;
}

template <class T1, class T2>
bool operator!= (const StackAllocator<T1>&, const StackAllocator<T2>&) throw() {
    return false;
}


int main() {
    // create a vector, using StackAllocator<> as allocator
    vector<int, StackAllocator<int>> v;
    for (int i = 0; i < 151; i++) {
        v.push_back(i);
    }

    for (auto i: v) {
        cout << i << endl;
    }
}
