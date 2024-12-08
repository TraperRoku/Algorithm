//ALGO2 IS1 224A LAB03
//Filip Kaźmierczak
//kf53844@zut.edu.pl
#include <iostream>
#include <sstream>
#include <chrono>
#include <functional>
#include <random>
using namespace std;


using chrono::duration_cast, chrono::milliseconds;

template<typename T>
class Node{
public:
    T data;
    Node* parent;
    Node* left;
    Node* right;
    int index;


    Node(T value) : data(value),parent(nullptr),left(nullptr),right(nullptr),index(0) {}

};

template<typename T>
class BinarySearchTree{
private:
    Node<T>* root;
    int currentIndex;
public:
    BinarySearchTree():root(nullptr),currentIndex(0) {};


    void wstaw(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (root == nullptr) {
            root = newNode;
        } else {
            currentIndex = 0;
            reWstawianie(root, newNode);
        }
        updateIndex(root);
    }



    Node <T>* szukaj(T value){
        return reSzukanie(root, value);
    }
    void preOrder() const {
        preOrder(root);
    }
    void inOrder() const {
        inOrder(root);
    }

    int height() const {
        return height(root) - 1;
    }
    void czystka() {
        reCzystka(root);
        root = nullptr;
    }


    void usun(const T& value) {
        Node<T> *nodeToDelete = szukaj(value);
        if (nodeToDelete != nullptr) {
            reUsuwanie(root, nodeToDelete);
        }
    }


   string toString() const {
        if (root == nullptr) {
            return "NULL";
        }
        stringstream result;
        result << "height: " << height() << endl;
        result << "{"<<endl;
        toString(root, result);
        result << "}"<<endl;

        return result.str();
    }

    void toStringkrotki() const {
        if (root == nullptr) {
            cout<< "NULL";
        }
        cout << "(" << "1" << ": [parent= ";
        if (root->data) {
            cout << root->data;
        } else {
            cout << "NULL";
        }
        cout << ", left= ";
        if (root->left->data) {
            cout << root->left->data;
        } else {
            cout << "NULL";
        }
        cout << ", right= ";
        if (root->right->data) {
            cout << root->right->data;
        } else {
            cout << "NULL";
        }
    }


private:


    void reWstawianie(Node<T>* currentNode, Node<T>* newNode){
        if(newNode->data < currentNode->data){
            if(currentNode->left== nullptr){
                currentNode->left = newNode;
                newNode->parent = currentNode;
            }else{
                reWstawianie(currentNode->left, newNode);
            }
        }else{
            if(currentNode->right == nullptr){
                currentNode->right = newNode;
                newNode->parent = currentNode;
            }else{
                reWstawianie(currentNode->right, newNode);
            }

        }
    }

    Node<T>* reSzukanie(Node<T>* currentNode, T value){
        if(currentNode == nullptr){
            return nullptr;
        }
        if(currentNode->data == value){
            return currentNode;
        }
        if(value < currentNode->data){
            return reSzukanie(currentNode->left, value);
        }else{
            return reSzukanie(currentNode->right, value);
        }

    }

    void reUsuwanie(Node<T>*& currentNode, Node<T>* nodeToDelete){
        if(currentNode == nullptr){
            return;
        }
        if(nodeToDelete->data < currentNode->data){
            reUsuwanie(currentNode->left, nodeToDelete);
        }else if(nodeToDelete->data > currentNode->data){
            reUsuwanie(currentNode->right, nodeToDelete);
        }else{
            if(currentNode->left == nullptr && currentNode->right == nullptr){
                delete currentNode;
                currentNode = nullptr;
            }else if(currentNode->left == nullptr){
                Node<T>* temp = currentNode;
                currentNode = currentNode->right;
                delete temp;
            }else if(currentNode -> right == nullptr){
                Node<T>* temp = currentNode; //adres
                currentNode = currentNode->left;
                delete temp; //usuwamy adres
            }else{
                Node<T>* minRight = findMin(currentNode->right);
                currentNode->data = minRight->data;
                reUsuwanie(currentNode->right, minRight);
            }
        }
    }
    Node<T>* findMin(Node<T>* node) const {
        if (node->left == nullptr) {
            return node;
        }
        return findMin(node->left);
    }

