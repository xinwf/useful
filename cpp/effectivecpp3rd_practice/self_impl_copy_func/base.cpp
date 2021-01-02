/*The base class Customer is used to expound if you implement the copy functions by yourself,
  and then you add another data member(we assume this data member is last_transaction_
  in this case), but you forget to copy the new data, hence, your copy functions would only
  copy part data from the object being copied. What needs our attention is that the compiler
  won't give us any warning or error, therefore, we must be extremely cautious when we implement
  copy functions by ourself.
*/
#include "base.h"

#include <iostream>

void logCall(const std::string& funcName){
    std::cout << funcName << "\n";
}

Customer::Customer(const std::string& name, const std::string& last_transaction)
    : name_(name), last_transaction_(last_transaction)
{
    logCall("Customer constructor");
}

Customer::Customer(const Customer& rhs):name_(rhs.name_)
{
    logCall("Customer copy constructor");
}

Customer& Customer::operator=(const Customer& rhs){
    logCall("Customer copy assignment operator");
    name_ = rhs.name_;
}

void Customer::OutputData() const {
    std::cout << name_ << " : " << last_transaction_ << "\n";
}