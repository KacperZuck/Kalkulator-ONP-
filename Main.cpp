
#include <iostream>
#include "class.cpp"
using namespace std;

#define Data_Size 6


int Priorytet(char* znak) {

    if (znak[0] == '(' || znak[0] == ')') {
        return 4;
    }
    else if (znak[0] == 'N') {  // N  negacja
        return 3;
    }
    else if (znak[0] == 'I') {  // IF
        return 3;
    }
    else if (znak[0] == 'M') {  // MIN MAX
        return 3;
    }
    else if (znak[0] == '*' || znak[0] == '/') {
        return 2;
    }
    else if (znak[0] == '+' || znak[0] == '-') {
        return 1;
    }
    return 0;
}

int Dzialanie(int a, int b, char* znak) {
    
    switch (znak[0]){
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;   
    }
    cout << "Podano nieprawidlowy operator" << endl;
    return 0;
}
bool CzyCyfra(char* znak) {
    return znak[0] >= '0' && znak[0] <= '9';
}
bool CzyOperator(char* znak) {
    return znak[0] == '+' || znak[0] == '-' || znak[0] == '*' || znak[0] == '/';
}
int ZmienInt(char* znak) {

    int liczba=0, i=0;
    while (znak[i] != '\0') { 
        if (znak[i] >= '0' && znak[i] <= '9') { 
            liczba = 10 * liczba + (znak[i] - '0');
            ++i;
        } else {
            break;
        }
    }
    return liczba;
}

void Liczba(char znak, Stos<char,Data_Size> &Wyjscie) {
    char* c = new char[Data_Size];
    int i = 0;
    while (znak != ' ') {
        c[i] = znak;
        cin.get(znak);
        i++;
    }
    c[i] = '\0';
    Wyjscie.Dodaj(c);
    delete[] c;
}

void Wynik(StosWynik<int>& stos, Stos<char, Data_Size>& Wyjscie) {


    int a, b, c;
    while ( !Wyjscie.isEmpty() ) { 
        if (CzyCyfra(Wyjscie.top())) {
            stos.Dodaj(ZmienInt(Wyjscie.top()));
            Wyjscie.Zdejmij();
        }
        else {

            if (CzyOperator(Wyjscie.top())) {
                char* buf = Wyjscie.top();      // SPROBOWAC PODMIENIC
                //cout << "Dzialanie: ";
                cout << buf[0] << " ";
                stos.WypiszStos();
                cout << endl;
                if (stos.GetSize() < 2) {
                    cout << "ERROR Niepoprawne wyrazenie ONP" << endl;
                    return;
                }

                b = stos.top();
                stos.Zdejmij();
                a = stos.top();
                stos.Zdejmij();

                if (b != 0) {
                    // cout << "TEST: " << stos.top() << endl;
                    stos.Dodaj(Dzialanie(a, b, Wyjscie.top()));
                    Wyjscie.Zdejmij();
                }
                else {  // b == 0
                    if (Wyjscie.top()[0] == '/') {
                        cout << "ERROR" << endl << endl;
                        return;   
                    }
                    else {
                        //  cout << "TEST: " << Stos.top() << endl;
                        stos.Dodaj(Dzialanie(a, b, Wyjscie.top()));
                        Wyjscie.Zdejmij();
                    }
                }
            }
            else if (Wyjscie.top()[0] == 'N') {
                char* buf = Wyjscie.top();
                cout << buf[0] << " ";
                stos.WypiszStos();
                cout << endl;
                a = stos.top();
                stos.Zdejmij();
                stos.Dodaj(-a);
                Wyjscie.Zdejmij();
            }
            else if (Wyjscie.top()[0] == 'I') { 
                char* buf = Wyjscie.top();
                cout << buf[0] << buf[1] << " ";
                stos.WypiszStos();
                cout << endl;
                if (stos.GetSize() < 3) {
                    cout << "ERROR Niepoprawne wyrazenie ONP" << endl;
                    return;
                }
                c = stos.top();
                stos.Zdejmij();
                b = stos.top();
                stos.Zdejmij();
                a = stos.top();
                stos.Zdejmij();
                if (a > 0) {
                    stos.Dodaj(b);
                    Wyjscie.Zdejmij();
                }else {
                    stos.Dodaj(c);
                    Wyjscie.Zdejmij();
                }
            }
            else if (Wyjscie.top()[0] == 'M') {
                
                int wynik = stos.top();
                int n=0,i=0;
                while (Wyjscie.top()[3+i] != '\0') { 
                    if (Wyjscie.top()[3+i] >= '0' && Wyjscie.top()[3+i] <= '9') { 
                        n = 10 * n + (Wyjscie.top()[3+i] - '0');
                        ++i;
                    } 
                }

                char* buf = Wyjscie.top();
                cout << buf[0] << buf[1] << buf[2] << n << " ";
                stos.WypiszStos();
                cout << endl;

                if(Wyjscie.top()[1]== 'A'){
                 //   cout << "TEST " << Wyjscie.top()[3] << endl;
                    for (int i = 0; i < n; i++) {   //MAX
                        int liczba = stos.top();
                        if (liczba > wynik) {
                            wynik = liczba;
                        }
                        stos.Zdejmij();
                    }
                }
                else{
                    for (int i = 0; i < n; i++) {   //MIN
                        int liczba = stos.top();
                        if (liczba < wynik) {
                            wynik = liczba;
                        }
                        stos.Zdejmij();
                    }
                }
                stos.Dodaj(wynik);
                Wyjscie.Zdejmij();
            }
        }
    }

    //cout << "Wynik: ";
    cout << stos.top() << endl;
}

