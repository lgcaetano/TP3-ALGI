#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "grafo.h"

using namespace std;

int main(int argc, char** argv){
    
    string tarefa(argv[1]);             
    string filePath(argv[2]);
      
    // cout << "AQUI" << endl;  
   
    ifstream inputFile(filePath);                  

    int numVertices, numArestas;
       
    inputFile >> numVertices;  
    inputFile >> numArestas;  
 
    int i, verticeOrigem, verticeDestino;               

    Grafo grafoVila(numVertices);

    // cout << tarefa << endl;  

    for(i = 0; i < numArestas; i++){
        inputFile >> verticeOrigem;
        inputFile >> verticeDestino;
        // cout << verticeOrigem << " " << verticeDestino << endl;   
        grafoVila.construirAresta(verticeOrigem, verticeDestino);
    }
                            

    if(tarefa == "tarefa1"){
        cout << grafoVila.getSizeOfMinVertexCover() << endl;
    } else if(tarefa == "tarefa2"){
        grafoVila.vertexCoverEstimate();
    }
     
    return 1;       
}