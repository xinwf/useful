#include <iostream>

class Base{
    public:
        Base() {}

        virtual float add(float a, float b, float c = 1.0){ return a + b; }
};

class Derived: public Base{
    public:
        Derived():Base(){}

        float add(float a, float b, float c){ std::cout << c << std::endl; return a * b; }
};

int main(){
    Base * base = new Derived();
    std::cout << base->add(2, 3) << std::endl;
    return 0;
}