    void preOrder(Node<T>* currentNode) const {
        if (currentNode == nullptr) {
            return;
        }
        cout << currentNode->data << " ";
        preOrder(currentNode->left);
        preOrder(currentNode->right);
    }

    void inOrder(Node<T>* currentNode) const {
        if (currentNode == nullptr) {
            return;
        }
        inOrder(currentNode->left);
        cout << currentNode->data << " ";
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

        result << "(" << currentNode->index << ": [p: ";
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
    BinarySearchTree<int> *tree = new BinarySearchTree<int>();


  /*  default_random_engine gen(time(nullptr));
    uniform_int_distribution<int> dist(-500, 500);
*/
    tree->wstaw(4);
    tree->wstaw(2);
    tree->wstaw(1);
    tree->wstaw(3);
    tree->wstaw(6);
    tree->wstaw(7);
    tree->wstaw(5);



    cout<<tree->toString()<<endl;

  /*  tree->usun(4);

    cout<<tree->toString()<<endl;
    auto tpre1 = std::chrono::steady_clock::now();
    cout<<"preOrder"<<endl;
    tree->preOrder();
    auto tpre2 = std::chrono::steady_clock::now();
    cout << "czas pomiaru " << duration_cast<milliseconds>(tpre2 - tpre1).count() << " milisekend" << endl;

    cout << endl;

    auto tIn1 = std::chrono::steady_clock::now();
    cout<<"inOrder"<<endl;
    tree->inOrder();
    auto tIn2 = std::chrono::steady_clock::now();
    cout << "czas pomiaru " << duration_cast<milliseconds>(tIn2 - tIn1).count() << " milisekend" << endl;
    tree->czystka();*/






    /*auto t4 = std::chrono::steady_clock::now();

    tree->wstaw(5);
    tree->wstaw(2);
    tree->wstaw(10);
    tree->wstaw(15);
    tree->wstaw(7);
    tree->wstaw(20);
    tree->wstaw(40);

    cout << tree->toString();
    auto t44 = std::chrono::steady_clock::now();*/
   /* cout << "czas pomiaru " << duration_cast<milliseconds>(t44 - t4).count() << " milisekend" << endl;*/
    tree->czystka();


  /*  auto t111 = std::chrono::steady_clock::now();
    for (int i = 0; i < pow(10,4); i++) {
        int dane = rand();
        tree->wstaw(dane);
    }
*//*    cout << tree->toString();*//*

    auto t222 = std::chrono::steady_clock::now();
    cout << "czas pomiaru " << duration_cast<milliseconds>(t222 - t111).count() << " milisekend" << endl;

    cout <<"Szukaj  "<< tree->szukaj(41) << endl;//adres*/

/*
    Node<int> *result = tree->szukaj(6);
    if (result != nullptr) {
        cout << result->data << endl;
    } else {
        cout << "Nie ma" << endl;
*/

/*

        tree->usun(-5);
    auto t22222 = std::chrono::steady_clock::now();
cout<<"preOrder"<<endl;
        tree->preOrder();

        cout << endl;

        cout<<"inOrder"<<endl;
        tree->inOrder();
    auto t33333 = std::chrono::steady_clock::now();
    cout << "czas pomiaru " << duration_cast<milliseconds>(t33333 - t22222).count() << " milisekend" << endl;
        cout << endl;
        int treeHeight = tree->height();
        cout << treeHeight << " wysokosc drzewa" << endl;

        cout << tree->toString();


        auto t11 = std::chrono::steady_clock::now();
        tree->czystka();
        auto t22 = std::chrono::steady_clock::now();
        cout << "czas pomiaru " << duration_cast<milliseconds>(t22 - t11).count() << " milisekend" << endl;


        cout << tree->toString();
        cout << "jest cos ?" << endl;
*/


        /*    auto t1 = std::chrono::steady_clock::now();
            for (int i = 0; i < pow(10, 4); i++) {
                int dane = rand();
                tree->wstaw(dane);

            }

            cout << tree->toString();
            auto t2 = std::chrono::steady_clock::now();

            cout << "czas pomiaru " << duration_cast<milliseconds>(t2 - t1).count() << " milisekend" << endl;*/

        delete tree;

        return 0;
    }
