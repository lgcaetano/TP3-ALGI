#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "grafo.h"

using namespace std;

int main(int argc, char** argv){
    
    string tarefa = argv[0];
    string filePath = argv[1];
    
    ifstream inputFile(filePath);

    int numVertices, numArestas;

    numVertices << inputFile;
    numArestas << inputFile;

    int i, id, verticeOrigem, verticeDestino;

    Grafo grafoVila(numVertices);

    for(i = 0; i < numArestas; i++){
        verticeOrigem << inputFile;
        verticeDestino << inputFile;
        grafoVila.construirAresta(verticeOrigem, verticeDestino);
    }
    








    return 1;
}