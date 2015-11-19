#include <iostream>
#include <fstream>

using namespace std;

int main(){
	ifstream file("input.txt");
	int count = 0;
	int x, y;

	while (file >> x >> y){
		count++;
		if (count == 1000001)
			cout << x << y << endl;
	}

	cout << count << endl;

	return 0;
}
