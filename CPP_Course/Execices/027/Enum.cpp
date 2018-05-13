#include <iostream>

using namespace std;
/* enum - enumeration - 0 1 2 3 4 */

enum dayOfWeek {M = 1, TU, W, TH, F, SA, SN};

string getDay(dayOfWeek);
int main()
{
    dayOfWeek d = M;

    /*cout << d << endl;

    cout << dayOfWeek(W) << endl;
*/
    int i;
    cout << "Enter the day of a week " << endl;
    //....
    cin >> i;
    cout << getDay(dayOfWeek(i)) << endl;

    return 0;
}
string getDay(dayOfWeek d)
{
    switch(d)
    {
        case M:
            return "Monday";
        case TU:
            return "Tuesday";
        case W:
            return "Wednesday";
        case TH:
            return "Thursday";
        case F:
            return "Friday";
        case SA:
            return "Saturday";
        case SN:
            return "Sunday";
        default:
            return "You typed something wrong!";
    }
}
