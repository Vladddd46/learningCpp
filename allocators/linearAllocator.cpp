#include <limits>
#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

static int memSize = 100;

// free mem range and merge them
template <class T>
class linearAllocator {
public:
    typedef T              value_type;
    typedef T*             pointer;
    typedef const T*       const_pointer;
    typedef T&             reference;
    typedef const T&       const_reference;
    typedef std::size_t    size_type;
    typedef std::ptrdiff_t difference_type;

    void print() {
        printf("\tstartAddress=%d endAddress=%d. All allocated memory=%dbytes.\n", startAddress, endAddress, endAddress-startAddress);
    }


    /* Allocates block of memory (100 bytes by default).
     * Initialize pointers,
     * startAddress - begin of allocated memory.
     * endAddress   - end of allocated memory.
     * 
     */
    linearAllocator(std::size_t count = memSize) {
        startAddress = (uint8_t *)(operator new(count * sizeof(T)));
        endAddress  = startAddress + (count * sizeof(T));
        pushBack(&allocedBlocksList, endAddress, nullptr);
        cout << "[D] constructor method called:" << endl;
        cout << "\t" << "Block of memmory was allocated: " << count * sizeof(T) << endl;
        printList();
        print();
        cout << endl << endl;
    }

    ~linearAllocator() {
        clear();
    }

    template <class U>
    linearAllocator(const linearAllocator<U>&) noexcept {}

    pointer allocate(size_type count) {
        cout << "[D] Allocate method called" << endl;
        size_type numBytesToAlloc = count * sizeof(T);
        cout << "\tBytes to allocate=" << count * sizeof(T) << " =>" << count << " object(s) of " << sizeof(T) << " size" << endl;
        uint8_t *memBlock = getMemoryBlock(numBytesToAlloc);
        if (memBlock == nullptr) {
            clear();
            pushBack(&allocedBlocksList, endAddress, nullptr);
            memBlock = getMemoryBlock(numBytesToAlloc);
        }
        printList();
        return (pointer)memBlock;
    }

    void deallocate(pointer p, size_type count) noexcept {
        cout << "[D] Deallocate method called" << endl;
        printf("\tRemoving mem block with start addr: %d\n", p);
        removeNodeByStartAddr(&allocedBlocksList, (uint8_t *)p);
        printList();
    }

    void destroy(T *p) {
        p->~T();
    }

    void clear() {
        cout << "[D] clear method called" << endl;
        printf("\tFreeing all memory from startAddress: %d\n", startAddress);
        if (startAddress != nullptr){
            delete[] startAddress;
            startAddress = nullptr;
        }
        endAddress = nullptr;
        freeList(&allocedBlocksList);
    }

    void listTest() {
        list_t *testList = nullptr;
        uint8_t a  = 0;
        uint8_t a1 = 1;
        uint8_t a2 = 2;
        uint8_t a3 = 3;
        uint8_t a4 = 4;
        uint8_t a5 = 5;
        insertInOrder(&testList, &a,  &a);
        insertInOrder(&testList, &a1, &a);
        insertInOrder(&testList, &a3, &a);
        insertInOrder(&testList, &a4, &a);
        insertInOrder(&testList, &a5, &a);
        insertInOrder(&testList, &a2, &a);
        while(testList) {
            printf("startAddr = %d\n", testList->startAddressOfBlock);
            testList = testList->next;
        }
    }

private:
    typedef struct list_s {
        uint8_t *startAddressOfBlock;
        uint8_t *endAddressOfBlock;
        struct list_s *next; 
    } list_t;

    uint8_t *startAddress      = nullptr;
    uint8_t *endAddress        = nullptr;
    list_t  *allocedBlocksList = nullptr;

    list_t *createNode(uint8_t *startAddr, uint8_t *endAddr) {
        list_t *node = new list_t;
        node->startAddressOfBlock = startAddr;
        node->endAddressOfBlock   = endAddr;
        node->next = nullptr;
        return node;
    }

