#include "stdafx.h"
#include "Lista.h"
#include <iostream>
#include "Grafo.h"
#include <string>
using namespace std;


int main()
{
	//string arquivo= "";
	cout << "Por favor, indique o arquivo: " << endl;
	//getline(cin, arquivo);
	Lista Lista_de_Adjacencia = Lista("live_journal.txt");
    return 0;
}

