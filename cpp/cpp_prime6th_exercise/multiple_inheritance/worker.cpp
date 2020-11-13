#include "worker.h"

#include <iostream>

using std::cout;
using std::endl;
using std::cin;

// Worker methods
Worker::~Worker() {}

void Worker::Set()
{
    cout << "Enter worker's name: ";
    getline(cin, full_name_);
    cout << "Enter worker's ID: ";
    cin >> id_;
    while (cin.get() != '\n') continue;
}

void Worker::Show() const
{
    cout << "Name: " << full_name_ << "\n";
    cout << "Employee ID: " << id_ << "\n";
}

// Waiter methods
void Waiter::Set()
{
    Worker::Set();
    cout << "Enter waiter's panache rating: ";
    cin >> panache_;
    while (cin.get() != '\n') continue;
}

void Waiter::Show() const
{
    cout << "Category: waiter\n";
    Worker::Show();
    cout << "Panache rating: " << panache_ << "\n";
}

// Singer methods
char *Singer::pv_[] = {"other", "alto", "contrallo", "soprano", "bass", "baritone", "tenor"};

void Singer::Set()
{
    Worker::Set();
    cout << "Enter number for singer's vocal range: \n";
    int i;
    for (i = 0; i < Vtypes; ++i){
        cout << i << ": " << pv_[i] << "    ";
        if (i%4 == 3) cout << endl;
    }
    if (i%4 != 0) cout << endl;
    while (cin >> voice_ && (voice_ < 0 || voice_ >= Vtypes))
        cout << "Please enter a value >= 0 and < " << Vtypes << endl;

    while (cin.get() != '\n') continue;
}

void Singer::Show() const
{
    cout << "Category: singer\n";
    Worker::Show();
    cout << "Vocal range: " << pv_[voice_] << endl;
}