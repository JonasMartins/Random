#include <iostream>

using namespace std;

int main ()
{

    string name = "Cassandra";
    string &cassie = name;
    string &cassey = name;
    string &sandra = name;

    cout << name << " " << &name << endl;
    cout << cassie << " " << &cassie << endl;
    cout << cassey << " " << &cassey << endl;
    cout << sandra << " " << &sandra << endl;




    return 0;
}

