//ALGO2 IS1 224A LAB01
//Filip Kaźmierczak
//kf53844@zut.edu.pl
#include <iostream>
#include <sstream>
#include <functional>
#include <chrono>
#include <ctime>
#include <random>

using namespace std;

using chrono::duration_cast, chrono::milliseconds;

template <typename T>
class linkedList{
private:
    struct Node{
        T dane;
        Node* prev;
        Node* next;

        Node(const T& dane) : dane(dane), prev(nullptr), next(nullptr){}
    };
    Node* head;
    Node* tail;
    int size;
public :
    linkedList() : head(nullptr), tail(nullptr), size(0){}

//    ~linkedList()
//    {
//       czystka();
//    }


    void dodajTyl(const T& dane) {
        Node* newNode = new Node(dane);
        if(head == nullptr){
            head = newNode;
            tail = newNode;
        }else{
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size ++;
    }
    void dodajPrzod(const T& dane){
        Node* newNode = new Node(dane);
        if(head == nullptr){
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    T findNode(int i ){
        if(head == nullptr) {
            cout << "Lista jest pusta" << endl;
            return T();
        }
        else if(i>=size || i<0) {
            cout<<"Poza indeksem"<<endl;
            return T();
        }
        else{
            if(i < size / 2){
                Node* temp = head;
                for(int o = 0; o<i;o++){
                    temp = temp->next;
                }
                return temp->dane;
            }else{
                Node* temp = tail;
                for(int o = size-1; o>i;o--){
                    temp = temp->prev;
                }
                return temp->dane;
            }

        }
    }

    void deleteTail(){
        if(size == 0 ){
            cout << "Lista jest pusta" << endl;
        }
        else if(size ==1 ){
            delete head;
            head = nullptr;
            tail = nullptr;
            size = 0;
        } else{
            tail = tail->prev;
            tail->next = nullptr;
            delete tail->next;
            size --;
        }
    }


    void deleteHead(){
        if (size == 0) {
            cout << "Lista jest pusta" << endl;
        } else if (size == 1) {
            delete head;
            head = nullptr;
            tail = nullptr;
            size = 0;
        } else {
            head = head->next;
            head->prev = nullptr;
            delete head->prev;
            size--;
        }
    }
    void czystka(){
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail =  nullptr;
        size = 0;
}


    void replace(int i, const T& newValue) {
        if (i < 0 || i >= size) {
            cout << "Indeks poza zakresem" << endl;
        }

        if (i == 0) {
            deleteHead();
            dodajPrzod(newValue);
        } else if (i == size - 1) {
            deleteTail();
            dodajTyl(newValue);
        } else {
            Node* tempNode = head;
            for (int o = 0; o < i; o++) {
                tempNode = tempNode->next;
            }
            Node* newNode = new Node(newValue);
            newNode->prev = tempNode->prev;
            newNode->next = tempNode->next;
            tempNode->prev->next = newNode;
            tempNode->next->prev = newNode;
            delete tempNode;
        }
    }


    template<typename Comp>
    Node* znajdz_element(const T& el, Comp comp) const{
        for (auto p = head; p; p = p->next)
            if (comp(el, p->dane))
                return p;
        return nullptr;
    }

    bool usun_element(const T& el, function<bool(const T&, const T&)> comparator) {
        Node* temp = znajdz_element(el, comparator);
        if (temp == nullptr)
            return false;
        if (temp == head) {
            deleteHead();
            return true;
        }
        if (temp == tail) {
            deleteTail();
            return true;
        }
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
        size--;
        return true;
    }

    bool dodajZPorzadkiem(const T& el, function<bool(const T&, const T&)> comparator) {
        Node* newNode = new Node(el);

        if (head == nullptr || comparator(el, head->dane)) {
            dodajPrzod(el);
        } else {
            Node* temp = head;
            while (temp->next && comparator(temp->next->dane, el)) {
                temp = temp->next;
            }

            newNode->next = temp->next;
            newNode->prev = temp;
            if (temp->next) {
                temp->next->prev = newNode;
            }
            temp->next = newNode;

            if (newNode->next == nullptr) {
                tail = newNode;
            }

            size++;
        }

        return true;
    }


    string to_string() const {
    cout<<"rozmiar listy " <<size<<endl; // przeciazenie :)
        if (size == 0)
            return "[]";
        ostringstream str;
        str << "[" << head->dane;
        for (auto p = head->next; p; p = p->next)
            str << ", " << p->dane;
        str << "]";
        return str.str();
    }

    string to_stringKrotszy() const {
        cout<<"rozmiar listy " <<size<<endl;
        if (size == 0)
            return "[]";
       ostringstream str;
        str << "[" << head->dane;
        str << ", " << head->next->dane;
        str << ", " << head->next->next->dane;
        str << "]";
        return str.str();
    }


};


struct some_class
{
    int some_int;
    char some_char;
};

ostream& operator<<(ostream &out, const some_class &obj) {
    out << obj.some_int;
    out << obj.some_char;
    return out;
};




int main() {




    auto t1 = chrono::steady_clock::now();

    auto komp = [](const some_class &a, const some_class &b) {
        return a.some_int == b.some_int  && a.some_char == b.some_char;

    };
    auto komp2 = [](const some_class &a, const some_class &b) {
        return a.some_int < b.some_int;
    };

    linkedList<some_class>* ll = new linkedList<some_class>();
    some_class so ;
    some_class so1 ;
    some_class so2 ;

    so.some_int = 123;
    so.some_char = 'a' ;

    so1.some_int = 1321311;
    so1.some_char = 'k' ;

    so2.some_int = 124;
    so2.some_char = 'b';

  ll->dodajPrzod(so);

  cout<<ll->znajdz_element(so,komp)<<endl;
  cout<< ll->to_string()<<endl;

  ll->dodajPrzod(so1);

  cout<< ll->to_string()<<endl;

  ll->dodajTyl(so2);

  cout<< ll->to_string()<<endl;




    default_random_engine intGen(chrono::high_resolution_clock::now().time_since_epoch().count());
    default_random_engine charGen(chrono::high_resolution_clock::now().time_since_epoch().count() + 1);

    uniform_int_distribution<int> intDist(-50000, 50000);
    uniform_int_distribution<char> charDist('a', 'z');

    some_class randomObject;
    randomObject.some_int = intDist(intGen);
    randomObject.some_char = charDist(charGen);

  ll->dodajZPorzadkiem(randomObject, komp2);

    randomObject.some_int = intDist(intGen);
    randomObject.some_char = charDist(charGen);

  ll->dodajZPorzadkiem(randomObject, komp2);

    randomObject.some_int = intDist(intGen);
    randomObject.some_char = charDist(charGen);

  ll->dodajZPorzadkiem(randomObject, komp2);



  cout<< ll->to_string()<<endl;

  cout<< ll->findNode(1)<<endl;
  cout<< ll->findNode(4)<<endl;

  cout<< ll->to_string()<<endl;

    randomObject.some_int = intDist(intGen);
    randomObject.some_char = charDist(charGen);

  ll->replace(2, randomObject);

  cout<< ll->to_string()<<endl;

  ll->usun_element(so1, komp);

  cout<< ll->to_string()<<endl;

  ll->deleteHead();

  cout<< ll->to_string()<<endl;

  ll->usun_element(so2, komp);

  cout<< ll->to_string()<<endl;

  ll->deleteTail();

  cout<< ll->to_string()<<endl;



  ll->czystka();

  for(int i = 0; i<pow(10,1); i++){


      randomObject.some_int = intDist(intGen);
      randomObject.some_char = charDist(charGen);
      ll->dodajTyl(randomObject);
  }
  cout<<"krotszy STRING"<<endl;
  cout<< ll->to_string()<<endl;


    auto t2 = chrono::steady_clock::now();
  cout << "CZAS W ms : " << duration_cast<milliseconds>(t2 - t1).count() << endl;

  ll->czystka();
  delete ll;


  return 0;
}