#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

// case-specific constants
int start_v = 1;
int end_v[] = {7,37,59,82,99,115,133,165,188,197};
int end_size = 10;
int n_vertices = 200;



// global variables
ifstream file("input.txt");
vector<vector<vector<int> > > graph(n_vertices);
vector<int> X;
int *A; 






int main(){
	// init greedy scores to 1000000
	A = new int[n_vertices];
	fill_n(A, n_vertices, 1000000);





	// input processing
	string line;
	while(getline(file, line)){
		istringstream iss(line);
		string str_v2, v2_temp, l_v1v2_temp;
		int v1, v2, l_v1v2;

		iss >> v1;
		v1--;

		while (iss >> str_v2){
			istringstream iss2(str_v2);
			getline(iss2, v2_temp, ',');
			getline(iss2, l_v1v2_temp, ',');
			v2 = atoi(v2_temp.c_str());
			l_v1v2 = atoi(l_v1v2_temp.c_str());
			v2--;

			vector<int> temp;
			temp.push_back(v2);
			temp.push_back(l_v1v2);
			graph.at(v1).push_back(temp);
		}
	}






	// init X with start vertex
	X.push_back(start_v-1);	
	A[start_v-1] = 0;

	// loop until all vertices added to X
	while (X.size() < n_vertices){
		int min_X_ver;
		vector<int> min_l;

		// loop through X vertices to find crossing edges 
		for (int i = 0; i < X.size(); i++){
			int X_ver = X.at(i);
			// loop through adjacency list to find min length
			for (int j = 0; j < graph.at(X_ver).size(); j++){
				vector<int> adj_ver = graph.at(X_ver).at(j);

				vector<int>::iterator it = find(X.begin(), X.end(), adj_ver.at(0));

				// proceed if adj vertex is not in X already
				if (it == X.end()){

					// assign min_l as first pair
					if(min_l.empty()){
						min_X_ver = X_ver;
						min_l = adj_ver;
						min_l.at(1) += A[min_X_ver];
					}
					// assign min_l if shorter length is found
					else if (adj_ver.at(1) + A[X_ver] < min_l.at(1)){
						min_X_ver = X_ver;
						min_l = adj_ver;
						min_l.at(1) += A[min_X_ver];
					}
				}
			}
		}
		// assign greedy score to new X vertex
		A[min_l.at(0)] = min_l.at(1);
		// push in vertex into X	
		X.push_back(min_l.at(0));
	}

	for (int i = 0; i < end_size; i++){
		cout << A[end_v[i]-1];
		if (i != end_size - 1)
			cout << ',';
	}
	cout << endl;

	return 0;
}
