#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <string>
#include <list>

using namespace std;

struct Arvore
{
	int vertice;
	int nivel;
	Arvore* ppai;

};
class Grafo
{
public:
	Grafo();
	~Grafo();


protected:
	int m_numero_de_vertices;
	int m_numero_de_arestas;
	int m_grau_minimo;
	int m_grau_maximo;
	float m_grau_medio;
	int m_mediana_grau;
	int * m_grau;
	string m_savePath = "output";

	void merge(int arr[], int l, int m, int r);

	void mergeSort(int arr[], int l, int r);

	void Infos();


};


#endif // GRAFO_H
