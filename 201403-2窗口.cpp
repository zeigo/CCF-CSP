#include <iostream>
#include <list>
using namespace std;

struct Win {
    int num;
    int left;
    int top;
    int right;
    int bottom;
    Win(int n, int l, int t, int r, int b) : num(n), left(l), top(t), right(r), bottom(b) {}
};
// 判断坐标是否在窗口内
bool in_win(int x, int y, Win &w);

int main(int argc, char const *argv[])
{
    int n, m;
    cin >> n >> m;
    list<Win> wins;
    for(int i = 0; i < n; i++) {
        int left, top, right, bottom;
        cin >> left >> top >> right >> bottom;
        wins.push_back(Win(i + 1, left, top, right, bottom));
    }
    while(m--) {
        int x, y;
        cin >> x >> y;
        bool is_found = false;
        for(list<Win>::iterator it = --wins.end(); it != --wins.begin(); it--) {
            if(in_win(x, y, *it)) {
                cout << it->num << endl;
                wins.push_back(*it);
                wins.erase(it);
                is_found = true;
                break;
            }
        }
        if(!is_found) {
            cout << "IGNORED" << endl;
        }
    }
    return 0;
}

bool in_win(int x, int y, Win &w) {
    return w.left <= x && w.right >= x && w.top <= y && w.bottom >= y;
}