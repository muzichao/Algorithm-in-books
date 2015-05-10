#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

int main()
{
    clock_t start, end;
    start = clock();
    for (int x = 3; x < 10000; ++x)
    {
        int i = int(sqrt((x*(x+1)/2)));
        if ( 2 * i * i == x*(x+1))
        {
            cout << "x = " << x << " -- i = " << i << endl;
        }
    }

    end = clock();
    cout<<"Run time: "<< (double)(end - start) / CLOCKS_PER_SEC << "S" << endl;

    start = clock();
    for (int a = 2; a < 100; ++a)
    {
        int bTemp = int(a/sqrt(2));
        int a2Sub2b2down = a*a - 2*bTemp*bTemp;
        int a2Sub2b2up = a2Sub2b2down - (4*bTemp+2);

        if (a2Sub2b2down == 1)
        {
            cout << "x = " << 2*bTemp*bTemp << " -- i = " << a * bTemp << endl;
        }
        else if(a2Sub2b2up == -1)
        {
            cout << "x = " << a*a << " -- i = " << a * (bTemp+1) << endl;
        }
    }
    end = clock();
    cout<<"Run time: "<< (double)(end - start) / CLOCKS_PER_SEC << "S" << endl;

    return 0;
}
