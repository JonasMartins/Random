#include <iostream>

using namespace std;

void setValue(int&);

int main ()
{
    int a;

    setValue(a);

    cout << "Variable a is equal to: " << a;

    return 0;
}

void setValue(int &variableToSet)
{
    cout << "Input the value: ";
    cin >> variableToSet;
}

