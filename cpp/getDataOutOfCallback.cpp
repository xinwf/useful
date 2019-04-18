#include <iostream>
#include <functional>

using namespace std;
using namespace std::placeholders;
 
typedef std::function<void(double)> Fun;//typedef一个函数指针

class GetDataOutOfCallback{
public:
    double data_from_cb;

    void caller(double a, Fun fp){
        fp(a);
    }

    void func(double a){
        std::cout << __FUNCTION__ <<":" << a <<"\n";
        data_from_cb = a;
    }

    void bind()
    {
        Fun fun = std::bind(&GetDataOutOfCallback::func, this, _1);
        caller(3.7, fun);
    }

    void print_var(){std::cout << __FUNCTION__ <<" : " << data_from_cb << "\n";}
};

int main(){
    GetDataOutOfCallback getDataOutOfCallback;
    getDataOutOfCallback.bind();
    getDataOutOfCallback.print_var();
    return 0;
}
