#include <iostream>
#include <sstream>
#include <map>
using namespace std;
typedef map<string, int> Privileges; // name -> level(-1����û�еȼ�)
typedef Privileges::iterator Pit;
 
int str_to_int(string str);
// "git:3" -> name: "git", level: 3
// "game" -> name: "game", level: -1 
void get_name_level(string &privi, string &name, int &level);

int main() {
	int pn;
	cin >> pn;
	while(pn--) { // ��������ʵ������ 
		string privi;
		cin >> privi;
	}
	int rn; // role���� 
	cin >> rn;
	map<string, Privileges > roles;
	while(rn--) { // �õ�roles�����ӦȨ��
		string role;
		int rpn; // role�����Ȩ�޸��� 
		cin >> role >> rpn;
		roles.insert(make_pair(role, Privileges()));
		Privileges &role_privis = roles[role]; 
		while(rpn--) {
			string privi;
			cin >> privi;
			string name;
			int level;
			get_name_level(privi, name, level);
			if(role_privis.find(name) != role_privis.end()) { // roleȨ���ظ����֣�ȡ��level
				level = max(level, role_privis[name]);
			}
			role_privis[name] = level;
		}
	}
	int un; // user���� 
	cin >> un;
	map<string, Privileges> users;
	while(un--) {
		string user;
		cin >> user;
		users.insert(make_pair(user, Privileges()));
		Privileges &user_privis = users[user];
		int urn; // userӵ�е�role����
		cin >> urn;
		while(urn--) {
			string role;
			cin >> role;
			Privileges &role_privis = roles[role];
			// ����role��Ȩ�ޣ����µ�user�� 
			for(Pit pit = role_privis.begin(); pit != role_privis.end(); pit++) {
				string name = pit->first;
				int level = pit->second;
				if(user_privis.find(name) != user_privis.end()) { // user��Ȩ���ظ���ȡ��level 
					level = max(level, user_privis[name]);
				}
				user_privis[name] = level;
			}
		}
	}
	int qn; // ��ѯ����
	cin >> qn; 
	while(qn--) {
		string user, privi;
		cin >> user >> privi;
		if(users.find(user) == users.end()) { // �û�������
			cout << "false" << endl;
		} else {
			Privileges &user_privis = users[user];
			string q_name;
			int q_level;
			get_name_level(privi, q_name, q_level);
			if(user_privis.find(q_name) == user_privis.end()) { // Ȩ����������
				cout << "false" << endl; 
			} else {
				int u_level = user_privis[q_name]; // �Ѽ�¼�ĵȼ�
				if(u_level == -1) {
					if(q_level == -1) // "crm" �� "crm" 
						cout << "true" << endl;
					else // "crm:2" �� "crm" 
						cout << "false" << endl;
				} else {
					if(q_level == -1) // "git" �� "git:3" 
						cout << u_level << endl;
					else if(u_level >= q_level) // "git:2" �� "git:3" 
						cout << "true" << endl;
					else // "git:4" �� "git:3" 
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

