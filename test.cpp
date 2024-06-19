#include<iostream>
using namespace std;

class date
{
    private:
        int year, month, day;
    public:
    date() {cout << "const";}
    date(int y, int m, int d): year(y), month(m), day(d){}
    int test;
    virtual void say() = 0;
};

class hour : public date
{
    public:
        void say(){cout << 2;}
};

int main()
{
    hour e;
    date* h = &e;
    h->say();
}