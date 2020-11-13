#ifndef WORKER_H_
#define WORKER_H_

#include <string>

class Worker
{
public:
    Worker(/* args */) : full_name_("no one"), id_(0L){}
    Worker(const std::string &s, long n)
            : full_name_(s), id_(n) {}
    virtual ~Worker() = 0;
    virtual void Set();
    virtual void Show() const;
private:
    /* data */
    std::string full_name_;
    long id_;
};

class Waiter : public Worker
{
public:
    Waiter(/* args */) : Worker(), panache_(0) {}
    Waiter(const std::string &s, long n, int p = 0)
            : Worker(s, n), panache_(p) {}
    Waiter(const Worker &wk, int p = 0) : Worker(wk), panache_(p) {}
    virtual void Set();
    virtual void Show() const;
private:
    int panache_;
};

class Singer : public Worker
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
private:
    /* data */
    static char *pv_[Vtypes];
    int voice_;
};

#endif