    uint8_t *getMemoryBlock(size_type memSize) {
        cout << "\t[D] getMemoryBlock function called" << endl;
        uint8_t *prevAddr = startAddress;
        list_t *tmp = allocedBlocksList;

        while(tmp != nullptr) {
            if (tmp->startAddressOfBlock - prevAddr > memSize) {
                printf("\t\tMem with startAddr=%d returned. endAddr=%d. Block of %d bytes alloced\n", prevAddr, prevAddr + memSize, memSize);
                insertInOrder(&allocedBlocksList, prevAddr, prevAddr + memSize);
                return prevAddr;
            }
            prevAddr = tmp->endAddressOfBlock;
            tmp = tmp->next;
        }
        printf("\tMem can not be allocated. NUll is returned\n\n");
        return nullptr; // never happens
    }

    // @brief Removes node with startAddrToDelete from list.
    void removeNodeByStartAddr(list_t **list, uint8_t *startAddrToDelete) {
        if (*list == nullptr) {
            return;
        }
        list_t *tmp = *list;
        list_t *nodeToFree = nullptr;
        if (tmp->startAddressOfBlock == startAddrToDelete) {
            nodeToFree = *list;
            *list = tmp->next;
            delete nodeToFree;
        }
        while(tmp) {
            if (tmp->next != nullptr && tmp->next->startAddressOfBlock == startAddrToDelete) {
                nodeToFree = tmp->next;
                printf("\t[D] node with startAddr %d was deleted\n", startAddrToDelete);
                tmp->next =tmp->next->next;
                delete nodeToFree;
                break;
            }
            tmp = tmp->next;
        }
    }

    // @brief Inserts node in sorted order. (sort by list->startAddressOfBlock)
    void insertInOrder(list_t **list, uint8_t *startAddr, uint8_t *endAddr) {
        list_t *node = createNode(startAddr, endAddr);

        list_t *tmp = *list;
        if (*list == nullptr) {
            *list = node;
        }
        else if (tmp->startAddressOfBlock > node->startAddressOfBlock) {
            node->next = *list;
            *list = node;
        }
        else  {
            while(tmp) {
                if (tmp && tmp->next->startAddressOfBlock > node->startAddressOfBlock) {
                    node->next = tmp->next;
                    tmp->next = node;
                    break;
                }
                else if (tmp && tmp->next == nullptr) {
                    tmp->next = node;
                    break;
                }
                tmp = tmp->next;
            }
        }
    }

    void pushBack(list_t **list, uint8_t *startAddr, uint8_t *endAddr) {
        list_t *node = createNode(startAddr, endAddr);
        if (*list == nullptr) {
            *list = node;
        }
        else {
            list_t *tmp = *list;
            while(tmp->next != nullptr) {
                tmp = tmp->next;
            }
            tmp->next = node;
        }
    }

    void freeList(list_t **list) {
        list_t *nodeToDel = nullptr;
        list_t *tmp = *list;
        while(tmp) {
            nodeToDel = tmp;
            tmp = tmp->next;
            if (nodeToDel != nullptr) {
                delete nodeToDel;
            }
        }
        allocedBlocksList = nullptr;
    }

    void printList() {
        cout << "\t[D] List printing" << endl;
        int index = 0;
        list_t *tmp = allocedBlocksList;
        while(tmp) {
            printf("\t\tNode_index=%d startAddr=%d endAddress=%d\n", index, tmp->startAddressOfBlock, tmp->endAddressOfBlock);
            index++;
            tmp = tmp->next;
        }
    }
};

// return that all specializations of this allocator are interchangeable
template <class T1, class T2>
bool operator== (const linearAllocator<T1>&, const linearAllocator<T2>&) throw() {
    return true;
}

template <class T1, class T2>
bool operator!= (const linearAllocator<T1>&, const linearAllocator<T2>&) throw() {
    return false;
}


int main() {
    // create a vector, using linearAllocator<> as allocator
    vector<int, linearAllocator<int>> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);
    v.push_back(7);
    v.push_back(8);
    v.push_back(9);

    for (auto i: v) {
        cout << i << endl;
    }
}
