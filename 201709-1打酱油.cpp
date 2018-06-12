#include <iostream>

using namespace std;


int main(int argc, char const *argv[])
{
    int n, count;
    cin >> n;
    n /= 10;
    while(n >= 5) {
        n -= 5;
        count += 7;
    }
    while(n >= 3) {
        n -= 3;
        count += 4;
    }
    count += n;
    cout << count;
    return 0;
}
