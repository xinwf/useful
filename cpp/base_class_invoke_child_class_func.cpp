#include <stdio.h>
 
template <typename T>
class A
{
public:
    A()
    {
        T *pT = (T *) this;
        pT->speek();
    }
};
 
class B    :    public A<B>
{
public:
    void speek()
    {
        printf("OK\n");
    }
};
 
int main()
{
    B b;
    return 0;
}
