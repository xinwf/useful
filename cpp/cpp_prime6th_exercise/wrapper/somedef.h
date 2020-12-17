#include <iostream>
#include <functional>

template <typename T, typename F>
T use_f(T v, F f)
{
    static int count1 = 0;
    ++count1;
    std::cout << "  use_f count1 = " << count1
              << ", &count1 = " << &count1 << "\n";
    return f(v);
}

template <typename T, typename F>
T use_g(T v, F f)
{
    static int count2 = 0;
    ++count2;
    std::cout << "  use_f count2 = " << count2
              << ", &count2 = " << &count2 << "\n";
    return f(v);
}

template <typename T>
T use_h(T v, std::function<T(T)> f)
{
    static int count3 = 0;
    ++count3;
    std::cout << "  use_f count3 = " << count3
              << ", &count3 = " << &count3 << "\n";
    return f(v);
}

class Fp
{
private:
    double z_;
public:
    Fp(double z = 1.0) : z_(z) {}
    double operator()(double p) { return z_ * p; }
};

class Fq
{
private:
    double z_;
public:
    Fq(double z = 1.0) : z_(z) {}
    double operator()(double p) { return z_ + p; }
};