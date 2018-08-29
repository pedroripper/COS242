#include "list.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

list::list(const char* file){
	ifstream myFile;

	myFile.open(file);

	//number of vertices in the graph:
	myFile >> m_numVertices;
	//allocate space for adj list pointers
	m_pList = new node*[m_numVertices+1]();
	//number of vertices
	m_numEdges = 0;

	string s;

	while (getline(myFile, s)){
		if (s.empty() == false){
			istringstream tmp(s);
			int v1,v2;
			tmp >> v1 >> v2;

			this -> addEdge(v1,v2);
		}
	}
	ofstream myInfoFile;
	myInfoFile.open(m_savePath + "/info.txt");
	myInfoFile << "Number of Vertices" << m_numVertices << endl
	<< "Number of Edges" << m_numEdges << endl;
}

list::addEdge(int originV, int destV){
	node* no = new node;
	 no-> to;
	 if (m_pList[from] != NULL) m_pList[from]->pPrev = no;
	 no-> pNext = m_pList[from];
	 link->pPrev = NULL;
	 this->m_pList[from] = link;

	 m_numEdges++;
}


