#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// һֱ60�֣����˰�����ul�����ol��ʯ��־������ 
// ��������ǿ���ͳ����� 
string deal_inline(string str);

int main() {
	string line, htm;
	while(getline(cin, line)) {
		if(line.find("#") == 0) { // ���� 
			int len = line.find_first_not_of("#"), // '#'����
			    start = line.find_first_not_of("# "); // ���⿪ʼ
			stringstream ss;
			ss << len;
			string lenstr = ss.str();
			htm += "<h" + lenstr + ">"
			       + deal_inline(line.substr(start))
			       + "</h" + lenstr + ">\n";
		} else if(line.find("*") == 0) { // �����б� 
			string ul, tmp;
			int start = line.find_first_not_of("* ");
			ul += "<li>" + deal_inline(line.substr(start)) + "</li>\n";
			while(getline(cin, tmp) && !tmp.empty()) {
				start = tmp.find_first_not_of("* ");
				ul += "<li>" + deal_inline(tmp.substr(start)) + "</li>\n";
			}
			htm += "<ul>\n" + ul + "</ul>\n";
		} else if(!line.empty()) { // ���� 
			string p = line, tmp;
			while(getline(cin, tmp) && !tmp.empty()) {
				p += "\n" + tmp;
			}
			htm += "<p>" + deal_inline(p) + "</p>\n";
		}
	}
	cout << htm;
	return 0;
}

string deal_inline(string str) {
	int pos = str.find("_");
	while(pos != string::npos) {
		str.replace(pos, 1, "<em>");
		pos = str.find("_", pos);
		str.replace(pos, 1, "</em>");
		pos = str.find("_", pos);
	}
	int p1 = str.find("[");
	while(p1 != string::npos) {
		int p2 = str.find("]", p1), p3 = str.find("(", p2), p4 = str.find(")", p3);
		string text = str.substr(p1 + 1, p2 - p1 - 1),
		       link = str.substr(p3 + 1, p4 - p3 - 1),
		       tl = "<a href=\"" + link + "\">" + text + "</a>";
		str.replace(p1, p4 - p1 + 1, tl);
		p1 = str.find("[", p1);
	}
	return str;
}
//##  hello w_orl_d
//
//p1:first line _[click](www.baidu.com)_
//second line
//
//p2
//
//* l1 _asd_
//* l2
//
//* l3
//
//A[Te_xxx_xt](links).
//asddasda

