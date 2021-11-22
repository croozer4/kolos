#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cmath>

using namespace std;

class K1{
    string * p1;

public:

    K1(): p1(new string("pusty")){}
    K1(const string& str): p1(new string(str)){}
    K1(const K1& k): p1(new string(*k.p1)){}

    const string& p() const{
        return *p1;
    }

    string& p(){
        return *p1;
    }
};

class K2{
    K1 txt[2];
    int w1;

public:

    K2(): txt(),w1(0){}
    K2(const string& s1, const string& s2, const int& i1):txt(),w1(i1){
        txt[0] = s1;
        txt[1] = s2;
    }
    K2(const K2& k):txt(k.txt), w1(k.w1){}

    const K2 operator+(const int& i) const{
        return K2(txt[0].p(), txt[1].p(), w1 + i);
    }

    void wczytaj(ifstream& file){

        string buf;
        getline(file,buf,' ');
        //cout << "pierwszy buf " << buf << endl;
        txt[0].p() = buf;

        getline(file,buf,' ');
        //cout << "drugi buf " << buf << endl;
        txt[1].p() = buf;

        getline(file,buf,'\n');
        //cout << "trzeci buf " << buf << endl;

        w1 = stoi(buf);
    }

    void operator+=(const int& i) {
        w1=w1+i;
    }

    friend ostream& operator<<(ostream&, const K2&);
    friend K2 operator+(K2&, const string&);
    friend K2 operator+(const string&, K2&);
};

K2 operator+(K2& k, const string& s){
    return K2(k.txt[0].p(), k.txt[1].p() + s, k.w1);
}

K2 operator+(const string& s, K2& k){
    return K2(k.txt[0].p(), s + k.txt[1].p(), k.w1);
}

ostream& operator<<(ostream& out, const K2& ob){
        out << ob.txt[0].p() << " " << ob.txt[1].p() << " " << ob.w1 << endl; 
        return out;
}


int main(int argc, char* argv[]){

    K2 ob1, ob2;
    const K2 * wsk1 = new K2("Ala", "Koala", 15);
    const K2 ob3(*wsk1);
    delete wsk1;
    wsk1 = 0;

    const K2 * wsk2 = new K2(ob3);
    ob2 = *wsk2;
    cout << ob1 << *wsk2;
    delete wsk2;
    wsk2 = 0;

    cout << ob2;
    cout << ob2 + 10;

    cout << "***** 3 *****\n" << endl;

    K2 tab[4];

    //.. odczyt danych z pliku data

    ifstream file(argv[1]);

    for(int i=0; i<4; i++){
        tab[i].wczytaj(file);
    }


     for(int i=0; i<4; ++i){
         tab[i]+=1;
         cout << tab[i];
     }

    cout << "***** 4 *****\n" << endl;

    tab[1] = tab[1] + " Kowalska";
    tab[3] = "Bocian " + tab[3];

    for(int i=0; i<4; ++i){
        cout << tab[i];
    }

    cout << "**** 5 ****" << endl;


    return 0;
}