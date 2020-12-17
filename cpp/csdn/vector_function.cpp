#include <iostream>
#include <vector>

int main()
{
    using namespace std;

    vector<int> intv1;
    vector<int> intv2(5);
    vector<int> intv3;
    vector<int> intv4;
    /*
     * resize function has applied 10 int spaces in memory, and initilizing those elements with 0,
     * after resize, every element can be invoked with index function.
     * 
     * reserve function also applies 10 int spaces in memory, but those memory was not initilized and 
     * which can't be invoked with index function validly, even you can do that. This is due to index
     * operation [] doesn't do boundary check for efficiency.
     */
    intv3.resize(10);
    intv4.reserve(10);
    int *pi = intv4.data();
    intv4[3] = 4;
    // intv4.at(2) = 4;
    cout << "pi: " << pi << ", pi+3: " << pi+3 << ", intv4[0]: " << &intv4[0] << ", intv4[3]: " << &intv4[3] << "\n";
    cout << "*pi: " << *pi << ", pi+3: " << *(pi+3) << ", intv4[3]: " << intv4[3] << "\n";

    cout << "intv1 size: " << intv1.size() << ", capacity: " << intv1.capacity() << ", addr: " << &intv1 << ", data addr: "<< intv1.data() << "\n";
    cout << "intv2 size: " << intv2.size() << ", capacity: " << intv2.capacity() << ", addr: " << &intv2 << ", data addr: "<< intv2.data() <<  "\n";
    cout << "intv3 size: " << intv3.size() << ", capacity: " << intv3.capacity() << ", addr: " << &intv3 << ", data addr: "<< intv3.data() <<  "\n";
    cout << "intv4 size: " << intv4.size() << ", capacity: " << intv4.capacity() << ", addr: " << &intv4 << ", data addr: "<< intv4.data() <<  "\n";
    intv3.resize(5);
    intv4.reserve(5);
    cout << "intv3 size: " << intv3.size() << ", capacity: " << intv3.capacity() << ", addr: " << &intv3 << ", data addr: "<< intv3.data() <<  "\n";
    cout << "intv4 size: " << intv4.size() << ", capacity: " << intv4.capacity() << ", addr: " << &intv4 << ", data addr: "<< intv4.data() <<  "\n";
    intv4.reserve(15);
    cout << "intv4 size: " << intv4.size() << ", capacity: " << intv4.capacity() << ", addr: " << &intv4 << ", data addr: "<< intv4.data() <<  "\n";
    cout << "\n";

    intv1.push_back(1);
    cout << "intv1 size: " << intv1.size() << ", capacity: " << intv1.capacity() << ", addr: " << &intv1 << ", data addr: "<< intv1.data() << "\n";
    intv1.push_back(2);
    cout << "intv1 size: " << intv1.size() << ", capacity: " << intv1.capacity() << ", addr: " << &intv1 << ", data addr: "<< intv1.data() << "\n";
    intv1.push_back(2);
    cout << "intv1 size: " << intv1.size() << ", capacity: " << intv1.capacity() << ", addr: " << &intv1 << ", data addr: "<< intv1.data() << "\n";
    intv1.push_back(2);
    cout << "intv1 size: " << intv1.size() << ", capacity: " << intv1.capacity() << ", addr: " << &intv1 << ", data addr: "<< intv1.data() << "\n";
    intv1.push_back(2);
    cout << "intv1 size: " << intv1.size() << ", capacity: " << intv1.capacity() << ", addr: " << &intv1 << ", data addr: "<< intv1.data() << "\n";

    cout << "\n";

    intv2.push_back(1);
    cout << "intv2 size: " << intv2.size() << ", capacity: " << intv2.capacity() << ", addr: " << &intv2 << ", data addr: "<< intv2.data() <<  "\n";
    intv2.push_back(1);
    cout << "intv2 size: " << intv2.size() << ", capacity: " << intv2.capacity() << ", addr: " << &intv2 << ", data addr: "<< intv2.data() <<  "\n";
    intv2.push_back(1);
    intv2.push_back(1);
    intv2.push_back(1);
    cout << "intv2 size: " << intv2.size() << ", capacity: " << intv2.capacity() << ", addr: " << &intv2 << ", data addr: "<< intv2.data() <<  "\n";
    intv2.push_back(1);
    cout << "intv2 size: " << intv2.size() << ", capacity: " << intv2.capacity() << ", addr: " << &intv2 << ", data addr: "<< intv2.data() <<  "\n";


    return 0;
}