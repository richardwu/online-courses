#include <stack>
#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

FILE *file;

int n_vertices = 875714;
int n_edges = 5105043;

bool *traversed = NULL;
int *f_times = NULL;

// list of edges
vector<vector<int> > edge_list; 
// list of scc sizes
vector<int> scc_sizes;
// adjacency lists
vector<vector<int> > G(n_vertices), Grev(n_vertices);


// Reverse sorting function
bool reverse_order(int i, int j){
	return i > j;
}

// Adds vertices to graph
void graph_add(vector <vector<int> >& graph, int v1, int v2){
	// Add v2 to adjacency list of v1
	graph.at(v1).push_back(v2);
}


void dfs_loop(vector <vector<int> >& graph){
	int f_t = 0;
	stack<int> dfs_stack;
	int scc_count = 0;
	// stack of vertices with highest f_time at the top
	// stack<int> f_time_v;

	// for (int i = 0; i < graph.size(); i++){
	// 	for(int j = 0; j < graph.at(i).size(); j++)
	// 		cout << graph.at(i).at(j) << ' ';
	// 	cout << endl;
	// }

	// Order vertices in terms of finishing time using graph
	for (int i = graph.size() - 1; i >= 0; i--){
		if (traversed[i] == false){
			dfs_stack.push(i);
			traversed[i] = true;
			scc_count = 0;

			// cout << "new loop " << endl;

			while(dfs_stack.size()){
				int cur_v = dfs_stack.top();
				// cout << "cur_v: " << cur_v << endl;
				bool pop = true;

				for(int j = 0; j < graph.at(cur_v).size(); j++){
					if (traversed[graph.at(cur_v).at(j)] == false){
						pop = false;
						break;
					}
				}

				if (pop){
					dfs_stack.pop();
					// increment finishing time & assign finishing time to cur_v
					f_t++;
					f_times[cur_v] = f_t;
					scc_count++;
					// cout << "scc_count " << scc_count << endl;
					// f_time_v.push(cur_v);
				}
				else{

					// add adjacent vertices to stack
					for(int k = 0; k < graph.at(cur_v).size(); k++){
						if (traversed[graph.at(cur_v).at(k)] == false){
							// set traversed true
							// cout << graph.at(cur_v).at(k) << endl;
							traversed[graph.at(cur_v).at(k)] = true;
							dfs_stack.push(graph.at(cur_v).at(k));
							break;
						}
					}
				}
			}
			scc_sizes.push_back(scc_count);
		}
	}

}



int main(){
	int v1, v2, index = 0;
	int max = -1;

	traversed = new bool[n_vertices];
	f_times = new int[n_vertices];

	file = fopen ("input.txt", "r");

	// Initialise adjacency lists
	for(int i = 0; i < n_edges; i++){
		fscanf(file, "%d %d", &v1, &v2);
			// account for index = 0
		v1--;
		v2--;

		vector<int> temp;
		temp.push_back(v1);
		temp.push_back(v2);
		edge_list.push_back(temp);	
		graph_add(Grev, v2, v1);

			// if (v1 > max)
			// 	max = v1;
			// if (v2 > max)
			// 	max = v2;

	}
	fclose (file);

	for ( int i = 0; i < n_vertices; i++)
		traversed[i] = false;

	// Find finishing times
	dfs_loop(Grev);

	for(int i = 0; i < edge_list.size(); i++){
		int v_index = f_times[edge_list.at(i).at(0)] - 1;
		graph_add(G, v_index, f_times[edge_list.at(i).at(1)] - 1);
	}

	// Reset scc_size list
	scc_sizes.clear();
	// Reset traversed array
	for ( int i = 0; i < n_vertices; i++)
		traversed[i] = false;

	// Find SCCs
	dfs_loop(G);

	// Print out 5 largest SCC sizes
	sort (scc_sizes.begin(), scc_sizes.end(), reverse_order);

	int end_i;
	if (scc_sizes.size() < 5)
		end_i = scc_sizes.size();
	else
		end_i = 5;

	for (int i = 0; i < end_i; i++)
		cout << "scc_size " << i+1 << ": " << scc_sizes.at(i) << endl;

	return 0;
}



