/* The derived class PriorityCustomer is used to clarify the phenominon that data would
 * be copied partly if we implement copy functions by ourself, this defect also can be
 * delivered to derived class.
 */ 

#include "derived.h"

#include <iostream>

PriorityCustomer::PriorityCustomer(int priority) : priority_(priority) {}

PriorityCustomer::PriorityCustomer(const PriorityCustomer& rhs) :
    Customer(rhs), // if the base class doesn't provide a default constructor,
                   // this member initialization list can't omit the initialization
                   // of the base class, otherwise, it would cause compilation error.
    priority_(rhs.priority_){
        logCall("PriorityCustomer copy constructor");
}

PriorityCustomer& PriorityCustomer::operator=(const PriorityCustomer& rhs){
    logCall("PriorityCustomer copy assignment");
    priority_ = rhs.priority_;
}

void PriorityCustomer::OutputData() const
{
    Customer::OutputData();
    std::cout << "priority_: " << priority_ << "\n";
}