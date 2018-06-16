#include <iostream>
#include <list>
using namespace std;

// 某行剩num张，最小为start
struct Row {
	int start;
	int num;
	Row(int s, int n) : start(s), num(n) {}
};

// row从start输出n张票，更新start和num 
void print_n(Row &row, int n);

int main() {
	list<Row> rows; // 采用list存储每行，当某行卖完，删去该行 
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
			if(it->num >= num) { // 某行足够
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
