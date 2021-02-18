#pragma once
// #include "header.h"

// vector implementation with placement new
template <typename T> class Vector {
    private:
        std::shared_ptr<uint8_t> arrStart;
        uint8_t *arrEnd;
        uint8_t *arrBack;
    public:
        int capacity() const {
            return (arrEnd - arrStart.get())/sizeof(T);
        }

        int size() const {
            return (arrBack - arrStart.get())/sizeof(T);
        }

        Vector() {
            uint8_t *tmp = new uint8_t[sizeof(T) * 2];
            arrStart.reset(tmp, [](uint8_t *memPtr) {delete[] memPtr;});
            arrEnd  = tmp + sizeof(T);
            arrBack = tmp;
        }

        Vector(int n) {
            uint8_t *tmp = new uint8_t[sizeof(T) * n];
            arrStart.reset(tmp, [](uint8_t *memPtr) {delete[] memPtr;});
            arrEnd  = tmp + (sizeof(T) * n);
            arrBack = tmp;
        }

        Vector(const Vector &other)
        {            
            uint8_t *tmp = new uint8_t[other.capacity() * sizeof(T)];
            arrStart.reset(tmp, [](uint8_t *memPtr) {delete[] memPtr;});
            arrEnd  = arrStart.get() + (other.capacity() * sizeof(T));
            arrBack = arrStart.get() + (other.size() * sizeof(T));

            std::cout << "[DEBUG] coping constructor" << std::endl;

            int capacity_val = other.capacity();
            for (int i = 0 ;i < capacity_val; i++) {
                new(arrStart.get() + (i * sizeof(T)))T(*(other.arrStart.get() + (i * sizeof(T))));
            }
        }

        Vector(Vector &&other) noexcept {
            arrStart.reset(other.arrStart.get(), [](uint8_t *memPtr) {delete[] memPtr;});
            arrEnd  = other.arrEnd;
            arrBack = other.arrBack;

            other.arrStart.reset();
            other.arrEnd   = nullptr;
            other.arrBack  = nullptr;
        }

        void pushBack(T val) {
            if (size() == capacity()) {
                vector_reallocate();
            }
            new(arrBack)T(val);
            arrBack = arrBack + sizeof(T);
        }

        void vector_reallocate() {
            int capacity_val = capacity();
            int size_val     = size();
            uint8_t *tmp = new uint8_t[(capacity_val * sizeof(T)) * 2];

            for (int i = 0; i < capacity_val; i++) {
                new(tmp + (i * sizeof(T)))T(*(arrStart.get() + (i * sizeof(T))));
            }
            arrStart.reset(tmp, [](uint8_t *memPtr) {delete[] memPtr;});
            arrEnd   = tmp + ((capacity_val * sizeof(T)) * 2);
            arrBack  = tmp + (size_val * sizeof(T));
        }

        bool empty() {
            if (size() == 0)
                return true;
            return false;
        }

        const T &operator[](int index) const {
            // if (index < 0 || (index * sizeof(T)) >= size()) {
            //     throw std::out_of_range("index is out of range");
            // }
            // static_cast
            return static_cast<int>*(T *)(arrStart.get() + (index * sizeof(T)));
        }

        T &operator[](int index) {
            // if (index < 0 || (index * sizeof(T)) >= size())
            //     throw std::out_of_range("index is out of range");
            return *(T *)(arrStart.get() + (index * sizeof(T)));
        }

        class Iterator {
            T *cur;
            public:
                Iterator(T *first) {
                    cur = first;
                }
                Iterator operator+(int n) {return cur + n;}
                Iterator operator-(int n) {return cur - n;}     

                T& operator++(int) {return *cur++;}  
                T& operator--(int) {return *cur--;}
                T& operator++() {return *++cur;}  
                T& operator--() {return *--cur;}  

                bool operator!=(const Iterator& it) {return cur != it.cur;}  
                bool operator==(const Iterator& it) {return cur == it.cur;}  
                bool operator>(const Iterator& it)  {return cur > it.cur;}
                bool operator<(const Iterator& it)  {return cur < it.cur;}
                bool operator>=(const Iterator& it) {return cur >= it.cur;}
                bool operator<=(const Iterator& it) {return cur <= it.cur;}

                T& operator*() {return *cur;}
        };

        Iterator begin() {return Iterator((T *)arrStart.get());}
        Iterator end() {return Iterator((T *)arrBack);}
        
        T begin(Vector &obj) {return (T)arrStart.get();};
        T end(Vector &obj) {return (T)arrBack;};

          void insert(Iterator position, T value) {
            if (position == end()) {
                pushBack(value);
                return;
            }
            if (position > end() || position < begin()) {
                std::cout << "Incorrect position" << std::endl;
                return;
            }
            if (arrBack == arrEnd) {
                vector_reallocate();
            }

            auto i = end();
            while(i > position) {
                auto tmp = i - 1;
                *i = *tmp;
                i--;
            }
            *i = value;
            arrBack = arrBack + sizeof(T);
        }

        void erase(Iterator position) {
            if (position >= end() || position < begin()) {
                throw std::out_of_range("Incorrect position");
            }
            while(position != end()) {
                *position = *(position + 1);
                position++;
            }
            arrBack = arrBack - (sizeof(T));
        }
};

