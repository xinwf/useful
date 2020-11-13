#ifndef WORKERMI_H_
#define WORKERMI_H_

#include <string>

class Worker
{
public:
    Worker() : full_name_("no one"), id_(0L){}
    Worker(const std::string &s, long n)
            : full_name_(s), id_(n) {}
    virtual ~Worker() = 0;
    virtual void Set() = 0;
    virtual void Show() const = 0;
protected:
    virtual void Data() const;
    virtual void Get();
private:
    /* data */
    std::string full_name_;
    long id_;
};


class Waiter : virtual public Worker
{
public:
    Waiter() : Worker(), panache_(0) {}
    Waiter(const std::string &s, long n, int p = 0)
            : Worker(s, n), panache_(p) {}
    Waiter(const Worker &wk, int p = 0) : Worker(wk), panache_(p) {}
    virtual void Set();
    virtual void Show() const;
protected:
    virtual void Data() const;
    virtual void Get();
private:
    int panache_;
};

class Singer : virtual public Worker
{
public:
    Singer(/* args */) : Worker(), voice_(other) {}
    Singer(const std::string &s, long n, int v = other) : Worker(s, n), voice_(v) {}
    Singer(const Worker &wk, int v = other) : Worker(wk), voice_(v) {}
    virtual void Set();
    virtual void Show() const;
protected:
    enum {other, alto, contrallo, soprano, bass, baritone, tenor};
    enum {Vtypes = 7};
    virtual void Data() const;
    virtual void Get();
private:
    /* data */
    static char *pv_[Vtypes];
    int voice_;
};

// multiple inheritance
class SingingWaiter : public Singer, public Waiter
{
public:
    SingingWaiter() {}
    SingingWaiter(const std::string &s, long n, int p = 0, int v = other)
            : Worker(s,n), Waiter(s, n, p), Singer(s, n, v) {}
    SingingWaiter(const Worker &wk, int p = 0, int v = other)
            : Worker(wk), Waiter(wk, p), Singer(wk, v) {}
    SingingWaiter(const Waiter &wt, int v = other)
            : Worker(wt), Waiter(wt), Singer(wt, v) {}
    SingingWaiter(const Singer &sg, int p = 0)
            : Worker(sg), Waiter(sg, p), Singer(sg) {}
    virtual void Set();
    virtual void Show() const;

protected:
    virtual void Data() const;
    virtual void Get();
};


#endif