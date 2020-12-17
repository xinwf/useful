#include "singleton_template_thread_safe.h"
#include <iostream>
#include <thread>

int main()
{
    using namespace std;
    Book *b1 = SingletonTTS<Book>::Instance();

    return 0;
}