// template <typename T> class Vector {
//     private:
//         std::shared_ptr<T> arrStart;
//         T *arrEnd;
//         T *arrBack;
//     public:
//         int capacity() const {
//             return arrEnd - arrStart.get();
//         }

//         int size() const {
//             return arrBack - arrStart.get();
//         }

//         Vector() {
//             arrStart.reset(new T[2]);
//             arrEnd  = arrStart.get() + 1;
//             arrBack = arrStart.get();
//         }

//         Vector(int n) {
//             arrStart.reset(new T[n]);
//             arrEnd  = arrStart.get() + n;
//             arrBack = arrStart.get();
//         }

//         Vector(const Vector &other)
//         {
//             arrStart.reset(new T[other.capacity()]);
//             arrEnd  = arrStart.get() + other.capacity();
//             arrBack = arrStart.get() + other.size();

//             std::cout << "[DEUBG] coping constructor" << std::endl;

//             int capacity_val1 = other.capacity();
//             for (int i = 0 ; i < capacity_val1; i++)
//                 arrStart.get()[i] = other.arrStart.get()[i];
//         }

//         Vector(Vector &&other) noexcept 
//         {
//             arrStart.reset(other.arrStart.get());
//             arrEnd  = other.arrEnd;
//             arrBack = other.arrBack;

//             other.arrStart.reset();
//             other.arrEnd   = nullptr;
//             other.arrBack  = nullptr;
//         }

//         void pushBack(T val) {
//             if (size() == capacity()) {
//                 vector_reallocate();
//             }
//             *arrBack = val;
//             arrBack++;
//         }

//         void vector_reallocate() {
//             int capacity_val = capacity();
//             int size_val     = size();
//             T *tmp = new T[capacity_val * 2];

//             for (int i = 0; i < capacity_val; i++) {
//                 tmp[i] = *(arrStart.get() + i);
//             }
//             // delete[] arrStart.get();
//             arrStart.reset(tmp);
//             arrEnd   = arrStart.get() + (capacity_val * 2);
//             arrBack  = arrStart.get() + size_val;
//         }

//         bool empty() {
//             if (size() == 0)
//                 return true;
//             return false;
//         }

//         const T &operator[](int index) const {
//             if (index < 0 || index >= size())
//                 throw std::out_of_range("index is out of range");
//             return *(arrStart.get() + index);
//         }

//         T &operator[](int index) {
//             if (index < 0 || index >= size())
//                 throw std::out_of_range("index is out of range");
//             return *(arrStart.get() + index);
//         }

//         class Iterator {
//             T *cur;
//             public:
//                 Iterator(T *first) {
//                     cur = first;
//                 }
//                 Iterator operator+(int n) {return cur + n;}
//                 Iterator operator-(int n) {return cur - n;}     

//                 T& operator++(int) {return *cur++;}  
//                 T& operator--(int) {return *cur--;}
//                 T& operator++() {return *++cur;}  
//                 T& operator--() {return *--cur;}  

//                 bool operator!=(const Iterator& it) {return cur != it.cur;}  
//                 bool operator==(const Iterator& it) {return cur == it.cur;}  
//                 bool operator>(const Iterator& it)  {return cur > it.cur;}
//                 bool operator<(const Iterator& it)  {return cur < it.cur;}
//                 bool operator>=(const Iterator& it) {return cur >= it.cur;}
//                 bool operator<=(const Iterator& it) {return cur <= it.cur;}

//                 T& operator*() {return *cur;}
//         };

//         Iterator begin() {return Iterator(arrStart.get());}
//         Iterator end() {return Iterator(arrBack);}
        
//         T begin(Vector &obj) {return arrStart.get();};
//         T end(Vector &obj) {return arrBack;};

//           void insert(Iterator position, T value) {
//             if (position == end()) {
//                 pushBack(value);
//                 return;
//             }

//             if (arrBack == arrEnd) {
//                 vector_reallocate();
//             }
//             if (position > end() || position < begin()) {
//                 throw std::out_of_range("Incorrect position");
//             }
//             auto i = end();
//             while(i > position) {
//                 auto tmp = i - 1;
//                 *i = *tmp;
//                 i--;
//             }
//             *i = value;
//             arrBack++;
//         }

//         void erase(Iterator position) {
//             if (position >= end() || position < begin()) {
//                 throw std::out_of_range("Incorrect position");
//             }
//             while(position != end()) {
//                 *position = *(position + 1);
//                 position++;
//             }
//             arrBack--;
//         }
// };

// old implementation without smart pointers.
// template <typename T> class Vector {
//     private:
//         T* _arrStart = nullptr;
//         T* _arrEnd   = nullptr;
//         T* _arrBack  = nullptr;
//     public:
//         int capacity() const {
//             return _arrEnd - _arrStart;
//         }

//         int size() const {
//             return _arrBack - _arrStart;
//         }

