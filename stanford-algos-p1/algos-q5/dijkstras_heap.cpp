#include <vector>

class DijksHeap{
	public:
		vector <vector<int> > heap;
		
		// member functions
		int size(void);
		vector<int> getParent(vector<int> child);
		vector<vector<int> > getChild(vector<int> parent);
		void extractMin(void);
		vector<int> delete(int vertex);
		void insert(vector<int> vertex);
}
