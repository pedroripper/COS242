#include <graph.h>
#include <string>

struct node{
	int vertex;
	node* pNext, pPrev;

};

class list{
	public:
		list(string path);
	protected:
		node* m_plist;

		void addEdge(int destV, int originV);



};