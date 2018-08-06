#include <iostream>
#define LOW 2
#define HIGH 20

using namespace std;

int main()
{
    for (int m = LOW; m <= HIGH; ++m)
    {
        vector <bool> covered(2*m + 1, false);
        covered[0] = covered[m - 1] = covered[m] = covered[m + 1] = covered[2*m] = true;

    }
}
