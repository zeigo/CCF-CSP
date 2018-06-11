#include <iostream>
#include <string>
#include <vector>

using namespace std;
// 注意大坑！！！URL末尾的斜杠要加入考虑，
// 即/articles/<int>/与/articles/2003，/articles/<int>与/articles/2003/均不匹配
// c++用的不熟，有的处理挺蠢的
struct Rule {
	string name;
	vector<string> params;
	vector<string> matches;
};

void get_rules(vector<Rule> &vr, int n);

bool match(string &url, Rule &rule);

int main(int argc, char const *argv[]) {
	int n, m;
	vector<Rule> vr;
	cin >> n >> m; // n rule条数，m URL个数
	get_rules(vr, n);
	string url;
	vector<string> urls;
	for(int i = 0; i < m; i++) {
		cin >> url;
		urls.push_back(url);
	}
	for(int i = 0; i < m; i++) {
		bool matched = false;
		for(int j = 0; j < n; j++) { // 依次对比规则
			Rule rule = vr[j];
			if(match(urls[i], rule)) {
				matched = true;
				cout << rule.name;
				for(int k = 0; k < rule.matches.size(); k++) {
					cout << " " + rule.matches[k];
				}
				rule.matches.clear();
				break;
			} else {
				rule.matches.clear();
			}
		}
		if(!matched) {
			cout << "404";
		}
		cout << endl;
	}
	return 0;
}

// 根据'/'将规则split成params，/a/<int>/划成{"a", "<int>", ""}
// 注意后面的空string用来处理边界情况
// start记录param的起点，由于url起点都为'/'，start从1开始
void get_rules(vector<Rule> &vr, int n) {
	for(int i = 0; i < n; i++) {
		string rule, name;
		int start = 1, num = 0;
		cin >> rule >> name;
		vector<string> params;
		for(int j = 1; j < rule.size(); j++) {
			if(rule[j] == '/') {
				params.push_back(rule.substr(start, num));
				start += num + 1;
				num = 0;
			} else {
				num++;
			}
		}
		if(num > 0) {
			params.push_back(rule.substr(start, num));
		} else {
			params.push_back("");
		}
		vr.push_back(Rule {name, params, vector<string>()});
	}
}

// 判断url是否能与rule匹配
bool match(string &url, Rule &rule) {
	int start = 1, n = url.size();
	for(int j = 0; j < rule.params.size(); j++) {
		int i = start, num = 0;
		string param = rule.params[j];
		if(param.empty()) { // rule结尾有'/'
			return i == n; // i==n时，url结尾也有'/'；i<n，url还未匹配到结尾；i>n，url结尾无'/'
		} else {
			bool flag = true; // 当不是path/int/str时不输出
			if(param == string("<path>")) { // <path>取到末尾
				while(i < n) {
					i++; num++;
				}
			} else if(param == string("<int>")) {
				while(i < n && url[i] != '/') {
					if(url[i] > '9' || url[i] < '0') { // 匹配失败
						return false;
					} else if(num == 0 && url[i] == '0' && i < n - 1) {
						start++; i++;
					} else {
						i++; num++;
					}
				}
			} else if(param == string("<str>")) {
				while(i < n && url[i] != '/') {
					i++; num++;
				}
			} else {
				int pi = 0, np = param.size(); // 从param的pi位置遍历
				while(i < n && url[i] != '/') {
					if(pi >= np || param[pi] != url[i]) return false;
					pi++; i++; num++;
				}
				if(pi < np) return false; // url长度不够匹配
				flag = false;
			}
			if(num > 0) {
				if(flag) rule.matches.push_back(url.substr(start, num));
				start += num + 1;
			} else {
				return false;
			}
		}
	}
	return start > n; // 当start>n，即params已匹配完，而url也刚好遍历完，匹配成功
}
//6 5
///articles/2003/ special_case_2003
///articles/<int> no_year_archive
///articles/<int>/ year_archive
///articles/<int>/<int>/ month_archive
///articles/<int>/<int>/<str>/ article_detail
///static/<path> static_serve
///articles/2001
///articles/2004/
///articles/1985/09/aloha/
///articles/hello/
///static/js/jquery.js