//         Vector() {
//             _arrStart = new T[1];
//             _arrEnd   = _arrStart + 1;
//             _arrBack  = _arrStart;
//         }

//         Vector(int n) {
//             _arrStart = new T[n];
//             _arrEnd   = _arrStart + n;
//             _arrBack  = _arrStart;
//         }

//         Vector(const Vector &other)
//         : _arrStart {new T[other.capacity()]}, _arrEnd {_arrStart + other.capacity()}, _arrBack {_arrStart + other.size()}
//         {
//             std::cout << "[DEUBG] coping constructor" << std::endl;
//             int capacity_val = other.capacity();
//             for (int i = 0 ; i < capacity_val; i++)
//                 _arrStart[i] = other._arrStart[i];
//         }

//         Vector(Vector &&other) noexcept 
//         : _arrStart {other._arrStart}, _arrEnd {other._arrEnd}, _arrBack {other._arrBack} 
//         {
//             other._arrStart = nullptr;
//             other._arrEnd   = nullptr;
//             other._arrBack  = nullptr;
//         }

//         ~Vector() {
//             std::cout << "[DEBUG] Destructor: " << this << " arr_address: " << _arrStart << std::endl;
//             delete[] _arrStart;
//         }

//         void pushBack(T val) {
//             if (size() == capacity()) {
//                 vector_reallocate();
//             }
//             *_arrBack = val;
//             _arrBack++;
//         }

//         void vector_reallocate() {
//             int capacity_val = capacity();
//             int size_val     = size();
//             T *tmp = new T[capacity_val * 2];

//             for (int i = 0; i < capacity_val; i++) {
//                 tmp[i] = *(_arrStart + i);
//             }
//             delete[] _arrStart;
//             _arrStart = tmp;
//             _arrEnd   = _arrStart + (capacity_val * 2);
//             _arrBack  = _arrStart + size_val;
//         }


//         bool empty() {
//             if (size() == 0)
//                 return true;
//             return false;
//         }

//         const T &operator[](int index) const {
//             if (index < 0 || index >= size())
//                 throw std::out_of_range("index is out of range");
//             return *(_arrStart + index);
//         }

//         T &operator[](int index) {
//             if (index < 0 || index >= size())
//                 throw std::out_of_range("index is out of range");
//             return *(_arrStart + index);
//         }

//         class Iterator {
//             T *cur;
//             public:
//                 Iterator(T *first) {
//                     cur = first;
//                 }
//                 Iterator operator+(int n) {return cur + n;}
//                 Iterator operator-(int n) {return cur - n;}     

//                 T& operator++(int) {return *cur++;}  
//                 T& operator--(int) {return *cur--;}
//                 T& operator++() {return *++cur;}  
//                 T& operator--() {return *--cur;}  

//                 bool operator!=(const Iterator& it) {return cur != it.cur;}  
//                 bool operator==(const Iterator& it) {return cur == it.cur;}  
//                 bool operator>(const Iterator& it)  {return cur > it.cur;}
//                 bool operator<(const Iterator& it)  {return cur < it.cur;}
//                 bool operator>=(const Iterator& it) {return cur >= it.cur;}
//                 bool operator<=(const Iterator& it) {return cur <= it.cur;}

//                 T& operator*() {return *cur;}
//         };
//         Iterator begin() {return Iterator(_arrStart);}
//         Iterator end() {return Iterator(_arrBack);}
        
//         T begin(Vector &obj) {return _arrStart;};
//         T end(Vector &obj) {return _arrBack;};

//         void insert(Iterator position, T value) {
//             if (position == end()) {
//                 pushBack(value);
//                 return;
//             }

//             bool deleteOldArrFlag = false;
//             T* pointerToArrayForDelete;

//             if (_arrBack == _arrEnd) {
//                 int capacity_val = capacity();
//                 int size_val     = size();
//                 T *tmp = new T[capacity_val * 2];

//                 for (int i = 0; i < capacity_val; i++) {
//                     tmp[i] = *(_arrStart + i);
//                     if (position == _arrStart + i) {
//                         position = tmp + i;
//                     }
//                 }
//                 deleteOldArrFlag = true;
//                 pointerToArrayForDelete = _arrStart;
//                 _arrStart = tmp;
//                 _arrEnd   = _arrStart + (capacity_val * 2);
//                 _arrBack  = _arrStart + size_val;
//             }
//             if (position > end() || position < begin()) {
//                 throw std::out_of_range("Incorrect position");
//             }
            
//             auto i = end();
//             while(i > position) {
//                 auto tmp = i - 1;
//                 *i = *tmp;
//                 i--;
//             }
//             *i = value;
//             _arrBack++;
            
//             if (deleteOldArrFlag) {
//                 delete[] pointerToArrayForDelete;
//             }
//         }

//         void erase(Iterator position) {
//             if (position >= end() || position < begin()) {
//                 throw std::out_of_range("Incorrect position");
//             }
//             while(position != end()) {
//                 *position = *(position + 1);
//                 position++;
//             }
//             _arrBack--;
//         }
// };