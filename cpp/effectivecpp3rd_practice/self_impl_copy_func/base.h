#ifndef SELF_IMPL_COPY_FUNC_BASE_H_
#define SELF_IMPL_COPY_FUNC_BASE_H_

#include <string>

void logCall(const std::string& funcName);

class Customer
{
private:
    std::string name_;
    // assume this member is added subsequently.
    std::string last_transaction_;
public:
    Customer() = default; // if we omit this default constructor, we must initialize the
                          // base class explicitly in derived class's constructor.
    Customer(const std::string& name, const std::string& last_transaction = "00000000");
    Customer(const Customer& rhs);
    Customer& operator=(const Customer& rhs);
    void OutputData() const;
};



#endif