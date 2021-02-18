#include <queue> 

template <typename T> class BinaryTree {
    private:
        typedef struct Node_s {
            T data;
            struct Node_s *left;
            struct Node_s *right;
        } Node_t;

        Node_t *createNode(T data) {
            Node_t *node = new Node_t;
            node->data  = data;
            node->left  = nullptr;
            node->right = nullptr;
            return node;
        }

        Node_t *binaryTree = nullptr;

        void printInDepthRecursively(Node_t *root) {
            if (root != nullptr) {
                std::cout << root->data << std::endl;
                if (root->left != nullptr) {
                    printInDepthRecursively(root->left);
                }
                if (root->right != nullptr) {
                    printInDepthRecursively(root->right);
                }
            } 
        }

        void printInDepthIteratively(Node_t *root) {
            if (root == nullptr) {
                return;
            }
            Node_t *node = root;
            vector<Node_t *> stack;
            stack.push_back(node);

            while(stack.empty() == false) {
                node = stack.back();
                std::cout << node->data << std::endl;
                stack.pop_back();
                if (node->right != nullptr) {
                    stack.push_back(node->right);
                }
                if (node->left != nullptr) {
                    stack.push_back(node->left);
                }
            }
        }

        void printInWidthIteratively(Node_t *root) {
            queue<Node_t *> q;
            if (root != nullptr) {
                q.push(root);
            }
            while(q.empty() == false) {
                Node_t *node = q.front();
                q.pop();
                std::cout << node->data << std::endl;
                if (node->left != nullptr) {
                    q.push(node->left);
                }
                if (node->right != nullptr) {
                    q.push(node->right);
                }
            }
        }

        void printInWidthRecursively(queue<Node_t *> q) {
            if (q.empty() == false) {
                Node_t *node = q.front();
                q.pop();
                std::cout << node->data << std::endl;
                if (node->left != nullptr) {
                    q.push(node->left);
                }
                if (node->right != nullptr) {
                    q.push(node->right);
                }
                printInWidthRecursively(q);
            }
        }

        void __delete__(Node_t *root) {
            if (root != nullptr) {
                if (root->left != nullptr) {
                    __delete__(root->left);
                }
                if (root->right != nullptr) {
                    __delete__(root->right);
                }
                delete root;
            } 
        }

        void push(Node_t *root, T data) {
            if (root == nullptr) {
                binaryTree = createNode(data);
            }
            else if (data < root->data) {
                if (root->left == nullptr) {
                    Node_t *node = createNode(data);
                    root->left = node;
                }
                else {
                    push(root->left, data);
                }
            }
            else if (data > root->data) {
                if (root->right == nullptr) {
                    Node_t *node = createNode(data);
                    root->right = node;
                }
                else {
                    push(root->right, data);
                }
            }
        }

    public:
        void pushLeft(T data) {
            Node_t *node = createNode(data);
            if (binaryTree == nullptr) {
                binaryTree = node;
            }
            else {
                binaryTree->left = node;
            }
        }

        void pushRight(T data) {
            Node_t *node = createNode(data);
            if (binaryTree == nullptr) {
                binaryTree = node;
            }
            else {
                binaryTree->right = node;
            }
        }
        
        void printBfsIterative() {
            printInWidthIteratively(binaryTree);
        }

        void printBfsRecusrive() {
            if (binaryTree != nullptr) {
                queue<Node_t *> q;
                q.push(binaryTree);
                printInWidthRecursively(q);
            }
        }

        void printDfsIterative() {
            printInDepthIteratively(binaryTree);
        }

        void printDfsRecursive() {
            printInDepthRecursively(binaryTree);
        }

        void add(T data) {
            push(binaryTree, data);
        }

        ~BinaryTree() {
            __delete__(binaryTree);
        }
};