#ifndef SELF_IMPL_COPY_FUNC_DERIVED_H_
#define SELF_IMPL_COPY_FUNC_DERIVED_H_

#include "base.h"

class PriorityCustomer : public Customer
{
private:
    int priority_;
public:
    PriorityCustomer() = default;
    PriorityCustomer(int priority);
    PriorityCustomer(const PriorityCustomer& rhs);
    PriorityCustomer& operator=(const PriorityCustomer& rhs);
    void OutputData() const;
};

#endif