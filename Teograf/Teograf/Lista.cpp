#include "stdafx.h"
#include "Lista.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;


Lista::Lista(string path)
{
	ifstream myFile;
	myFile.open(path);
	cout << endl << "Lendo arquivo " << path << " Por favor aguarde." << endl;
	if (!myFile)
//Se o arquivo não existir
	{
		cout << "Arquivo " << path << " Nao foi encontrado.";
		return;
	}
	myFile >> m_numero_de_vertices;
// Salva o numero de vertices totais do grafo
	m_pLista = new ListNode*[m_numero_de_vertices + 1]();
	// aloca espaço para o vetor de tamanho igual ao numero de vertices +1, para nõ precisarmos
	//nos preocupar com o 0.
	m_numero_de_arestas = 0;

	string s;
	//guarda cada linha do arquivo
	while (getline(myFile, s))
	{
		if (s.empty() == false)
		{
			istringstream tmp(s);
			int v1, v2;
			tmp >> v1 >> v2;
			this->addAresta(v1, v2);
			this->addAresta(v2, v1);
		}
	}
	cout << endl << "Leitura ocorreu com sucesso" << endl;

	ofstream myInfoFile;
	myInfoFile.open(m_savePath + "/info.txt");
	myInfoFile << "# n = " << m_numero_de_vertices << endl
		<< "# m = " << (m_numero_de_arestas/2) << endl
		<< "# g_max = " << m_grau_maximo << endl
		<< "# g_min = " << m_grau_minimo << endl
		<< "# g_med = " << m_grau_medio << endl
		<< "# mediana = " << m_mediana_grau << endl;

	//TODO incluir informações sobre componentes conexas

	

	cout << "Analise salva em " << m_savePath << "/info.txt" << endl;

}



//constroi uma aresta
void Lista::addAresta(int de, int para)
{
	ListNode* no = new ListNode;
	no->vertice = para;
	if (m_pLista[de] != NULL)
	{
		m_pLista[de]->pPrev = no;
	}
	no->pNext = m_pLista[de];
	no->pPrev = NULL;
	this->m_pLista[de] = no;

	m_numero_de_arestas++;
}

Lista::~Lista()
{
	ListNode* temp;
	for (int i = 1; i <= m_numero_de_vertices; i++)
	{
		for (ListNode* neigh = m_pLista[i]; neigh != NULL;)
		{
			temp = neigh;
			neigh = neigh->pNext;
			delete temp;

		}
	}
	delete[] m_pLista;
}