#include <iostream>

using namespace std;
int main(int argc, char const *argv[])
{
    int sum = 0, last = 0, score;
    while(cin >> score) {
        switch (score)
        {
            case 0:
                cout << sum;
                return 0;
            case 1:
                sum += 1;
                last = 1;
                break;
            case 2:
                if(last == 1) {
                    last = 2;
                } else {
                    last += 2;
                }
                sum += last;
                break;
            default:
                break;
        }
    }
}
