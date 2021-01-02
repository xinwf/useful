#include "base.h"
#include "derived.h"

#include <iostream>

int main()
{
    using namespace std;
    /* The unused variable x is used to observe the difference of built-in type's
     * initialization when it is in a dependant and user-defined form seperately.
     * 
     */
    int x;
    cout << "x: " << x << "\n";
    Customer cust1("Lu Lina1");
    Customer cust2("Lu Lina2", "20200102");
    Customer cust3(cust1);
    Customer cust4(cust2);
    Customer cust5("Lu Lina3");
    cust5 = cust2;

    cust1.OutputData();
    cust2.OutputData();
    cust3.OutputData();
    cust4.OutputData();
    cust5.OutputData();


    PriorityCustomer priCust1;
    PriorityCustomer priCust2(1);
    PriorityCustomer priCust3(priCust1);
    PriorityCustomer priCust4(priCust2);
    PriorityCustomer priCust5;
    priCust5 = priCust2;

    priCust1.OutputData();
    priCust2.OutputData();
    priCust3.OutputData();
    priCust4.OutputData();
    priCust5.OutputData();
    
    return 0;
}