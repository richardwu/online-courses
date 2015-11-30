#include <vector>
#include <functional>
#include <iostream>
#include <queue>

using namespace std;

int main(){
	priority_queue<int> low;
	priority_queue<int, vector<int>, greater<int> > high;

	high.push(5);
	cout << high.top() << endl;
	high.push(10);
	cout << high.top() << endl;
	high.push(4);
	cout << high.top() << endl;
	high.push(15);
	cout << high.top() << endl;


	return 0;
}


