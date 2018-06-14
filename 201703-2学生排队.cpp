#include <iostream>
#include <list>
#include <algorithm> 

using namespace std;
typedef list<int>::iterator It;

// list双向迭代器实现+/-n 
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
		// pos为插入位置，假设1->2->3->4->5->end
		// 3 +2, 3要插到end之前，即insert的pos为3+3
		// 3 -1, 3要插到2之前，即insert的pos为3-1 
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
