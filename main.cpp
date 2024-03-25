#include <iostream>
#include <sstream>
#include <string>

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

class AVLTree {
    private:
        Node* root;

        int getHeight(Node* node) {
            if (node == nullptr)
                return 0;
            return node->getHeight();
        }

        int getBalanceFactor(Node* node) {
            if (node == nullptr)
                return 0;
            return getHeight(node->getLeft()) - getHeight(node->getRight());
        }

        void updateHeight(Node* node) {
            node->setHeight(1 + std::max(getHeight(node->getLeft()), getHeight(node->getRight())));
        }

        Node* rotateRight(Node* y) {
            Node* x = y->getLeft();
            Node* T2 = x->getRight();

            x->setRight(y);
            y->setLeft(T2);

            updateHeight(y);
            updateHeight(x);

            return x;
        }

        Node* rotateLeft(Node* x) {
            Node* y = x->getRight();
            Node* T2 = y->getLeft();

            y->setLeft(x);
            x->setRight(T2);

            updateHeight(x);
            updateHeight(y);

            return y;
        }

        Node* insertHelper(Node* node, int value) {
            if (node == nullptr) {
                node = new Node(value);
                return node;
            }

            if (value < node->getData())
                node->setLeft(insertHelper(node->getLeft(), value));
            else if (value > node->getData())
                node->setRight(insertHelper(node->getRight(), value));
            else
                return node; // Duplicate values are not allowed in AVL tree

            updateHeight(node);

            int balanceFactor = getBalanceFactor(node);

            // Left Left Case
            if (balanceFactor > 1 && value < node->getLeft()->getData())
                return rotateRight(node);

            // Right Right Case
            if (balanceFactor < -1 && value > node->getRight()->getData())
                return rotateLeft(node);

            // Left Right Case
            if (balanceFactor > 1 && value > node->getLeft()->getData()) {
                node->setLeft(rotateLeft(node->getLeft()));
                return rotateRight(node);
            }

            // Right Left Case
            if (balanceFactor < -1 && value < node->getRight()->getData()) {
                node->setRight(rotateRight(node->getRight()));
                return rotateLeft(node);
            }

            return node;
        }

        Node* deleteHelper(Node* root, int value) {
            if (root == nullptr)
                return root;

            if (value < root->getData())
                root->setLeft(deleteHelper(root->getLeft(), value));
            else if (value > root->getData())
                root->setRight(deleteHelper(root->getRight(), value));
            else {
                // Node to be deleted found

                // Case 1: Leaf node
                if (root->getLeft() == nullptr && root->getRight() == nullptr) {
                    delete root;
                    root = nullptr;
                }
                // Case 2: Node with only one child
                else if (root->getLeft() == nullptr || root->getRight() == nullptr) {
                    Node* child = root->getLeft() ? root->getLeft() : root->getRight();
                    Node* predecessor = findPredecessor(root);

                    if (predecessor != nullptr) {
                        // Swap the values of the node to be deleted and its predecessor
                        int temp = root->getData();
                        root->setData(predecessor->getData());
                        predecessor->setData(temp);

                        // Recursively delete the predecessor
                        root->setLeft(deleteHelper(root->getLeft(), predecessor->getData()));
                    }
                    else {
                        // If there is no predecessor, replace the node with its child
                        delete root;
                        root = child;
                    }
                }
                // Case 3: Node with two children
                else {
                    Node* predecessor = findPredecessor(root);
                    root->setData(predecessor->getData());
                    root->setLeft(deleteHelper(root->getLeft(), predecessor->getData()));
                }
            }

            if (root == nullptr)
                return root;

            updateHeight(root);

            int balanceFactor = getBalanceFactor(root);

            // Left Left Case
            if (balanceFactor > 1 && getBalanceFactor(root->getLeft()) >= 0)
                return rotateRight(root);

            // Left Right Case
            if (balanceFactor > 1 && getBalanceFactor(root->getLeft()) < 0) {
                root->setLeft(rotateLeft(root->getLeft()));
                return rotateRight(root);
            }

            // Right Right Case
            if (balanceFactor < -1 && getBalanceFactor(root->getRight()) <= 0)
                return rotateLeft(root);

            // Right Left Case
            if (balanceFactor < -1 && getBalanceFactor(root->getRight()) > 0) {
                root->setRight(rotateRight(root->getRight()));
                return rotateLeft(root);
            }

            return root;
        }

        Node* findPredecessor(Node* node) {
            if (node->getLeft() == nullptr)
                return nullptr;

            Node* current = node->getLeft();
            while (current->getRight() != nullptr)
                current = current->getRight();

            return current;
        }

    public:
        AVLTree() {
            this->root = nullptr;
        }

        Node* getRoot() {
            return this->root;
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

        Node* deleteNode(int value) {
            root = deleteHelper(getRoot(), value);
            return root;
        }

        Node* search(int value) {
            Node* currentNode = getRoot();
            while (currentNode != nullptr && currentNode->getData() != value) {
                if (value < currentNode->getData()) {
                    currentNode = currentNode->getLeft();
                } else {
                    currentNode = currentNode->getRight();
                }
            }
            return currentNode;
        }

};


int main() {
    AVLTree avlTree;

    std::string input;
    std::getline(std::cin, input);

    std::istringstream iss(input);
    std::string move;
    while (iss >> move) {
        if (move.length() == 2 && move[0] == 'A' && std::isdigit(move[1])) {
            int value = move[1] - '0';
            avlTree.insert(value);
        } else if (move.length() == 2 && move[0] == 'D' && std::isdigit(move[1])) {
            int value = move[1] - '0';
            avlTree.deleteNode(value);
        } else if (move == "PRE") {
            if (avlTree.getRoot() == nullptr) {
            } else {
                std::cout << "Preorder traversal: ";
                avlTree.preOrder(avlTree.getRoot());
                std::cout << std::endl;
            }
        } else if (move == "POST") {
            if (avlTree.getRoot() == nullptr) {
                std::cout << "Empty" << std::endl;
            } else {
                avlTree.postOrder(avlTree.getRoot());
                std::cout << std::endl;
            }
        } else if (move == "IN") {
            if (avlTree.getRoot() == nullptr) {
                std::cout << "Empty" << std::endl;
            } else {
                avlTree.inOrder(avlTree.getRoot());
                std::cout << std::endl;
            }
        }
    }

    return 0;
}