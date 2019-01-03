#include<iostream>
using namespace std;

class Add {
public:
    Add(){}
    virtual ~Add() {}
    virtual int add(int arg1, int arg2) {return 0;}
};

template <typename M>
class AddBase : public Add {
    public:
        AddBase() {}
        virtual ~AddBase() {}
        M add(M arg1, M arg2);
};

template <typename M>
M AddBase<M>::add(M arg1, M arg2){
    return arg1 + arg2;
}

class AddDerive : public AddBase<int>{
public:
    AddDerive() = default;
    virtual ~AddDerive() = default;
};



int main()
{
    AddBase<int> addInst;
    AddBase<double> addDouble;
    std::cout<<addInst.add(3,5)<<std::endl;
    std::cout<<addDouble.add(4.5, 9.7)<<std::endl;
    AddDerive addDerive;
    std::cout<<addDerive.add(2,8)<<std::endl;
    //Add addBase = static_cast<Add >(addDerive);
    Add * addBase = &addDerive;
    std::cout<<addBase->add(1,1)<<std::endl;
    return 0;
}
