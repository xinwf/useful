#include "singleton_template_thread_safe.h"
#include <iostream>
#include <thread>

int main()
{
    using namespace std;
    Book *b1 = SingletonTTS<Book>::Instance();
    Book *b2 = SingletonTTS<Book>::Instance();
    cout << "&b1: " << &b1 << ", b1 : " << b1 << "\n";
    cout << "&b2: " << &b2 << ", b2 : " << b2 << "\n";
    cout << "b1's data: " , b1->Data();
    cout << "b2's data: " , b2->Data();
    SingletonTTS<Book>::Destroy();
    SingletonTTS<Book>::HasInstance();
    cout << "b1's data: " , b1->Data();
    cout << "b2's data: " , b2->Data();

    Book *b3 = SingletonTTS<Book>::Instance();
    cout << "&b3: " << &b3 << ", b3 : " << b3 << ", sizeof b3: " << sizeof(*b3) << "\n";
    cout << "b3's data: " , b3->Data();
    delete b3;
    b3 = nullptr;
    // SingletonTTS<Book>::Destroy();
    cout << "&b3: " << &b3 << ", b3 : " << b3 << ", sizeof b3: " << sizeof(*b3) << "\n";
    SingletonTTS<Book>::HasInstance();

    Book *b4 = SingletonTTS<Book>::Instance();
    cout << "&b4: " << &b4 << ", b4 : " << b4 << ", sizeof b4: " << sizeof(*b4) << "\n";
    cout << "b4's data: " , b4->Data();

    return 0;
}