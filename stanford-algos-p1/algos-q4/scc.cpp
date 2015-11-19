#include <stack>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


// Adds vertices to graph
void graph_add(vector <vector<int> >& graph, int v1, int v2){
	// Add empty vectors until v1 is included 
	while (graph.size() <= v1)
		graph.push_back(vector<int>());

	// Add v2 to adjacency list of v1
	graph.at(v1).push_back(v2);
}


void dfs_loop(vector <vector<int> >& G, vector <vector<int> >& Grev, bool *traversed, int *f_times, int n_vertices){
	int f_t = 0;
	stack<int> dfs_stack;
	// stack of vertices with highest f_time at the top
	stack<int> f_time_v;

	// Order vertices in terms of finishing time using Grev
	for (int i = Grev.size() - 1; i >= 0; i--){
		if (traversed[i] == false){
			dfs_stack.push(i);
			traversed[i] = true;
			while(dfs_stack.size()){
				int cur_v = dfs_stack.top();
				bool pop = true;

				for(int j = 0; j < Grev.at(cur_v).size(); j++){
					if (traversed[Grev.at(cur_v).at(j)] == false){
						pop = false;
						break;
					}
				}

				if (pop){
					dfs_stack.pop();
					// increment finishing time & assign finishing time to cur_v
					//f_t++;
					//f_times[cur_v] = f_t;
					f_time_v.push(cur_v);
				}
				else{

					// add adjacent vertices to stack
					for(int k = 0; k < Grev.at(cur_v).size(); k++){
						if (traversed[Grev.at(cur_v).at(k)] == false){
							// set traversed true
							traversed[Grev.at(cur_v).at(k)] = true;
							dfs_stack.push(Grev.at(cur_v).at(k));
						}
					}
				}

			}
		}
	}

	int count = 0;
	vector<int> largest_sccs;

	for (int i = 0; i < n_vertices; i++)
		traversed[i] = false;

	while(f_time_v.size()){

		int cur_leader = f_time_v.top();
		f_time_v.pop();

		if(traversed[cur_leader] == false){
			dfs_stack.push(cur_leader);
			traversed[cur_leader] = true;

			while(dfs_stack.size()){
				int cur_v = dfs_stack.top();
				bool pop = true;
				for (int j = 0; j < G.at(cur_v).size(); j++){
					if(traversed[G.at(cur_v).at(j)] == false){
						pop = false;
						break;
					}
				}

				if(pop){
					dfs_stack.pop();
					count++;
				}
				else{
					// add adjacent vertices to stack
					for(int j = 0; j < G.at(cur_v).size(); j++){
						if (traversed[G.at(cur_v).at(j)] == false){
							// set traversed true
							traversed[G.at(cur_v).at(j)] = true;
							dfs_stack.push(G.at(cur_v).at(j));
						}
					}
				}
			}

			if (count > 0)
				largest_sccs.push_back(count);

			count = 0;
		}
	}

	sort(largest_sccs.begin(), largest_sccs.end());

	int size = largest_sccs.size();

	int end_i;
	if (size >= 5)
		end_i = size-5;
	else
		end_i = 0;

	for(int i = largest_sccs.size() - 1; i >= end_i; i--)
		cout << largest_sccs.at(i) << endl;


}



int main(){
	ifstream file;
	int v1, v2, index = 0, max = -1;
	// adjacency lists 
	vector <vector<int> > G, Grev;
	bool *traversed = NULL;
	int *f_times = NULL;

	file.open("input.txt");

	// Initialise adjacency lists
	if (file.is_open()){
		while (file >> v1){
			file >> v2;
			
			// account for index = 0
			v1--;
			v2--;

			graph_add(G, v1, v2);
			graph_add(Grev, v2, v1);

			if (v1 > max)
				max = v1;
			if (v2 > max)
				max = v2;

		}
		file.close();
	}

	// Initialize traversed array based on highest vertex
	int n_vertices = max + 1;
	traversed = new bool[n_vertices];
	f_times = new int[n_vertices];
	for ( int i = 0; i < n_vertices; i++)
		traversed[i] = false;

	dfs_loop(G, Grev, traversed, f_times, n_vertices);

	//cout << G.size() << endl;
	//cout << Grev.size() << endl;

	// for (int i = 0; i < G.at(0).size(); i++)
		// cout << G.at(0).at(i) << endl;

	// for (int i = 0; i < Grev.at(0).size(); i++)
		// cout << Grev.at(0).at(i) << endl;


	return 0;
}



