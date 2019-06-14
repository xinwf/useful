// Example program
#include <iostream>
#include <string>
#include <vector>

int main()
{
int *pb = new int[5];
*(pb+1) = 1;
*(pb+2) = 2;
*(pb+3) = 3;
*(pb+4) = 4;
// int *pb_bak = pb;
std::cout << *pb << std::endl;
std::cout << pb << std::endl;
// *pb++;
// std::cout << *pb << std::endl;
// std::cout << *pb_bak << std::endl;
// std::cout << *(pb_bak+1) << std::endl;
// std::cout << pb << ",  " << pb_bak << std::endl;

// std::cout << *pb <<" " << pb << std::endl;
// std::cout << *(pb++) <<" " << pb  << std::endl;
std::cout << *pb++ <<" " << pb  << std::endl;
// std::cout << *pb << std::endl;
// std::cout << *(pb++) << std::endl;
// std::cout << *pb << std::endl;
// std::cout << *(pb++) << std::endl;
// std::cout << *pb << std::endl;

// int i = 5;
// std::cout << 2 * (i++) << std::endl;
// std::cout << 2 * i << std::endl;

// int j = 1;
// std::cout << (j-- > 0) << std::endl;
// int m=2,n=3;
// std::cout << 2 * (m++ + n++) << std::endl;
return 0;
}