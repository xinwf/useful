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
public:
    Book(int i):m_i(i){std::cout << "Book series " << i << "\n";}
    ~Book(){std::cout << "Book series " << m_i << " destroied\n";}
};


#endif