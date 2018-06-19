#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char const *argv[])
{
    int n;
    cin >> n;
    string pwd;
    cin >> pwd;
    getchar();
    while(n--) {
        string path;
        getline(cin, path); // 注意path可能为空字符串，不能直接cin>>path，前面要getchar 
        if(path == "") {
            cout << pwd << endl;
        } else {
            if(path[0] != '/') {
                path = pwd + "/" + path;
            }
            path += "/"; // 末尾补上"/"便于处理
            vector<string> stk;
            stringstream ss(path);
            string tmp;
            while(getline(ss, tmp, '/')) {
                if(tmp == ".") continue;
                else if(tmp == "..") {
                    if(!stk.empty()) stk.pop_back();
                } else if(!tmp.empty()) {
                    stk.push_back(tmp);
                }
            }
            if(stk.empty()) {
                cout << "/" << endl;
            } else {
                for(int i = 0; i < stk.size(); i++) {
                    cout << "/" + stk[i];
                }
                cout << endl;
            }
        }
    }
    return 0;
}
