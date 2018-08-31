#pragma once
#include "Grafo.h"
#include <string>
class Matriz :
	public Grafo
{
public:
	Matriz(string path);
	~Matriz();
private:
	void construtor();
	bool** m_matriz;
	void addAresta(int i, int j);
	int *m_grau;
	void Grau();
};

