#ifndef __SINGLETON_TEMPLATE_THREAD_SAFE_H__
#define __SINGLETON_TEMPLATE_THREAD_SAFE_H__
#include <iostream>
#include <mutex>

template <typename T>
class SingletonTTS
{
public:
    static T *Instance();
    static void Destroy();
    static T *HasInstance();

protected:
    SingletonTTS(){};
    virtual ~SingletonTTS(){};   

private:
    SingletonTTS(T &&){};
    SingletonTTS(const T &){};
    T& operator=(const T &){};

    static T *m_pInstance;
    static std::mutex m_mutex;
};

class Book //: public SingletonTTS<Book>
{
private:
    int m_i;
    std::string data;
public:
    Book(int i):m_i(i){
        data = std::to_string(i) + " hello world!";
        std::cout << "Book series " << i << " published.\n";
    }
    void Data() {std::cout << data << "  addr: " << &data << "\n"; }
    ~Book(){std::cout << "Book series " << m_i << " is destroied.\n\n";}
};

#include "singleton_template_thread_safe.tpp"

#endif