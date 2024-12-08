//ALGO2 IS1 224A LAB06
//Filip Kaümierczak
//kf53844@zut.edu.pl
#include <iostream>
#include <list>
#include <sstream>
#include <ctime>

using namespace std;

template<typename V>
class hashTable {
private:
    const double stala = 0.75;
    int size = 0;
    int capacity = 5;
    list<pair<string, V>>* table = new list<pair<string, V>>[capacity];

    void reHash() {
        capacity = capacity * 2;

        list<pair<string, V>>* newTable = new list<pair<string, V>>[capacity];

        for (int i = 0; i < capacity / 2; i++) {
            for (auto& item : table[i]) {
                int newIndex = funkcjaHashujaca(item.first) % capacity;
                newTable[newIndex].push_back(item);
            }
        }

        delete[] table;
        table = newTable;
    }

    int funkcjaHashujaca(const string& key) {
        int hash = 0;
        int size1 = key.length();

        for (int i = 0; i < size1; i++) {
            hash = (hash * 31 + key[i]) % capacity;
        }
        return hash;
    }

public:

    void wstaw(string k, V v) {
        int index = funkcjaHashujaca(k) % capacity;

        for (auto& element : table[index]) {
            if (element.first == k) {
                element.second = v;
                return;
            }
        }

        table[index].emplace_back(k, v);
        size++;

        if (size > stala * capacity) {
            reHash();
        }
    }

    pair<string, V>* szukaj(string k) {
        int index = funkcjaHashujaca(k) % capacity;
        for (auto& item : table[index]) {
            if (item.first == k) {
                return &item;
            }
        }
        return nullptr;
    }

    bool usuwanko(string k) {
        pair<string, V>* doUsuniecia = szukaj(k);
        if (doUsuniecia != nullptr) {
            int index = funkcjaHashujaca(k) % capacity;

            for (auto it = table[index].begin(); it != table[index].end(); it++) {
                if (*it == *doUsuniecia) {
                    table[index].erase(it);
                    size--;
                    return true;
                }
            }
        }

        return false;
    }

    void czystka() {
        size = 0;
        capacity = 5;
        delete[] table;
        table = new list<pair<string, V>>[capacity];
    }

    string to_string() const {
        stringstream ss;
        ss << "size: " << size << "\n";
        ss << "capacity: " << capacity << "\n";
        ss << "tabblica:\n{\n";

        for (int i = 0; i < capacity; ++i) {
            if (!table[i].empty()) {
                ss << i << ": ";
                for (const auto& element : table[i]) {
                    ss << element.first << " -> " << element.second << "; ";
                }
                ss << "\n";
            }
        }

        ss << "}\n";

        return ss.str();
    }
};

int main() {
    srand(time(nullptr));

    hashTable<int>* myHashTable = new hashTable<int>;

    clock_t start = clock();

    for (int i = 0; i < 100000; i++) {
        int randomValue = rand() % 1000;
        string randomKey;


        stringstream keyStream;
        keyStream << "key" << i;
        randomKey = keyStream.str();

        myHashTable->wstaw(randomKey, randomValue);
    }

    clock_t end = clock();
    double czas = double(end - start) / CLOCKS_PER_SEC * 1000.0;


    cout << "CZAS "<<czas<<endl;



    myHashTable->czystka();

    cout << myHashTable->to_string() << endl;

    cout<<"Nic sie nie wyswietlilo ? "<<endl;

    myHashTable->wstaw("KLUCZ1",1);
    myHashTable->wstaw("KLUCZ2",2);
    myHashTable->wstaw("KLUCZ4",4);
    cout << myHashTable->to_string() << endl;

    clock_t start1 = clock();
    cout<<"usuwam"<<endl;
if( myHashTable->usuwanko("KLUCZ1")){
    cout<<"Prawidlowo usuniecie klucza KLUCZ1"<<endl;
}else{
    cout<<"Nie pyklo"<<endl;
}


cout<<myHashTable->szukaj("KLUCZ2")<<" <-klucz2"<<endl;
cout<<myHashTable->szukaj("KLUCZ48923")<<" <-KLUCZ48923"<<endl;

    clock_t end1 = clock();
    double czas1 = double(end1 - start1) / CLOCKS_PER_SEC * 1000.0;

    cout << "CZAS "<<czas1<<endl;

    cout << myHashTable->to_string() << endl;

    delete myHashTable;

    return 0;
}
