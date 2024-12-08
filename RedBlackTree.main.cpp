//ALGO2 IS1 224A LAB04
//Filip Kaźmierczak
//kf53844@zut.edu.pl
#include <iostream>
#include <sstream>
#include <chrono>
#include <functional>
#include <random>

using namespace std;

enum Color {
    RED,
    BLACK
};

using chrono::duration_cast, chrono::milliseconds;

template<typename T>
class Node {
public:
    T data;
    Color color;
    Node* parent;
    Node* left;
    Node* right;
    int index;

    Node(T value) : data(value), color(RED), parent(nullptr), left(nullptr), right(nullptr), index(0) {}
};

template<typename T>
class RedBlackTree {
private:
    Node<T>* root;
    int currentIndex;

public:
    RedBlackTree() : root(nullptr), currentIndex(0) {}

    void wstaw(T value) {
        if (root == nullptr) {
            Node<T>* newNode = new Node<T>(value);
            newNode->color = BLACK;
            root = newNode;
        } else {
            currentIndex = 0;
            Node<T>* newNode = new Node<T>(value);
            reWstaw(root, newNode);
            fixTree(newNode);
        }
        updateIndex(root);


    }

    void fixTree(Node<T>* newNode) {
        Node<T>* parent, *grandparent;

        if (newNode != root && newNode->color == RED && newNode->parent->color == RED) {
            parent = newNode->parent;
            grandparent = parent->parent;

            if (parent == grandparent->left) {
                Node<T>* uncle = grandparent->right;

                if (uncle && uncle->color == RED) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;

                } else {

                    if (newNode == parent->right) {
                        rotacjaLeft(newNode, parent);





                        rotacjaRight(parent, grandparent);
                        swap(parent->color, grandparent->color);

                    }
                }
            } else {
                Node<T>* uncle = grandparent->left;


                if (uncle && uncle->color == RED) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;

                } else {

                    if (newNode == parent->left) {
                        rotacjaRight(newNode, parent);
                        newNode = parent;
                        parent = newNode->parent;
                    }

                    rotacjaLeft(parent, grandparent);
                    swap(parent->color, grandparent->color);

                }
            }
        }

        root->color = BLACK;
    }



    Node<T>* szukaj(T value) const {
        return reSzukaj(root, value);
    }

    void preOrder() const {
        preOrder(root);
    }

    void inOrder() const {
        inOrder(root);
    }

    int getHeight() const {
        return height(root) - 1;
    }

    void czystka() {
        reCzystka(root);
        root = nullptr;
    }

    std::string toString() const {
        if (root == nullptr) {
            return "NULL";
        }
        stringstream result;
        result << "height: " << getHeight() << endl;
        result << "{" << endl;
        toString(root, result);
        result << "}" << endl;
        return result.str();
    }



