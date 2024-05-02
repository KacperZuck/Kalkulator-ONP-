
#include <iostream>
using namespace std;

class ListaLicznik {
public:
    ListaLicznik* next;
    int liczba;
    ListaLicznik(int value) : liczba(value), next(nullptr) {
        liczba = value;
    }
};

class StosMinMax {
private:
    ListaLicznik* topElement;
public:
    StosMinMax() : topElement(nullptr) {}

    ~StosMinMax() {
        while (topElement) {
            ListaLicznik* temp = topElement;
            topElement = topElement->next;
            delete temp;
        }
    }

    void DodajLicznik() {
        int value = 1;  
        ListaLicznik* Nowy = new ListaLicznik(value);   // tu blad
        Nowy->next = topElement;
        topElement = Nowy;
    }

    void Usun() {
        if (isEmpty()) {
            return;
        }
        else {
            ListaLicznik* Nowy = topElement;
            topElement = topElement->next;
            delete Nowy;
        }
    }

    void Zwieksz() {
        if (isEmpty()) {
            return;
        }
        else {
            int buf = topElement->liczba;
            ++buf;
            topElement->liczba = buf;
        }
    }

    int Liczba() {
        if (isEmpty()) {
            return 0;
        }
        else {
            int number = topElement->liczba;
            return number;
        }
    }

    bool isEmpty() const {
        return topElement == nullptr;
    }
};

template<typename Type, size_t Size>
class Lista {
public:
    Type data[Size];
    size_t length;
    Lista* next;

    Lista(const Type* value, size_t len) : length(len), next(nullptr) {
        size_t i = 0;
        while (i < len && i < Size) {
            data[i] = value[i];
            ++i;
        }
    }
};

template<typename Type, size_t Size>
class Stos {
private:
    Lista<Type, Size>* topElement;
    size_t wskaznik;

public:
    Stos() : topElement(nullptr), wskaznik(0) {}

    ~Stos() {
        while (topElement) {
            Lista<Type, Size>* temp = topElement;
            topElement = topElement->next;
            delete temp;
        }
    }

    void Dodaj(Type* value) {
        size_t len = 0, i = 0;
        while (value[i] != '\0'){  
            len++;
            i++;
        }
        Lista<Type, Size>* Nowy = new Lista<Type, Size>(value, len);
        Nowy->next = topElement;
        topElement = Nowy;
    }

    void Zdejmij() {
        if (isEmpty()) {
            return;
        }
        else {
            Lista<Type, Size>* Nowy = topElement;
            topElement = topElement->next;
            delete Nowy;
        }
    }

    Type* top() {
        if (isEmpty()) {
            return nullptr;
        }
        else {
            char* c = new char[Size];
            int i = 0;
            for( ;i < topElement->length ; i++) {
                c[i] = topElement->data[i];
            }
            c[i] = '\0';
            return c;    
            delete[] c;
        }
    }

    void Odwroc() {

        if (isEmpty() || wskaznik == 1) {
            return;
        }
        Lista<Type, Size>* prev = nullptr;
        Lista<Type, Size>* current = topElement;
        Lista<Type, Size>* next = nullptr;

        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }

        topElement = prev;                
    }

    void WypiszStos() const {
        if (isEmpty()) {
            return;
        }
        Lista<Type, Size>* current = topElement;


        while (current != nullptr) {
            size_t len = current->length;
            for (size_t i = 0; i < len; i++) { 
                if (current->data[i] == -16) {
                    break;
                }
                else {
                    cout << current->data[i];
                }
            }
            cout << " ";
            current = current->next;
        }
        cout << endl;
        delete current;
    }

    bool isEmpty() const {
        return topElement == nullptr;
    }
};




template <typename Type>

class Lista2 {
public:
    Type data;  
    Lista2* next;

    Lista2(Type value) : data(value), next(nullptr){}
};

template<typename Type>
class StosWynik {
private:
    Lista2<Type>* topElement;
    size_t size;

public:
    StosWynik() : topElement(nullptr), size(0) {}

    ~StosWynik() {
        while (topElement) {
            Lista2<Type>* temp = topElement;
            topElement = topElement->next;
            delete temp;
        }
    }

    void Dodaj(const Type& value) {
        Lista2<Type>* Nowy = new Lista2<Type>(value);
        Nowy->next = topElement;
        topElement = Nowy;
        size++;
    }

    void Zdejmij() {
        if (isEmpty()) {
            return;
        }
        else {
            Lista2<Type>* temp = topElement;
            topElement = topElement->next;
            delete temp;
            size--;
        }
    }

    Type& top() {
        if (isEmpty()) {
            static Type buf;
            return  buf;
        }
        else {
            return topElement->data;
        }
    }

    bool isEmpty() const {
        return topElement == nullptr;
    }

    size_t GetSize() const {
        return size;
    }

    void WypiszStos() const {
        if (isEmpty()) {
            return;
        }
        Lista2<Type>* current = topElement;

        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        delete current;
    }
};
