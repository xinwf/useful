#include "exc_mean.h"

#include <iostream>
#include <cmath>

double hmean(double a, double b);
double gmean(double a, double b);

int main()
{
    using std::cout;
    using std::cin;
    using std::endl;

    double x, y, z;
    
    cout << "Enter two numbers: ";
    while (cin >> x >> y) {
        try {
            z = hmean(x, y);
            cout << "Harmonic mean of " << x << " and " << y
                << " is " << z << endl;
            cout << "Geometric mean of " << x << " and " << y
                << " is " << gmean(x,y) << endl;
            cout << "Enter next set of numbers <q to quit>: ";
        } catch(BadHmean &bh) {
            bh.Mesg();
            cout << "Try again.\n";
            continue;
        } catch(BadGmean &bg) {
            bg.Mesg();
            cout << "Values used: " << bg.v1_ << ", " << bg.v2_ << endl;
            cout << "Sorry, you don't get to play any more.\n";
            break;
        }
        
    }
    cout << "Bye!\n";
    return 0;
}

double hmean(double a, double b)
{
    if (a == -b)
        throw BadHmean(a, b);
    return 2.0 * a * b / (a + b);
}

double gmean(double a, double b)
{
    if (a < 0 || b < 0)
        throw BadGmean(a, b);
    return std::sqrt(a * b);
}