private:


    void rotacjaLeft(Node<T>* child, Node<T>* parent) {
        if (parent->parent != nullptr) {
            if (parent == parent->parent->left) {
                parent->parent->left = child;
            } else {
                parent->parent->right = child;
            }
        } else {
            root = child;
        }

        child->parent = parent->parent;
        parent->parent = child;
        parent->right = child->left;

        if (child->left != nullptr) {
            child->left->parent = parent;
        }

        child->left = parent;
    }

    void rotacjaRight(Node<T>* child, Node<T>* parent) {
        if (parent->parent != nullptr) {
            if (parent == parent->parent->left) {
                parent->parent->left = child;
            } else {
                parent->parent->right = child;
            }
        } else {
            root = child;
        }

        child->parent = parent->parent;
        parent->parent = child;
        parent->left = child->right;

        if (child->right != nullptr) {
            child->right->parent = parent;
        }

        child->right = parent;
    }

    void reWstaw(Node<T>* currentNode, Node<T>* newNode) {
        if (newNode->data < currentNode->data) {
            if (currentNode->left == nullptr) {
                currentNode->left = newNode;
                newNode->parent = currentNode;
            } else {
                reWstaw(currentNode->left, newNode);
            }
        } else {
            if (currentNode->right == nullptr) {
                currentNode->right = newNode;
                newNode->parent = currentNode;
            } else {
                reWstaw(currentNode->right, newNode);
            }
        }
    }

    Node<T>* reSzukaj(Node<T>* currentNode, T value) const {
        if (currentNode == nullptr) {
            return nullptr;
        }
        if (currentNode->data == value) {
            return currentNode;
        }
        if (value < currentNode->data) {
            return reSzukaj(currentNode->left, value);
        } else {
            return reSzukaj(currentNode->right, value);
        }
    }

    void preOrder(Node<T>* currentNode) const {
        if (currentNode == nullptr) {
            return;
        }
        cout << currentNode->data << " (" << (currentNode->color == RED ? "RED" : "BLACK") << ") ";
        preOrder(currentNode->left);
        preOrder(currentNode->right);
    }

    void inOrder(Node<T>* currentNode) const {
        if (currentNode == nullptr) {
            return;
        }
        inOrder(currentNode->left);
        cout << currentNode->data << " (" << (currentNode->color == RED ? "RED" : "BLACK") << ") ";
        inOrder(currentNode->right);
    }

    int height(Node<T>* currentNode) const {
        if (currentNode == nullptr) {
            return 0;
        }
        int leftHeight = height(currentNode->left);
        int rightHeight = height(currentNode->right);
        return max(leftHeight, rightHeight) + 1;
    }

    void reCzystka(Node<T>*& currentNode) {
        if (currentNode == nullptr) {
            return;
        }
        reCzystka(currentNode->left);
        reCzystka(currentNode->right);
        delete currentNode;
        currentNode = nullptr;
    }

    void updateIndex(Node<T>* currentNode) {
        if (currentNode == nullptr) {
            return;
        }
        currentNode->index = currentIndex++;
        updateIndex(currentNode->left);
        updateIndex(currentNode->right);
    }

    void toString(Node<T>* currentNode, stringstream& result) const {
        if (currentNode == nullptr) {
            return;
        }

        result << "(" << currentNode->index << ": [color: " << (currentNode->color == RED ? "RED" : "BLACK") << ", p: ";
        if (currentNode->parent) {
            result << currentNode->parent->data;
        } else {
            result << "NULL";
        }
        result << ", l: ";
        if (currentNode->left) {
            result << currentNode->left->data;
        } else {
            result << "NULL";
        }
        result << ", r: ";
        if (currentNode->right) {
            result << currentNode->right->data;
        } else {
            result << "NULL";
        }
        result << "], data: " << currentNode->data << ")" << endl;
        toString(currentNode->left, result);
        toString(currentNode->right, result);
    }



};

int main() {
    RedBlackTree<int> *tree = new RedBlackTree<int>();

     default_random_engine gen(time(nullptr));
  uniform_int_distribution<int> dist(-500, 500);

/*  auto t2 = std::chrono::steady_clock::now();*/
/*
  tree->wstaw(4);
  tree->wstaw(2);
  tree->wstaw(6);
  tree->wstaw(1);
  tree->wstaw(3);
  tree->wstaw(5);
  tree->wstaw(7);
  tree->wstaw(8);
  tree->wstaw(9);
*/

/*
tree->wstaw(2);
tree->wstaw(1);
tree->wstaw(4);
tree->wstaw(9);
tree->wstaw(5);
//1 2 4 5 9
  cout << "ToString " << tree->toString() << endl;
  cout<<"preOrder"<<endl;
  tree->preOrder();

  cout<<endl;
  cout<<"inOrder"<<endl;
  tree->inOrder();
  cout<<endl;
*/



/*
  auto t22 = std::chrono::steady_clock::now();
  cout << "czas pomiaru " << duration_cast<milliseconds>(t22 - t2).count() << " milisekend" << endl;
*/

  tree->czystka();
/*

  auto t1 = std::chrono::steady_clock::now();
  for(int i=0;i<pow(10,1);i++){
      int dane = rand();
      tree->wstaw(dane);
  }
  cout << tree->toString();

    cout<<endl;
    cout<<"inOrder"<<endl;
    tree->inOrder();

    cout<<endl;
    cout<<"preOrder"<<endl;
    tree->preOrder();
    cout<<endl;

  auto t11 = std::chrono::steady_clock::now();
  cout << "czas pomiaru " << duration_cast<milliseconds>(t11 - t1).count() << " milisekend" << endl;
*/

    tree->wstaw(4);
    tree->wstaw(2);
    tree->wstaw(6);
    tree->wstaw(1);
    tree->wstaw(3);
    tree->wstaw(5);
    tree->wstaw(7);
    tree->wstaw(8);
    tree->wstaw(9);
    cout<<tree->toString()<<endl;
  tree->czystka();
  delete tree;
  return 0;
}
