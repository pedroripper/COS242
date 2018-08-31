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
	

	//criando array de graus e ordenando e obtendo infos
	Grafo::m_grau = new int[m_numero_de_vertices+1]();
	this->Grau();

	Grafo::mergeSort(Grafo::m_grau, 1, m_numero_de_vertices); 
	Grafo::Infos();



	cout << endl << "Leitura ocorreu com sucesso" << endl;

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
	cout << endl << "Deseja rodar BFS ou DFS?" << endl;
	string escolha;
	cin >> escolha;
	if (escolha == "BFS")
	{
		int vertice;
		cout << "Escolha um vertice:" << endl;
		cin >> vertice;
		cout << "Rodando BFS..." << endl;
		BFS_lista(vertice);
		cout << "Processo concluido." <<endl ;
	}
	if (escolha == "DFS")
	{
		int vertice;
		cout << "Escolha um vertice:" << endl;
		cin >> vertice;
		cout << "Rodando DFS..." << endl;
		DFS_lista(vertice);
		cout << "Processo concluido." << endl;
	}

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




void Lista::Grau()
{

	int grau = 0;
	ListNode* temp;
	for (int i = 1; i <= m_numero_de_vertices; i++)
	{
		for (ListNode* neigh = m_pLista[i]; neigh != NULL;)
		{
			temp = neigh;
			neigh = neigh->pNext;
			grau++;

		}

		Grafo::m_grau[i] = grau;
		grau = 0;
	}

	return;
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



// BFS

void Lista::BFS_lista(int s)
{
	m_vetor_de_marcacao = new int[m_numero_de_vertices + 1](); //inicializa vetor de marcação

	while (!fila.empty())   //cofere que a fila estara vazia
	{
		fila.pop();
	}


	Arvore* raiz = new Arvore;
	raiz->vertice = s;
	raiz->nivel = 0;
	raiz->ppai = NULL;

	ofstream myBFSFile;
	myBFSFile.open(m_savePath + "/lista_BFS.txt");
	myBFSFile << "Vertice: " << raiz->vertice << ", Nivel: " << raiz->nivel
		<< ", Pai: - " << endl;

	m_vetor_de_marcacao[s] = 1;    //marca vetor s
	fila.push(raiz);               //bota s na fila

	while (!fila.empty())
	{
		Arvore* v = fila.front();       //le elemento da fila
		fila.pop();                         // tira elemento da fila

		int w;
		for (ListNode* neigh = m_pLista[v->vertice]; neigh != NULL;)
		{
			w = neigh->vertice;
			neigh = neigh->pNext;
			if (m_vetor_de_marcacao[w] == 0)     //se w não estiver marcado
			{
				m_vetor_de_marcacao[w] = 1;//marca w

				Arvore* x = this->Parentesco(v, w);  // cria relacionameneto entre os vertices

				//imprime informações sobre a arvore
				myBFSFile << "Vertice: " << x->vertice << ", Nivel: " << x->nivel
					<< ", Pai: " << v->vertice << endl;
				
				fila.push(x);                   //coloca w na lista

			}
		}
	}


}



//DFS
void Lista::DFS_lista(int s)
{
	m_vetor_de_marcacao = new int[m_numero_de_vertices + 1](); //inicializa vetor de marcação
	while (!pilha.empty())   //cofere que a pilha estara vazia
	{
		pilha.pop();
	}
	Arvore* raiz = new Arvore;
	raiz->vertice = s;
	raiz->nivel = 0;
	raiz->ppai = NULL;

	ofstream myDFSFile;
	myDFSFile.open(m_savePath + "/lista_DFS.txt");

	pilha.push(raiz);               //bota s na pilha
	while (!pilha.empty())
	{
		Arvore* u = pilha.top();       //le elemento da fila
		pilha.pop();  // tira elemento da fila
		if (m_vetor_de_marcacao[u->vertice] == 0)
		{
			//imprime informações sobre a arvore
			myDFSFile << "Vertice: " << u->vertice << ", Nivel: " << u->nivel
				<< ", Pai: " << u->vertice << endl;

			m_vetor_de_marcacao[u->vertice] = 1;    //marca vetor s
			for (ListNode* neigh = m_pLista[u->vertice]; neigh != NULL;)
			{
				int v;
				v = neigh->vertice;
				neigh = neigh->pNext;
				Arvore* x = this->Parentesco(u, v);  // cria relacionameneto entre os vertices
				pilha.push(x);
			}

		}
	}

	return;
}



Arvore* Lista::Parentesco(Arvore* v, int w)
{
	Arvore* filho = new Arvore;
	filho->vertice = w;
	int nivel_pai = v->nivel;
	filho->nivel = nivel_pai + 1;
	filho->ppai = v;

	
	return filho;
}

