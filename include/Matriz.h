#ifndef MATRIZ_H
#define MATRIZ_H

#include "Lista.h"
#include <string>
#include <queue>
#include <stack>

class Matriz :
	public Grafo
{
public:
	Matriz(string path);
	~Matriz();

private:
	void construtor();
	stack<Arvore*> pilha;
	bool** m_matriz;
	void addAresta(int i, int j);
	int *m_grau;
	queue<Arvore*> fila;
	int *m_vetor_de_marcacao;
	void BFS_Matriz(int s);
	void DFS_matriz(int s);
	Arvore * Parentesco(Arvore * v, int w);



};



#endif // MATRIZ_H
