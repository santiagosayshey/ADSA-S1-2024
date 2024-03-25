#include <iostream>

class Node {
    private:
        int data;
        Node* left;
        Node* right;
        int height;
    public:
        Node(int data) {
            this->data = data;
            this->left = nullptr;
            this->right = nullptr;
            this->height = 1;
        }
        int getData() {
            return this->data;
        }
        Node* getLeft() {
            return this->left;
        }
        Node* getRight() {
            return this->right;
        }
        int getHeight() {
            return this->height;
        }
        void setData(int data) {
            this->data = data;
        }
        void setLeft(Node* left) {
            this->left = left;
        }
        void setRight(Node* right) {
            this->right = right;
        }
        void setHeight(int height) {
            this->height = height;
        }
};

class BST {
    private:
        Node* root;
    public:
        BST() {
            this->root = nullptr;
        }
        Node* getRoot() {
            return this->root;
        }
        Node* search(int value) {
            Node* currentNode = getRoot();
            while (currentNode != nullptr && currentNode->getData() != value) {
                std::cout << "Searching current node with value: " << currentNode->getData() << std::endl;
                if (value < currentNode->getData()) {
                    currentNode = currentNode->getLeft();
                } else {
                    currentNode = currentNode->getRight();
                }
            }
            return currentNode;
        }
        void inOrder(Node* node) {
            if (node->getLeft() != nullptr) {
                inOrder(node->getLeft());
            }
            
            std::cout << node->getData() << " ";

            if (node->getRight() != nullptr) {
                inOrder(node->getRight());
            }
        }
        void preOrder(Node* node) {
            std::cout << node->getData() << " ";
            if (node->getLeft() != nullptr) {
                preOrder(node->getLeft());
            }
            if (node->getRight() != nullptr) {
                preOrder(node->getRight());
            }
        }
        void postOrder(Node* node) {
            if (node->getLeft() != nullptr) {
                postOrder(node->getLeft());
            }
            if (node->getRight() != nullptr) {
                postOrder(node->getRight());
            }
            std::cout << node->getData() << " ";
        }

        Node* insert(int value) {
            root = insertHelper(getRoot(), value);
            return root;
        }

        Node* insertHelper(Node* node, int value) {
            if (node == nullptr) {
                node = new Node(value);
                return node;
            }

            if (value < node->getData()) {
                node->setLeft(insertHelper(node->getLeft(), value));
                return node;
            }

            if (value > node->getData()) {
                node->setRight(insertHelper(node->getRight(), value));
                return node;
            }
        }   



};


int main() {

    BST bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);
    bst.insert(10);
    bst.insert(25);
    bst.insert(35);
    bst.insert(45);
    bst.insert(55);
    bst.insert(65);
    bst.insert(75);
    bst.insert(90);

    bst.inOrder(bst.getRoot());
    std::cout << std::endl;


    return 0;   
}

/* 
               50
             /    \
           30      70
          /  \    /  \
        20   40  60   80
       /  \  / \  / \  / \
      10 25 35 45 55 65 75 90

 */