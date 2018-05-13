#include <iostream>

using namespace std;

void checkIfTheSame(int&, int&);

int main ()
{

    int a = 4;
    int b = 3;
    int c = a;
    int &d = a;

    checkIfTheSame(a, b);
    checkIfTheSame(a, c);
    checkIfTheSame(a, d);

    return 0;
}

void checkIfTheSame(int &firstVariable, int &secondVariable)
{
    if (firstVariable == secondVariable && &firstVariable == &secondVariable)
    {
        cout << "The variables are completely the same !";
    }
    else if (firstVariable == secondVariable && &firstVariable != &secondVariable)
    {   
		cout << firstVariable << " " << &firstVariable << endl;    
        cout << secondVariable << " " << &secondVariable << endl;
        cout << "The variables have got same values but they are different variables !" << endl;
    }
    else
    {
        cout << firstVariable << " " << &firstVariable << endl;
        cout << secondVariable << " " << &secondVariable << endl;
        cout << "The variables are different !" << endl;
    }
}

