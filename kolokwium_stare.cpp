#include <iostream>
#include <fstream>


using namespace std;

class K1{
    string * p1;

public:

    K1():p1(new string[2]){
        p1[0] = "Pusty";
        p1[1] = "Pusty";
    }
    K1(const string& s1, const string& s2): p1(new string[2]){
        p1[0] = s1;
        p1[1] = s2;
    }
    K1(const K1& k): p1(new string[2]){
        p1[0] = k.p1[0];
        p1[1] = k.p1[1];
    }

    const string& p(int i) const{
        return p1[i];
    }

    friend class K2;

};

class K2{
    K1 w1;
    double w2;

public:

    K2(): w1(K1()), w2(0){}
    K2(const string& s1, const string& s2, const double& d): w1(s1,s2), w2(d){}
    K2(const K2& k): w1(), w2(k.w2){
        w1.p1[0] = k.w1.p1[0];
        w1.p1[1] = k.w1.p1[1];
    }

    K1& getW1(){
        return w1;
    }

    double getW2(){
        return w2;
    } 

    void wczytaj(ifstream& file){

        string buf;
        getline(file, buf, ' ');
        //cout << "pierwsz buf " << buf << endl;

        w1.p1[0] = buf;

        getline(file, buf, ' ');
        //cout << "drugi buf " << buf << endl;

        w1.p1[1] = buf;

        getline(file, buf, '\n');
        //cout << "trzeci buf " << buf << endl;

        w2 = stod(buf);

    }

    void operator+=(const double& i){
        w2+=i;
    }

    friend ostream& operator<<(ostream&, const K2&);
    friend K2& operator-(const K2&, const double);
    friend K2 operator+(K2&, const string&);
    friend K2 operator+(const string&, K2&);
};

K2 operator+(K2& k, const string& s){
    return K2(k.w1.p(0), k.w1.p(1) + s, k.w2);
}

K2 operator+(const string& s, K2& k){
    return K2(s + k.w1.p(0), k.w1.p(1), k.w2);
}

ostream& operator<<(ostream& out, const K2& k){
    out << k.w1.p(0) << " " << k.w1.p(1) << " " << k.w2 << endl;

    return out;
}

K2 operator-(K2& k, const double d){
    return K2(k.getW1().p(0), k.getW1().p(1), k.getW2() - d);
}

int main(int argc, char* argv[]){

    K2 ob1, ob2;
    const K2 * wsk1 = new K2("kawa", "z mlekiem", 4.50);
    const K2 ob3(*wsk1);
    delete wsk1;
    wsk1=0;

    const K2 *wsk2 = new K2(ob3);
    ob2 = *wsk2;
    cout << ob1 << *wsk2;
    delete wsk2;
    wsk2 = 0;

    cout << ob2;
    cout << ob2-1.25;
    cout << "***** 3 *****\n" << endl;

    K2 tab[4];

    //...wczytanie z pliku

    ifstream file(argv[1]);

    for(int i=0; i<4; i++){
        tab[i].wczytaj(file);
    }

    for(int i=0; i<4; i++){
        tab[i]+=1;
        cout << tab[i];
    }
    cout << "***** 4 *****\n" << endl;

    tab[1] = tab[1] + " with sugar";
    tab[3] = "Hot " + tab[3];

    for(int i=0; i<4; ++i){
        cout << tab[i];
    }

    cout << "**** 5 ****" << endl;
    return 0;
}