//ALGO2 IS1 224A LAB05
//FILIP KAèMIERCZAK
//kf53844@zut.edu.pl

#include <iostream>
#include <sstream>
#include <Math.h>
#include <chrono>
using  namespace std;

template<typename  T>
class BinaryHeap{
public:
    int capacity;
    int size ;
    T* array;

    BinaryHeap() : array(nullptr), size(0), capacity(5) {
        array = new T[capacity];
    }

    ~BinaryHeap() {
        delete[] array;
    }


    void wstaw(T value){

        if(capacity== size){
            powieksz();
        }
        array[size] = value;

        naprawiacz(size);

        size++;

    }
    void czystka(){
        delete[] array;
        array = nullptr;
        size = 0;
        capacity = 5;
        array = new T[capacity];

    }





    std::string to_string() const {
        std::ostringstream result;
        result << "Binary Heap:"<<endl;
        for (int i = 0; i < size; ++i) {
            result << "Index " << i << ": " << array[i] <<
                   " [Parent: ";

            int parentIndex = parent(i);

            if (parentIndex >= 0 && parentIndex < size && parentIndex != i) {
                result << array[parentIndex];
            } else {
                result << "NULL";
            }

            result << ", Left Child: ";
            int leftChildIndex = leftChild(i);
            if (leftChildIndex >= 0 && leftChildIndex < size) {
                result << array[leftChildIndex];
            } else {
                result << "NULL";
            }

            result << ", Right Child: ";
            int rightChildIndex = rightChild(i);
            if (rightChildIndex >= 0 && rightChildIndex < size) {
                result << array[rightChildIndex];
            } else {
                result << "NULL";
            }

            result << "]"<<endl;
        }
        return result.str();
    }

    void pollowanko(){

        if (size > 0) {
            array[0] = array[size - 1];
            size--;


            naprawiaczWDol(0);
        }

    }



private:

    void swap(int parentValue , int key, T array[]){
        T temp = array[key];
        array[key] = array[parentValue];
        array[parentValue] = temp;
    }

    void naprawiaczWDol(int key) {
        int lChild = leftChild(key);
        int rChild = rightChild(key);


        if (lChild < size && rChild < size) {
            int maxChildIndex = (array[lChild] > array[rChild]) ? lChild : rChild;

            if (array[maxChildIndex] > array[key]) {
                swap(maxChildIndex, key, array);
                naprawiaczWDol(maxChildIndex);
            }
        } else if (array[lChild] > array[key]) {
            swap(lChild, key, array);
            naprawiaczWDol(lChild);
        } else if ( array[rChild] > array[key]) {
            swap(rChild, key, array);
            naprawiaczWDol(rChild);
        }
    }








    int parent(int key) const {
        return (key - 1) / 2;
    }

    int leftChild(int key) const {
        return (2 * key) + 1;
    }

    int rightChild(int key) const {
        return (2 * key) + 2;
    }

    void naprawiacz(int key){
        int parentValue = parent(key);

        while(key > 0 && array[parentValue] < array[key]){
            swap(parentValue, key,array);
            key = parentValue;
            parentValue = parent(key);
        }

    }



    void powieksz(){
        capacity = capacity*2;
        T* newArray = new T[capacity];
        for(int i = 0;i<size;i++){
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
    }


};
int main() {
    BinaryHeap<int>* binaryHeap = new BinaryHeap<int>();
   clock_t t1 = clock();

   for(int i = 0; i < pow(10,1); i++){
       int rand1 = rand();
       binaryHeap->wstaw(rand1);
   }
   binaryHeap->czystka();


  /*  for(int i =0;i < pow(10,1) ; i++){
        int dane = rand();
        binaryHeap->wstaw(dane);
    }*/


    cout<<binaryHeap->to_string()<<endl;
    clock_t t2 = clock();
    cout<<"czas "<<(double)t2-t1<<endl;
    binaryHeap->pollowanko();


    cout<<binaryHeap->to_string()<<endl;






    delete binaryHeap;

    return 0;
}
