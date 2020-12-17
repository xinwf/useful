#include "somedef.h"
#include <iostream>
#include <functional>

double dob(double x) { return 2.0*x; }
double square(double x) { return x*x; }

int main()
{
    using std::cout;
    using std::endl;
    using std::function;

    double y = 1.21;

    // use_f is instantiated 5 times in this invoke method,
    // first 2 invocations have the same function features
    cout << "Function pointer dob:\n";
    cout << "   " << use_f(y, dob) << "\n";
    cout << "Function pointer square:\n";
    cout << "   " << use_f(y, square) << "\n";
    cout << "Function object Fp:\n";
    cout << "   " << use_f(y, Fp(5.0)) << "\n";
    cout << "Function object Fq:\n";
    cout << "   " << use_f(y, Fq(5.0)) << "\n";
    cout << "Lamada expression 1:\n";
    cout << "   " << use_f(y, [](double u) {return u*u;}) << "\n";
    cout << "Lamada expression 2:\n";
    cout << "   " << use_f(y, [](double u) {return u+u/2.0;}) << "\n";

    // all following invocation methods of use_* only instantiated once
    // due to wrapper with std::function
    
    // function<double(double)> ef1 = dob;
    // function<double(double)> ef2 = square;
    // function<double(double)> ef3 = Fp(10.0);
    // function<double(double)> ef4 = Fq(10.0);
    // function<double(double)> ef5 = [](double u) {return u*u;};
    // function<double(double)> ef6 = [](double u) {return u+u/2.0;};
    // cout << "Function pointer dob:\n";
    // cout << "   " << use_g(y, ef1) << "\n";
    // cout << "Function pointer square:\n";
    // cout << "   " << use_g(y, ef2) << "\n";
    // cout << "Function object Fp:\n";
    // cout << "   " << use_g(y, ef3) << "\n";
    // cout << "Function object Fq:\n";
    // cout << "   " << use_g(y, ef4) << "\n";
    // cout << "Lamada expression 1:\n";
    // cout << "   " << use_g(y, ef5) << "\n";
    // cout << "Lamada expression 2:\n";
    // cout << "   " << use_g(y, ef6) << "\n";

    typedef function<double(double)> fdd;
    cout << "Function pointer dob:\n";
    cout << "   " << use_g(y, fdd(dob)) << "\n";
    cout << "Function pointer square:\n";
    cout << "   " << use_g(y, fdd(square)) << "\n";
    cout << "Function object Fp:\n";
    cout << "   " << use_g(y, fdd(Fp(10.0))) << "\n";
    cout << "Function object Fq:\n";
    cout << "   " << use_g(y, fdd(Fq(10.0))) << "\n";
    cout << "Lamada expression 1:\n";
    cout << "   " << use_g(y, fdd([](double u) {return u*u;})) << "\n";
    cout << "Lamada expression 2:\n";
    cout << "   " << use_g(y, fdd([](double u) {return u+u/2.0;})) << "\n";

    cout << "Function pointer dob:\n";
    cout << "   " << use_h<double>(y, dob) << "\n";
    cout << "Function pointer square:\n";
    cout << "   " << use_h<double>(y, square) << "\n";
    cout << "Function object Fp:\n";
    cout << "   " << use_h<double>(y, Fp(10.0)) << "\n";
    cout << "Function object Fq:\n";
    cout << "   " << use_h<double>(y, Fq(10.0)) << "\n";
    cout << "Lamada expression 1:\n";
    cout << "   " << use_h<double>(y, [](double u) {return u*u;}) << "\n";
    cout << "Lamada expression 2:\n";
    cout << "   " << use_h<double>(y, [](double u) {return u+u/2.0;}) << "\n";

    return 0;
}