int main() {
    Stos<char, Data_Size> Token;
    Stos<char, Data_Size> Wyjscie;
    StosWynik<int> Stos;
    StosMinMax Licznik;

    char znak[Data_Size];
    int wiersze;
    cin >> wiersze;

    for (int i = 0; i < wiersze; i++) {

        char x = 'a';
        while (x != '.') {
            cin >> znak[0];
            x = znak[0];

            char* oper = new char[Data_Size];
            oper[0] = x;
            oper[1] = '\0';

            if (x == '(') {
                Token.Dodaj(oper);
                Licznik.DodajLicznik();
            }
            else if (x == ')') {
                while (!Token.isEmpty()) {
                    if (Token.top()[0] == '(') {
                        Token.Zdejmij();    // zdejmuje nawias
                        if( !Token.isEmpty() ){
                            if (Token.top()[0] == 'M') {    
                            char* buf = Token.top();
                            if(Licznik.Liczba() > 9){
                                int jednosci = Licznik.Liczba()%10, dziesiatki = Licznik.Liczba()/10;
                                buf[3]= '0' + dziesiatki;
                                buf[4]= '0' + jednosci; 
                                buf[5]='\0';
                            }
                            else{
                            buf[3] = '0' + Licznik.Liczba();    
                            buf[4] = '\0';
                            }
                            Wyjscie.Dodaj(buf);
                            Token.Zdejmij();
                            }
                        }
                        Licznik.Usun();
                        break;
                    }
                    else {
                        Wyjscie.Dodaj(Token.top());
                        Token.Zdejmij();
                    }
                }
            }
            else if (x == 'N') {
                if (Token.isEmpty() == true) {
                    Token.Dodaj(oper);
                }
                else {
                    if (Priorytet(Token.top()) < 3) {  
                        Token.Dodaj(oper);
                    }
                    else if (Priorytet(Token.top()) == 3) {
                        Token.Dodaj(oper);
                    }
                    else {  
                        while (!Token.isEmpty() && Priorytet(Token.top()) < 4 && Priorytet(Token.top()) > 1) { // 
                            Wyjscie.Dodaj(Token.top());
                            Token.Zdejmij();
                        }
                        Token.Dodaj(oper);
                    }
                }
            }
            else if (x == 'I') {        // IF
                cin.get(znak[0]);
                char* operDwa = new char[Data_Size];
                operDwa[0] = x;
                operDwa[1] = znak[0];
                operDwa[2] = '\0';

                if (Token.isEmpty() == true) {
                    Token.Dodaj(operDwa);
                }
                else {
                    if (Priorytet(Token.top()) < 3) {   
                        Token.Dodaj(operDwa);
                    }
                    else if (Priorytet(Token.top()) == 3) {
                        Token.Dodaj(operDwa);
                    }
                    else {  
                        while (!Token.isEmpty() && Priorytet(Token.top()) < 4 && Priorytet(Token.top()) > 1) { // 
                            Wyjscie.Dodaj(Token.top());
                            Token.Zdejmij();
                        }
                        Token.Dodaj(operDwa);
                    }
                }
                delete[] operDwa;
            }
            else if (x == 'M') {

                cin.get(znak[1]);
                cin.get(znak[2]);
                char* operTrzy = new char[Data_Size];
                operTrzy[0] = x;
                operTrzy[1] = znak[1];
                operTrzy[2] = znak[2];
                operTrzy[3] = 'i';          /// mozliwe na 1
                operTrzy[4] = '\0';


                if (Token.isEmpty() == true) {   // MAX / MIN
                    Token.Dodaj(operTrzy);
                }
                else {
                    if (Priorytet(Token.top()) < 3) {   
                        Token.Dodaj(operTrzy);
                    }
                    else if (Priorytet(Token.top()) == 3) {
                        Token.Dodaj(operTrzy);
                    }
                    else {  
                        while (!Token.isEmpty() && Priorytet(Token.top()) < 4 && Priorytet(Token.top()) > 1) { // 
                            Wyjscie.Dodaj(Token.top());
                            Token.Zdejmij();
                        }
                        Token.Dodaj(operTrzy);
                    }
                }
                delete[] operTrzy;
            }
            else if (x == '*' || x == '/') {

                if (Token.isEmpty() == true) {
                    Token.Dodaj(oper);
                }
                else {
                    if (Priorytet(Token.top()) < 2) {   
                        Token.Dodaj(oper);
                    }
                    else {  
                        while (!Token.isEmpty() && Priorytet(Token.top()) < 4 && Priorytet(Token.top()) > 1) { // 
                            Wyjscie.Dodaj(Token.top());
                            Token.Zdejmij();
                        }
                        Token.Dodaj(oper);
                    }
                }
            }
            else if (x == '+' || x == '-') {
                if (Token.isEmpty() == true) {
                    Token.Dodaj(oper);
                }
                else {
                    while (!Token.isEmpty() && Priorytet(Token.top()) < 4) {
                        Wyjscie.Dodaj(Token.top());
                        Token.Zdejmij();
                    }
                    Token.Dodaj(oper);
                }
            }
            else if (x >= '0' && x <= '9') {
                Liczba(x, Wyjscie);
            }
            else if (x == '.') {
                while (!Token.isEmpty()) {      
                    Wyjscie.Dodaj(Token.top());
                    Token.Zdejmij();
                }
            }
            if (x == ',') {
                while (Token.top()[0] != '(') {      
                    Wyjscie.Dodaj(Token.top());
                    Token.Zdejmij();
                }
                Licznik.Zwieksz();
            }
            delete[] oper;
        }

        cout << endl;
        Wyjscie.Odwroc();
        Wyjscie.WypiszStos();

        Wynik(Stos, Wyjscie);


        while (!Stos.isEmpty()) {
            Stos.Zdejmij();
        }
        while (!Wyjscie.isEmpty()) {
            Wyjscie.Zdejmij();
        }
        cout << endl;
    }
    return 0;
}