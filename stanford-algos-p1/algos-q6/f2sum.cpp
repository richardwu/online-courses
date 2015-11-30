#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>


using namespace std;

ifstream file ("f2sum.txt");
unordered_map<long, long> a;

int main(){

	// input processing
	string line;
	long number;
	if (file.is_open()){
		while(getline(file, line)){
			number = stol(line);
			a[number] = number;
		}
		file.close();
	}


	unordered_map<long, long>::const_iterator it;

	int count = 0;
	for (long t = -10000; t <= 10000; t++){
		for(auto& x: a){
			if (t - x.second != x.second){
				it = a.find(t-x.second);
				if (it != a.end()){
					count++;
					break;
				}
			}
		}
	}

	cout << count << endl;

	return 0;
}
