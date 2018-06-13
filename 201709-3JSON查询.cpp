#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;
typedef map<string, string> Kv;
// 修剪空格
void trim(string &str);
// 转义 \\ \"
void escape(string &str);
// 根据去掉{}的json找出key-value,多层的记录"a.b" -> "", "a.b.c" -> "foo"
void find_key_value(string &str, string prefix, Kv &kv);
// 找到pos位置上'{'对应的'}'的位置
int find_right_brace(string &str, int pos);

int main(int argc, char const *argv[]) {
	int n, m;
	cin >> n >> m;
	getchar(); // 第一行换行
	string json;
	while(n--) {
		string line;
		getline(cin, line);
		json += line;
	}
	trim(json);
	json = json.substr(1, json.size() - 2);
	string prefix;
	Kv kv;
	find_key_value(json, prefix, kv);
	vector<string> query(m);
	for(int i = 0; i < m; i++) {
		cin >> query[i];
	}
	for(int i = 0; i < m; i++) {
		string key = query[i];
		if(kv.find(key) != kv.end()) {
			if(kv[key].empty()) {
				cout << "OBJECT" << endl;
			} else {
				cout << "STRING " << kv[key] << endl;
			}
		} else {
			cout << "NOTEXIST" << endl;
		}
	}
	return 0;
}

void trim(string &str) {
	int pos = str.find(" ");
	while(pos != string::npos) {
		str.replace(pos, 1, "");
		pos = str.find(" ", pos);
	}
}

void replace_all(string &str, char c) {
	int i = 0;
	while(i < str.size()) {
		if(str[i] == c && str[i - 1] == '\\') {
			str.erase(i - 1, 1);
		} else {
			i++;
		}
	}
}

void escape(string &str) {
	 replace_all(str, '\"');
	 replace_all(str, '\\');
}

void find_key_value(string &str, string prefix, Kv &kv) {
    str += ",";
    int start = 0, colon = str.find(":", start);
    while(colon != string::npos) {
        // 先找冒号:，从start到colon，去掉""后为key
        string key = str.substr(start + 1, colon - start - 2);
        escape(key);
        if(str[colon + 1] == '\"') { 
            // colon后为'\"',value为string，寻找逗号comma，中间部分去掉""为value
            int comma = str.find(",", colon);
            string value = str.substr(colon + 2, comma - colon - 3);
            escape(value);
			kv[prefix + key] = value;
            start = comma + 1;
        } else if(str[colon + 1] == '{') {
            // colon后为'{',value为object，寻找匹配的右括号，中间部分去掉""，value递归
            int rightBrace = find_right_brace(str, colon + 1);
            string value = str.substr(colon + 2, rightBrace - colon - 2);
			kv[prefix + key] = string();
			find_key_value(value, prefix + key + ".", kv);
            start = rightBrace + 2;
		}
        colon = str.find(":", start);
    }
}

int find_right_brace(string &str, int pos) {
    int stk = 1;
    for(int i = pos + 1; i < str.size(); i++) {
        if(str[i] == '{') stk++;
        else if(str[i] == '}') {
            stk--;
            if(stk == 0) return i;
        }
    }
}

