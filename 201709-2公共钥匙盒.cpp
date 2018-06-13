#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
 
using namespace std;

int main(int argc, char const *argv[])
{
    int n, k; // n钥匙数，k使用数
    cin >> n >> k;
    vector<int> keys(n);
    for(int i = 0; i < n; i++) {
        keys[i] = i + 1;
    }
    typedef map<int, pair<vector<int>, vector<int> > > Plan;
    Plan plan; // 某时要取/还的钥匙
    while(k--) {
        int w, s, c; // w编号，s取时，c时长
        cin >> w >> s >> c;
        plan[s].first.push_back(w);
        plan[s + c].second.push_back(w);
    }
    for(Plan::iterator it = plan.begin(); it != plan.end(); it++) {
        vector<int> fetchs = it->second.first, backs = it->second.second;
        if(!backs.empty()) { // 先放回
            sort(backs.begin(), backs.end()); // 排序
            int j = 0; // 依次寻找空位，可利用上次找到的空位减少查询时间
            for(vector<int>::iterator i = backs.begin(); i != backs.end(); i++) {
                while(j < n) {
                    if(keys[j] == 0) {
                        keys[j] = *i;
                        j++;
                        break;
                    }
                    j++;
                }
            }
        }
        if(!fetchs.empty()) { // 取钥匙，找到对应位置j即将keys[j]置为0
            for(vector<int>::iterator i = fetchs.begin(); i != fetchs.end(); i++) {
                for(int j = 0; j < n; j++) {
                    if(keys[j] == *i) {
                        keys[j] = 0;
                        break;
                    }
                }
            }
        }
    }
    for(int i = 0; i < n; i++) {
        cout << keys[i] << " ";
    }
    return 0;
}
