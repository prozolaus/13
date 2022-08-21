#include "std_lib_facilities.h"


int main()
{
    int R = 200;
    for (double i = 0; i < 360; i += 60)
    {

        cout << round(R * cos(i * M_PI / 180)) << endl;
        cout << round(R * sin(i * M_PI / 180)) << endl;
        cout << endl;
    }
}