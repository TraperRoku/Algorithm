//ALGO2 IS1 224A LAB02
//Filip Kaźmierczak
//kf53844@zut.edu.pl
#include <iostream>
#include <sstream>
#include <chrono>
#include <functional>
#include <random>

using namespace std;

using chrono::duration_cast, chrono::milliseconds;

 template <typename T>
 class dynamic_array{
private:
    T* array;
    int size;
    int pojemnosc ;
    const double grow = 1.5;

   void zmienWielkosc(){
if(pojemnosc == 0){
    pojemnosc = 5;
}
       int nowaPojemnosc = grow * pojemnosc;
       T* newArray = new T[nowaPojemnosc];
       for(int i =0 ;i < size; i++){
       newArray[i] = array[i];
       }

         delete[] array;
       pojemnosc = nowaPojemnosc;
       array = newArray;
   }

public:
     dynamic_array() : array(nullptr), size(0), pojemnosc(0) {}

     ~dynamic_array() {
         delete[] array;
     }


void dodajTail(const T& dane){
       if(size == pojemnosc){
           zmienWielkosc();
       }
       array[size] = dane;
       size++;

   }

   T zwrocWynik(int i){

       if(i<size && i>=0){
           return array[i];
       }else {
          cout<<"Indeks poza zakresem"<<endl;
       }
    }


   void podmiana(int i, const T& dane){
       if(i<size && i>=0){
           array[i] = dane;
       }else{
           cout<<"Indeks poza zakresem"<<endl;
       }
   }

    string to_string() const
     {cout<<"rozmiar tablicy "<<size<<endl;
         ostringstream str;
        str << "[" << array[0];
         for (int p = 1; p<size;p++){
             str << "," << array[p];}
         str << "]";
         return str.str();}

     void czystka(){
       delete[] array;
       array = nullptr;
       pojemnosc = 0;
       size = 0;
   }

     static bool comparator(const T& a, const T& b) {
         return a > b;
     }


     void babelkowe_sortowanie() {
         for (int i = 0; i < size - 1; ++i) {
             for (int j = 0; j < size - i - 1; ++j) {
                 if (comparator(array[j], array[j + 1])) {
                     swap(array[j], array[j + 1]);
                 }
             }
         }
     }

      string to_stringKrotszy() const {
        cout<<"rozmiar listy " <<size<<endl;
        if (size == 0)
            return "[]";
       ostringstream str;
        str << "[" << array[size-3];
        str << ", " << array[size-2]<<" "<<array[size-1];
        str << "]";
        return str.str();
    }


 };




int main() {

    dynamic_array<int> *tablica = new dynamic_array<int>;
    auto t1 = chrono::steady_clock::now();
    tablica->dodajTail(323);

    cout << tablica->to_string() << endl;
    auto t11 = chrono::steady_clock::now();
    cout << "czas pomiaru " << t11-t1 << " milisekend" << endl;

    tablica->czystka();

    tablica->dodajTail(444);
    cout << tablica->to_string() << endl;

    tablica->dodajTail(17);
    cout << tablica->to_string() << endl;

    tablica->dodajTail(5);
    cout << tablica->to_string() << endl;
    auto t2 = chrono::steady_clock::now();
    cout<<"Pokaz mi 2 wyraz indeks 1 "<<endl;
    cout<<tablica->zwrocWynik(1)<<endl;

    auto t22 = chrono::steady_clock::now();

    cout << "czas pomiaru " << t22-t2 << " milisekend" << endl;

    tablica->dodajTail(3);
    cout << tablica->to_string() << endl;

    auto t3 = chrono::steady_clock::now();

    cout<<"PODMIANA"<<endl;
    tablica->podmiana(2,77);
    cout << tablica->to_string() << endl;

    auto t33 = chrono::steady_clock::now();

    cout << "czas pomiaru " << t33-t3 << " milisekend" << endl;

    tablica->dodajTail(4);
    cout <<tablica->to_string() << endl;

    tablica->dodajTail(8);
    cout << tablica->to_string() << endl;

    auto t4 = chrono::steady_clock::now();
    cout << "Sortowanie Babelkowe:" << endl;
    tablica->babelkowe_sortowanie();
    cout << tablica->to_string() << endl;
    auto t44 = chrono::steady_clock::now();

    cout << "czas pomiaru " << t44-t4 << " milisekend" << endl;

    tablica->czystka();

    auto t0 = chrono::steady_clock::now();
    for (int i = 0; i < pow(10,4); i++) {
        int dane = rand();
        tablica->dodajTail(dane);

    }

   cout<< tablica->zwrocWynik(998)<<endl;

   /* tablica->babelkowe_sortowanie();*/
    cout << tablica->to_stringKrotszy() << endl;
    auto t01 = chrono::steady_clock::now();


    cout << tablica->to_stringKrotszy() << endl;
    tablica->dodajTail(4);
    cout << tablica->to_stringKrotszy() << endl;
    tablica->czystka();

    cout << "czas pomiaru " << t01-t0 << " milisekend" << endl;

    delete tablica;

    return 0;
}
