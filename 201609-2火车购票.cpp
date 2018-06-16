#include <iostream>
#include <list>
using namespace std;

// ĳ��ʣnum�ţ���СΪstart
struct Row {
	int start;
	int num;
	Row(int s, int n) : start(s), num(n) {}
};

// row��start���n��Ʊ������start��num 
void print_n(Row &row, int n);

int main() {
	list<Row> rows; // ����list�洢ÿ�У���ĳ�����꣬ɾȥ���� 
	for(int i = 0; i < 20; i++) {
		rows.push_back(Row(5 * i + 1, 5));
	}
	int n;
	cin >> n;
	while(n--) {
		int num;
		cin >> num;
		bool is_enough = false;
		for(list<Row>::iterator it = rows.begin(); it != rows.end(); it++) {
			if(it->num >= num) { // ĳ���㹻
				print_n(*it, num);
				if(it->num == 0) rows.erase(it);
				cout << endl;
				is_enough = true;
				break;
			}
		}
		if(!is_enough) {
			for(list<Row>::iterator it = rows.begin(); it != rows.end(); it++) {
				if(it->num >= num) {
					print_n(*it, num);
					if(it->num == 0) rows.erase(it);
					cout << endl;
					break;
				} else {
					num -= it->num;
					print_n(*it, it->num);
					list<Row>::iterator tmp = it;
					it--;
					rows.erase(tmp);
				}
			}
		}
	}
	return 0;
}

void print_n(Row &row, int n) {
	int start = row.start;
	for(int j = 0; j < n; j++) {
		cout << start + j << " ";
	}
	row.start += n;
	row.num -= n;
}
