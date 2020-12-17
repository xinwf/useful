#include <iostream>
#include <memory>

double * pd0 = nullptr;
double * pd1 = nullptr;

void memory_leak()
{
    // std::cout << __FUNCTION__ << "\n";
    double * pd2 = new double(5);
    pd0 = pd2;
    std::cout << "pd2's addr: " << pd2 << ", value: " << *pd2 << ", pd0's addr: " << pd0 << ", value: " << *pd0  << "\n";
}

void no_memory_leak()
{
    // std::cout << __FUNCTION__ << "\n";
    std::unique_ptr<double> pd3(new double(6));
    pd1 = pd3.get();
    std::cout << "pd3's addr: " << &pd3 << ", value: " << *pd3 << ", pd1's addr: " << pd1 << ", value: " << *pd1 << "\n";
}

int main()
{
    memory_leak();
    no_memory_leak();
    // std::cout << __FUNCTION__ << "\n";
    std::cout << "pd0's addr: " << pd0 << ", value: " << *pd0 << "\n";
    std::cout << "pd1's addr: " << pd1 << ", value: " << *pd1 << "\n";
}
