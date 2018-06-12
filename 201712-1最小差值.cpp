#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char const *argv[])
{
    int n, x;
    vector<int> vi;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> x;
        vi.push_back(x);
    }    
    sort(vi.begin(), vi.end());
    int minDiff = 10000;
    for(int i = 0; i < n - 1; i++) {
        minDiff = min(abs(vi[i] - vi[i + 1]), minDiff);
    }
    cout << minDiff;
    return 0;
}
