#pragma once
#include "Grafo.h"
#include <iostream>
#include <queue>
#include <stack>

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

	stack<Arvore*> pilha;
	queue<Arvore*> fila;
	int *m_vetor_de_marcacao;
	void addAresta(int de, int para);
	ListNode** m_pLista;
	void Grau();
	void BFS_lista(int s);

	void DFS_lista(int s);

	Arvore* Parentesco(Arvore* v, int w);


};

