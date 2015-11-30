#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

ifstream file("median.txt");

int main(){
	priority_queue<int> low;	// max heap
	priority_queue<int, vector<int>, greater<int> > high; // min heap


	string line;
	int number, sum = 0;
	if(file.is_open()){
		while(getline(file, line)){
			number = stoi(line);
			if(low.empty())
				low.push(number);
			else if (high.empty()){
				if (low.top() > number){
					high.push(low.top());
					low.pop();
					low.push(number);
				}
				else
					high.push(number);
			}
			else{

				// Note: low always has 0 or 1 more than high heap
				// high heap size is never more than low heap
				
				// must append to low heap
				if (high.size() >= low.size()){
					// number is greater than lowest of high heap
					if(number > high.top()){
						low.push(high.top());
						high.pop();
						high.push(number);
					}
					else
						low.push(number);
				}
				// must append to high heap
				else{
					if(number < low.top()){
						high.push(low.top());
						low.pop();
						low.push(number);
					}
					else
						high.push(number);
				}
			}
			sum += low.top();
			sum %= 10000;
		}
		file.close();

		cout << sum << endl;
	}
	return 0;
}

