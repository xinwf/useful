#include <iostream>

class BadHmean
{
public:
    BadHmean(double a = 0, double b = 0) : v1_(a), v2_(b) {}
    void Mesg();
private:
    double v1_, v2_;
};

inline void BadHmean::Mesg()
{
    std::cout << "hmean(" << v1_ << ", " << v2_ << "): "
              << "invalid arguments: a = -b\n";
}

class BadGmean
{
public:
    double v1_, v2_;
    BadGmean(double a = 0, double b = 0) : v1_(a), v2_(b) {}
    const char * Mesg();
};

inline const char * BadGmean::Mesg()
{
    return "gmean() arguments should be >= 0\n";
}