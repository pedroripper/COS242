#include "stdafx.h"
#include "Matriz.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;


Matriz::Matriz(string path)
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

	myFile >> m_numero_de_vertices;    	// Salva o numero de vertices totais do grafo

	

	this->construtor();       //chama a função para construir a matriz


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

	m_grau_medio = (float)m_numero_de_arestas / m_numero_de_vertices;
	m_numero_de_arestas = m_numero_de_arestas / 2;

	cout << endl << "Leitura ocorreu com sucesso" << endl;


	//criando array de graus e ordenando e obtendo infos
	Grafo::m_grau = new int[m_numero_de_vertices + 1]();
	this->Grau();
	Grafo::mergeSort(Grafo::m_grau, 1, m_numero_de_vertices);
	Grafo::Infos();


	ofstream myInfoFile;
	myInfoFile.open(m_savePath + "/info.txt");
	myInfoFile << "# n = " << m_numero_de_vertices << endl
		<< "# m = " << (m_numero_de_arestas) << endl
		<< "# g_max = " << m_grau_maximo << endl
		<< "# g_min = " << m_grau_minimo << endl
		<< "# g_med = " << m_grau_medio << endl
		<< "# mediana = " << m_mediana_grau << endl;

	//TODO incluir informações sobre componentes conexas



	cout << "Analise salva em " << m_savePath << "/info.txt" << endl;


}


void Matriz::addAresta(int linha, int coluna)
{
	m_matriz[linha][coluna] = true;
	m_numero_de_arestas++;
	return;
}



void Matriz::construtor()
{

	m_matriz = new bool*[m_numero_de_vertices+1];

	for (int i = 0; i < m_numero_de_vertices + 1; ++i)
		
		m_matriz[i] = new bool[m_numero_de_vertices];

	//iniciando ela com zero
	for (int i = 0; i < m_numero_de_vertices; ++i)
		for (int j = 0; j < m_numero_de_vertices; ++j)
			m_matriz[i][j] = false;

	return;
}




Matriz::~Matriz()
{
	for (int i = 0; i < m_numero_de_vertices; ++i)
		delete[]m_matriz[i];

	delete[]m_matriz;
}


void Matriz::Grau()
{
	int grau = 0;
	for (int i = 1; i <= m_numero_de_vertices; i++)
	{
		for (int j = 1; j <= m_numero_de_vertices; j++)
		{
			if (m_matriz[i][j] == true) grau++;	
		}

		Grafo::m_grau[i] = grau;
		grau = 0;
	}
	return;
}

