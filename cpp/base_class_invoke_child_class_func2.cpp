#include <stdio.h>
#include <iostream>
using namespace std;
 
class B;
 
class A
{
private:
    B* b;
public:
    A(){};
    A(B* b);
    void fun();
};
 
class B : public A
{
public:
    B(){};
    void speek()
    {
        printf("OK\n");
    }
};
 
A::A(B* b)
{
    this->b = b;
}
 
void A::fun()
{
    b->speek();
}
 
int main()
{
    A a(new B);
    a.fun();
 
    return 0;
}