#include <iostream>
#include <assert.h>
using namespace std;

//使用局部静态变量实现的单例类
//注意这是类，而不是模板，它实现了下面Singleton模板的create方法
class LocalStaticInstance {
protected:
    template <class T>
    static void create(T*& ptr)
    {
        cout << "Using LocalStaticInstance ...\n";
        static T instance;
        ptr = &instance;
    }
};

//释放器 用于释放在堆上分配的单例
template <class T>
class Destroyer
{
    T* doomed;
public:
    Destroyer(T* q) : doomed(q)
    {
        assert(doomed);
    }

    ~Destroyer();
};
//在类外实现的析构函数，注意析构函数开头要写成Destroyer<T>形式
//因为Destroyer<T>才是一个真正的类型
template <class T>
Destroyer<T>::~Destroyer()
{
    try
    {
        if(doomed)
            delete doomed;
    } catch(...) { }

    doomed = 0;
}

//使用指针实现，懒惰初始化单例类
class LazyInstance
{
protected:
    template <class T>
    static void create(T*& ptr)
    {
        cout << "Using LazyInstance ...\n";
        ptr = new T;
        static Destroyer<T> destroyer(ptr);
    }

};

//Singleton类对外提供一致接口，默认调用LazyInstance
template <class T, class InstancePolicy=LazyInstance>
class Singleton : private InstancePolicy
{
public:
    static T* instance();
};

//在类声明之外定义instance接口
template <class T, class InstancePolicy>
T* Singleton<T, InstancePolicy>::instance()
{
    static T* ptr = 0;
    if(!ptr)
    {
        InstancePolicy::create(ptr);
    }

    return const_cast<T*>(ptr);
}

//使用局部静态单例类，需要显式指定
class LocalStaticInstanceInt: public Singleton<LocalStaticInstanceInt, LocalStaticInstance>
{
public:
    virtual ~LocalStaticInstanceInt()
    {
        cout << "destory LocalStaticInstanceInt" << endl;
    }

    int getValue() const {return value;}
    void setValue(int val) {value = val;}
    friend class LocalStaticInstance;
    friend class LazyInstance;
private:
    LocalStaticInstanceInt():value(0)
    {
        cout << "create LocalStaticInstanceInt" << endl;
    }
    int value;
};

//使用懒惰初始化单例类  默认
class LocalStaticInstanceString: public Singleton<LocalStaticInstanceString>
{
public:
    ~LocalStaticInstanceString()
    {
        cout << "destory LocalStaticInstanceString" << endl;
    }

    string getValue() const {return value;}
    void setValue(string val) {value = val;}

    friend class LocalStaticInstance;
    friend class LazyInstance;
private:
    LocalStaticInstanceString():value("hello")
    {
        cout << "create LocalStaticInstanceString" << endl;
    }
    string value;
};

int main()
{
    {
        LocalStaticInstanceInt* lsi1 = Singleton<LocalStaticInstanceInt>::instance();
        LocalStaticInstanceInt* lsi2 = Singleton<LocalStaticInstanceInt, LocalStaticInstance>::instance();
        cout << "lsi1.value = "<< lsi1->getValue() << "  lsi2.value = " << lsi2->getValue() << endl;

        lsi1->setValue(5);
        cout << "lsi1.value = "<< lsi1->getValue() << "  lsi2.value = " << lsi2->getValue() << endl;
    }

    {
        LocalStaticInstanceString* lss1 = Singleton<LocalStaticInstanceString>::instance();
        LocalStaticInstanceString* lss2 = Singleton<LocalStaticInstanceString>::instance();
        cout << "lsi1.value = "<< lss1->getValue() << "  lsi2.value = " << lss2->getValue() << endl;

        lss1->setValue("world");
        cout << "lsi1.value = "<< lss1->getValue() << "  lsi2.value = " << lss2->getValue() << endl;
    }
}