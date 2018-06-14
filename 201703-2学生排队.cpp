#include <iostream>
#include <list>
#include <algorithm> 

using namespace std;
typedef list<int>::iterator It;

// list˫�������ʵ��+/-n 
It add_it(It i, int n) {
	while(n--) i++;
	return i;
}

It minus_it(It i, int n) {
	while(n--) i--;
	return i;
}
	

int main() {
	int n, m;
	cin >> n >> m;
	list<int> li;
	for(int i = 0; i < n; i++) {
		li.push_back(i + 1);
	}
	while(m--) {
		int num, step;
		cin >> num >> step;
		// posΪ����λ�ã�����1->2->3->4->5->end
		// 3 +2, 3Ҫ�嵽end֮ǰ����insert��posΪ3+3
		// 3 -1, 3Ҫ�嵽2֮ǰ����insert��posΪ3-1 
		It it = find(li.begin(), li.end(), num), pos; 
		if(step > 0) {
			pos = add_it(it, step + 1);
		
		} else {
			pos = minus_it(it, -step);
		}
		li.erase(it);
		li.insert(pos, num);
	}
	for(It i = li.begin(); i != li.end(); i++) {
		cout << *i << " ";
	}
	return 0;
}
