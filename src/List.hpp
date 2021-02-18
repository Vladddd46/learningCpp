#pragma once
// #include "header.h"

template <typename T> class List {
    private:
        typedef struct Node_s {
            T data;
            struct Node_s *next;
            struct Node_s *prev;
        } Node_t;

        Node_t *createNode(T data) {
            Node_t *node = new Node_t;
            node->data   = data;
            node->next   = nullptr;
            node->prev   = nullptr;
            return node;
        }
        Node_t *_listStart = nullptr;
        Node_t *_listEnd   = nullptr;

    public:
        List() {}

        List(List &&other) noexcept 
        : _listStart {other._listStart}, _listEnd {other._listEnd} {
            other._listStart = nullptr;
            other._listEnd   = nullptr;
        }

        List(const List &other) {
            Node_t *tmp = other._listStart;
            while(tmp) {
                pushBack(other.data);
                tmp = tmp->next;
            }
            Node_t *tmp2 = _listStart;
            while(tmp2 && tmp->next != nullptr) {
                tmp2 = tmp2->next;
            }
            _listEnd = tmp2;
        }

        class Iterator {
            Node_t *cur;
            public:
                Iterator(Node_t *first) {
                    cur = first;
                }

                Node_t *returnPointerToNode() {
                    return cur;
                }

                Iterator operator++() {
                    if (cur == nullptr) {
                        throw std::out_of_range("node is null");
                    }
                    return Iterator(cur->next);
                }

                Iterator operator--() {
                    if (cur == nullptr) {
                        throw std::out_of_range("node is null");
                    }    
                    return Iterator(cur->prev);
                }

                Iterator operator++(int) {
                    if (cur == nullptr) {
                        throw std::out_of_range("node is null");
                    }    
                    return Iterator(cur->next);
                }

                Iterator operator--(int) {
                    if (cur == nullptr) {
                        throw std::out_of_range("node is null");
                    }    
                    return Iterator(cur->prev);
                }

                Iterator operator+(int n) {
                    int i = 0;
                    while(i < n) {
                        if (cur == nullptr || cur->next == nullptr) {
                            throw std::out_of_range("iterator is out of range");
                        }
                        cur = cur->next;
                        i++;
                    }
                    return Iterator(cur);
                }
                
                Iterator operator-(int n) {
                    int i = 0;
                    while(i < n) {
                        if (cur == nullptr || cur->prev == nullptr) {
                            throw std::out_of_range("iterator is out of range");
                        }
                        cur = cur->prev;
                        i++;
                    }
                    return Iterator(cur);
                }

                bool operator!=(const Iterator& it) {return cur != it.cur;}  
                bool operator==(const Iterator& it) {return cur == it.cur;}  
                bool operator>(const Iterator& it)  {return cur > it.cur;}
                bool operator<(const Iterator& it)  {return cur < it.cur;}
                bool operator>=(const Iterator& it) {return cur >= it.cur;}
                bool operator<=(const Iterator& it) {return cur <= it.cur;}

                T& operator*() {
                    if (cur == nullptr) {
                        throw std::out_of_range("* operator error");
                    }
                    return cur->data;
                }
                
        };
        Iterator begin() {return Iterator(_listStart);}
        Iterator end()   {return Iterator(_listEnd);}
    
        // T begin(List &obj) {return _listStart;};
        // T end(List &obj) {return _listEnd;};

        T& front() {
            if (_listStart == nullptr) {
                throw std::out_of_range("list is empty");
            }
            return _listStart->data;
        }

        T& back() {
            if (_listEnd == nullptr) {
                throw std::out_of_range("list is empty");
            }
            return  _listEnd->data;
        }

        void pushBack(T data) {
            Node_t *node = createNode(data);
            if (_listStart == nullptr) {
                _listStart = node;
                _listEnd   = node;
            }
            else {
                node->prev     = _listEnd;
                _listEnd->next = node;
                _listEnd       = _listEnd->next;
            }
        }

        void pushFront(T data) {
            Node_t *node = createNode(data);
            if (_listStart == nullptr) {
                _listStart = node;
                _listEnd   = node;
            }
            else {
                node->next       = _listStart;
                _listStart->prev = node;
                _listStart       = node;
            }
        }

        void insert(Iterator position, T data) {
            Node_t *ptr = position.returnPointerToNode();
            if (ptr != nullptr && ptr->prev == nullptr) {
                pushFront(data);
            }
            else if (ptr != nullptr) {
                Node_t *newNode = createNode(data);
                ptr = ptr->prev;
                Node_t *nextNode = ptr->next;
                newNode->next  = nextNode;
                newNode->prev  = ptr;
                nextNode->prev = newNode;
                ptr->next      = newNode;
            }

        }

        void popFront() {
            if (_listStart == _listEnd) {
                free(_listStart);
                _listStart = nullptr;
                _listEnd   = nullptr;
            }
            if (_listStart != nullptr) {
                Node_t *tmp = _listStart;
                _listStart       = _listStart->next;
                _listStart->prev = nullptr;
                free(tmp);
            }
        }

        void popBack() {
            if (_listStart != nullptr) {
                Node_t *tmp = _listEnd;
                _listEnd    = _listEnd->prev;
                _listEnd->next = nullptr;
                free(tmp);
            }
            else if (_listStart == _listEnd) {
                free(_listStart);
                _listStart = nullptr;
                _listEnd   = nullptr;
            }
        }

        int size() const {
            Node_t *tmp = _listStart;
            int res = 0;
            while(tmp != nullptr) {
                res++;
                tmp = tmp->next;
            }
            return res;
        }

        void printList() const {
            Node_t *tmp = _listStart;
            while(tmp != nullptr) {
                std::cout << tmp->data << std::endl;
                tmp = tmp->next;
            }
        }

        void printListReverse() const {
            Node_t *tmp = _listEnd;
            while(tmp != nullptr) {
                std::cout << tmp->data << std::endl;
                tmp = tmp->prev;
            }
        }
};
