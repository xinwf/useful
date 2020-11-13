#include "workermi.h"

#include <iostream>

using std::cout;
using std::endl;
using std::cin;

// Worker methods
Worker::~Worker() {}

void Worker::Data() const
{
    cout << "Name: " << full_name_ << endl;
    cout << "Employee ID: " << id_ << endl;
}

void Worker::Get()
{
    getline(cin, full_name_);
    cout << "Enter worker's ID: ";
    cin >> id_;
    while (cin.get() != '\n') continue;
}

// Waiter methods
void Waiter::Set()
{
    cout << "Enter waiter's name: ";
    Worker::Get();
    Get();
}

void Waiter::Show() const
{
    cout << "Category: waiter\n";
    Worker::Data();
    Data();
}

void Waiter::Data() const
{
    cout << "Panache rating: " << panache_ << "\n";
}

void Waiter::Get()
{
    cout << "Enter waiter's panache rating: ";
    cin >> panache_;
    while (cin.get() != '\n') continue;
}

// Singer methods
char *Singer::pv_[] = {"other", "alto", "contrallo", "soprano", "bass", "baritone", "tenor"};

void Singer::Set()
{
    cout << "Enter singer's name: ";
    Worker::Get();
    Get();
}

void Singer::Show() const
{
    cout << "Category: singer\n";
    Worker::Data();
    Data();
}

void Singer::Data() const
{
    cout << "Vocal range: " << pv_[voice_] << endl;
}

void Singer::Get()
{
    cout << "Enter number for singer's vocal range: \n";
    int i;
    for (i = 0; i < Vtypes; ++i){
        cout << i << ": " << pv_[i] << "    ";
        if (i%4 == 3) cout << endl;
    }
    if (i%4 != 0) cout << endl;
    cin >> voice_;
    while (cin.get() != '\n') continue;
}

// SingingWaiter methods
void SingingWaiter::Data() const
{
    Singer::Data();
    Waiter::Data();
}

void SingingWaiter::Get()
{
    Waiter::Get();
    Singer::Get();
}

void SingingWaiter::Set()
{
    cout << "Enter singing waiter's name: ";
    Worker::Get();
    Get();
}

void SingingWaiter::Show() const
{
    cout << "Category: singing waiter\n";
    Worker::Data();
    Data();
}