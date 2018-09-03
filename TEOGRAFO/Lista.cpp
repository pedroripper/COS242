
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
        //Se o arquivo n„o existir
    {
        cout << "Arquivo " << path << " Nao foi encontrado.";
        return;
    }
    myFile >> m_numero_de_vertices;
    // Salva o numero de vertices totais do grafo
    m_pLista = new ListNode*[m_numero_de_vertices + 1]();
    
    // aloca espaÁo para o vetor de tamanho igual ao numero de vertices +1, para nı precisarmos
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
            
            if (v1 <= m_numero_de_vertices & v2 <= m_numero_de_vertices)
            {
                this->addAresta(v1, v2);
                this->addAresta(v2, v1);
            }
        }
    }
    
    
    //criando array de graus e ordenando e obtendo infos
    Grafo::m_grau = new int[m_numero_de_vertices + 1]();
    this->Grau();
    
    Grafo::mergeSort(Grafo::m_grau, 1, m_numero_de_vertices);
    Grafo::Infos();
    
    
    cout << endl << "Leitura ocorreu com sucesso" << endl;
    
    
    
    
    m_vetor_de_marcacao = new int[m_numero_de_vertices + 1](); //inicializa vetor de marcaÁ„o
    
    cout << "Por favor Aguarde" << endl;
    
    //FComponentes_conexas();  //chama funÁ„o para determinar informaÁıes sobre componentes conexas
    
    
    
    ofstream myInfoFile;
    myInfoFile.open(m_savePath + "/info.txt");
    myInfoFile << "# n = " << m_numero_de_vertices << endl
    << "# m = " << (m_numero_de_arestas) << endl
    << "# g_max = " << m_grau_maximo << endl
    << "# g_min = " << m_grau_minimo << endl
    << "# g_med = " << m_grau_medio << endl
    << "# mediana = " << m_mediana_grau << endl;
    /*<< "# numero de componentes conexas: " << m_numero_de_componentes_conexas << endl;
    
    int maior = m_tamanho_da_componente_conexa;
    int k = m_i;
    for (int i = 1; i <= m_numero_de_componentes_conexas; i++)
    {
        for (int i = 1; i <= m_numero_de_componentes_conexas; i++)
        {
            if (m_componentes_conexos[i] > maior)
            {
                maior = m_componentes_conexos[i];
                k = i;
                
            }
            
            
        }
        
        m_componentes_conexos[k] = 0;
        myInfoFile << "#numero de vertices da componete conexa: " << maior
        << endl << "#vetores que fazem parte dessa componente: ";
        for (int i = 1; i <= m_numero_de_vertices; i++)
        {
            if (m_vetor_de_marcacao[i] == k)
            {
                myInfoFile << i << ", ";
            }
        }
    }
    myInfoFile << endl << endl;
    
    m_vetor_de_marcacao = new int[m_numero_de_vertices + 1](); //inicializa vetor de marcaÁ„o*/
    
    
    cout << "Analise salva em " << m_savePath << "/info.txt" << endl;
    
    
    float tempo =0;
    for (int i = 1; i <= 10; i++)
    {
        start = std::chrono::system_clock::now();
        DFS_lista(1);
        end = std::chrono::system_clock::now();
        float elapse_seconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        tempo = tempo + elapse_seconds;
        m_vetor_de_marcacao = new int[m_numero_de_vertices + 1]();
    }
    tempo = tempo / 1000;
    cout << "Tempo de Execucao: " << tempo << " Milissegundos" << endl;
    
    
    
    
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
        cout << "Processo concluido." << endl;
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
        
        m_tamanho_da_componente_conexa++;
        
        
        int w;
        for (ListNode* neigh = m_pLista[v->vertice]; neigh != NULL;)
        {
            w = neigh->vertice;
            neigh = neigh->pNext;
            if (m_vetor_de_marcacao[w] == 0)     //se w n„o estiver marcado
            {
                m_vetor_de_marcacao[w] = 1;//marca w
                
                Arvore* x = this->Parentesco(v, w);  // cria relacionameneto entre os vertices
                
                //imprime informaÁıes sobre a arvore
                myBFSFile << "Vertice: " << x->vertice << ", Nivel: " << x->nivel
                << ", Pai: " << v->vertice << endl;
                
                fila.push(x);                   //coloca w na lista
                
            }
        }
    }
    
    return;
}



//DFS
void Lista::DFS_lista(int s)
{
    
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
            //imprime informaÁıes sobre a arvore
            myDFSFile << "Vertice: " << u->vertice << ", Nivel: " << u->nivel;
            
            if (!(u == raiz)) myDFSFile << ", Pai: " << u->ppai->vertice << endl;
            else myDFSFile << ", Pai: - " << endl;
            
            
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




void Lista::FComponentes_conexas()
{
    m_componentes_conexos = new int[m_numero_de_vertices + 1];
    m_i = 1;
    for (int i = 1; i <= m_numero_de_vertices; i++)
    {
        if (m_vetor_de_marcacao[i] == 0)
        {
            
            m_numero_de_componentes_conexas++;
            BFS_lista(i);
            
            m_componentes_conexos[i] = m_tamanho_da_componente_conexa;
            m_i++;
            
        }
        
    }
    
    
    m_i = 1;
    return;
}




