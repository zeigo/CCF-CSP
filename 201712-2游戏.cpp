#include <iostream>
#include <queue>

using namespace std;

// 先将编号全放入队列，每次从头部取编号报数。若被淘汰，直接删去；若未淘汰，放到最后
int main(int argc, char const *argv[])
{
    int n, k;
    cin >> n >> k;
    int count = 1;
    queue<int> qi;
    for(int i = 0; i < n; i++) {
        qi.push(i + 1);
    }
    while(qi.size() > 1) {
        int num = qi.front();
        qi.pop();
        if(count % k == 0 || count % 10 == k) {
        } else {
            qi.push(num);
        }
        count++;
    }
    cout << qi.front();
    return 0;
}
