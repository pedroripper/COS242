#pragma once
#include "Grafo.h"
#include <iostream>

using namespace std;

struct ListNode 
{
	int vertice;
	ListNode* pNext;
	ListNode* pPrev;

};


class Lista :
	public Grafo
{
public:

	Lista(string path);
	~Lista();

protected:

	void addAresta(int de, int para);
	ListNode** m_pLista;
};

