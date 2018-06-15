#include <iostream>
#include <sstream>
#include <map>
using namespace std;
typedef map<string, int> Privileges; // name -> level(-1代表没有等级)
typedef Privileges::iterator Pit;
 
int str_to_int(string str);
// "git:3" -> name: "git", level: 3
// "game" -> name: "game", level: -1 
void get_name_level(string &privi, string &name, int &level);

int main() {
	int pn;
	cin >> pn;
	while(pn--) { // 这里输入实际无用 
		string privi;
		cin >> privi;
	}
	int rn; // role个数 
	cin >> rn;
	map<string, Privileges > roles;
	while(rn--) { // 得到roles及其对应权限
		string role;
		int rpn; // role输入的权限个数 
		cin >> role >> rpn;
		roles.insert(make_pair(role, Privileges()));
		Privileges &role_privis = roles[role]; 
		while(rpn--) {
			string privi;
			cin >> privi;
			string name;
			int level;
			get_name_level(privi, name, level);
			if(role_privis.find(name) != role_privis.end()) { // role权限重复出现，取高level
				level = max(level, role_privis[name]);
			}
			role_privis[name] = level;
		}
	}
	int un; // user个数 
	cin >> un;
	map<string, Privileges> users;
	while(un--) {
		string user;
		cin >> user;
		users.insert(make_pair(user, Privileges()));
		Privileges &user_privis = users[user];
		int urn; // user拥有的role个数
		cin >> urn;
		while(urn--) {
			string role;
			cin >> role;
			Privileges &role_privis = roles[role];
			// 遍历role的权限，更新到user里 
			for(Pit pit = role_privis.begin(); pit != role_privis.end(); pit++) {
				string name = pit->first;
				int level = pit->second;
				if(user_privis.find(name) != user_privis.end()) { // user的权限重复，取高level 
					level = max(level, user_privis[name]);
				}
				user_privis[name] = level;
			}
		}
	}
	int qn; // 查询数量
	cin >> qn; 
	while(qn--) {
		string user, privi;
		cin >> user >> privi;
		if(users.find(user) == users.end()) { // 用户不存在
			cout << "false" << endl;
		} else {
			Privileges &user_privis = users[user];
			string q_name;
			int q_level;
			get_name_level(privi, q_name, q_level);
			if(user_privis.find(q_name) == user_privis.end()) { // 权限名不存在
				cout << "false" << endl; 
			} else {
				int u_level = user_privis[q_name]; // 已记录的等级
				if(u_level == -1) {
					if(q_level == -1) // "crm" 查 "crm" 
						cout << "true" << endl;
					else // "crm:2" 查 "crm" 
						cout << "false" << endl;
				} else {
					if(q_level == -1) // "git" 查 "git:3" 
						cout << u_level << endl;
					else if(u_level >= q_level) // "git:2" 查 "git:3" 
						cout << "true" << endl;
					else // "git:4" 查 "git:3" 
						cout << "false" << endl;
				}
			}
		}
	}
	return 0;
}

int str_to_int(string str) {
	stringstream ss(str);
	int res;
	ss >> res;
	return res;
}

void get_name_level(string &privi, string &name, int &level) {
	int pos = privi.find(":");
	if(pos != string::npos) {
		name = privi.substr(0, pos);
		level = str_to_int(privi.substr(pos + 1));
	} else {
		name = privi;
		level = -1;
	}
}

