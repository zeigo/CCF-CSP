#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <sstream>
using namespace std;
// 按' '分割str
vector<string> split_str(string &str);

int main(int argc, char const *argv[])
{
    string optstr;
    cin >> optstr;
    set<string> opts, opts_arg; // opts无参选项集合，opts_arg有参选项集合
    for(int i = 0; i < optstr.size(); i++) {
        if((i + 1 < optstr.size()) && optstr[i + 1] == ':') {
            opts_arg.insert("-" + optstr.substr(i, 1));
            i++;
        } else {
            opts.insert("-" + optstr.substr(i, 1));
        }
    }
    int n;
    cin >> n;
    getchar();
    for(int i = 0; i < n; i++) {
        string cmd;
        getline(cin, cmd);
        vector<string> args = split_str(cmd);
        map<string, string> buffer;
        for(int j = 1; j < args.size(); j++) {
            string arg = args[j];
            if(opts.find(arg) != opts.end()) { // arg为无参选项
                buffer[arg] = string("");
            } else if(opts_arg.find(arg) != opts_arg.end()) { // arg为有参选项
                if(j + 1 < args.size()) { // 确保j不是最后一个
                    buffer[arg] = args[j + 1];
                    j++;
                }
            } else {
                break;
            }
        }
        cout << "Case " << i + 1 << ": ";
        for(map<string, string>::iterator it = buffer.begin(); it != buffer.end(); it++) {
            if(it->second.empty()) {
                cout << it->first << " ";
            } else {
                cout << it->first << " " << it->second << " ";
            }
        }
        cout << endl;
    }
    return 0;
}

vector<string> split_str(string &str) {
    str += " ";
    stringstream ss(str);
    vector<string> res;
    string tmp;
    while(getline(ss, tmp, ' ')) {
        res.push_back(tmp);
    }
    return res;
}
