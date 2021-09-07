#ifndef GRAFO_H
#define GRAFO_H
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

int max(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}

void imprimirVetor(vector<int> vetor){
    for(int i = 0; i < (int)vetor.size(); i++){
        cout << vetor[i] << ' ';
    }
    cout << endl;
}

void imprimirMatriz(vector<vector<int>> matrix){
    cout << "Matriz" << endl;
    for(int i = 0; i < (int)matrix.size(); i++){
        imprimirVetor(matrix[i]);
    }
    cout << endl;
}



vector<int> copyOfVector(vector<int> vetor){
    int i = 0;
    vector<int> copia;
    for(i = 0; i < (int)vetor.size(); i++){
        copia.push_back(vetor[i]);
    }
    return copia;
}

void clearStack(stack<int> pilha){
    while(!pilha.empty()){
        pilha.pop();
    }
}


bool vectorContainsElement(vector<int> vetor, int element){
    return count(vetor.begin(), vetor.end(), element);
}


bool matrixContainsElement(vector<vector<int>> matriz, int element){
    int i = 0;
    for(i = 0; i < (int)matriz.size(); i++){
        if(vectorContainsElement(matriz[i], element)){
            return true;
        }
    }
    return false;
}


void removeVisitedElements(vector<int> &vetor, vector<vector<int>> matriz){
    int i = 0;

    for(i = 0; i < (int)vetor.size(); i++){
        if(matrixContainsElement(matriz, vetor[i])){
            vetor.erase(vetor.begin() + i);
            i--;
        }
    }
}

int matrixContainsPair(vector<vector<int>> matrix, vector<int> pair){
    int i = 0;
    for(i = 0; i < matrix.size(); i++){
        if(matrix[i][0] == pair[0] && matrix[i][1] == pair[1])
            return 1;
        if(matrix[i][0] == pair[1] && matrix[i][1] == pair[0])
            return 1;
    }
    return 0;
}


void updateMatching(vector<vector<int>> &currentMatching, vector<vector<int>> &augmentingPath){
    int i = 0;
    for(i = 0; i < currentMatching.size(); i++){
        if(matrixContainsPair(augmentingPath, currentMatching[i])){
            currentMatching.erase(currentMatching.begin() + i);
            i--;
        }
    }

    for(i = 0; i < augmentingPath.size(); i+=2){
        currentMatching.push_back(augmentingPath[i]);
    }
}

int findPartition(vector<int> vetor, int elemento){
    int i = 0;
    int count = 0;
    for(i = 0; i < vetor.size(); i++){
        if(vetor[i] == -1)
            count++;
        else if(vetor[i] == elemento)
            return count;
    }
}

vector<int> filterVector(vector<int> vetor){

    vector<int> copia;
    copia = copyOfVector(vetor);
    int i;
    for(i = 0; i < copia.size(); i++){
        if(copia[i] == -1){
            copia.erase(copia.begin() + i);
            i--;
        }
    }
    return copia;
}



vector<vector<int>> retrievePathFromTree(vector<vector<int>> alteredBfsTree, int destino){

    int treeDepht = alteredBfsTree.size();
    int currentVertice = destino;
    vector<vector<int>> augmentingPath;
    int parentIndex;
    int i;
    vector<int> currentEdge;


    for(i = treeDepht - 1; i > 0; i--){
        currentEdge[0] = currentVertice;
        currentEdge[1] = filterVector(alteredBfsTree[i - 1])[findPartition(alteredBfsTree[i], currentVertice)];
        augmentingPath.push_back(currentEdge);
    }
}



class Grafo{

    public:
        Grafo(int _numVertices);

        int contemAresta(int origem, int destino);
        
        void construirAresta(int origem, int destino);
        
        vector<int> dfs(int verticeAtual, vector<int> &verticesVisitados, stack<int> &verticesParaKosaraju);

        void imprimirMatrizDeAdjacencia();

        vector<vector<int>> findMaximumMatching();

    private:
        vector<int> getNeighbouringVertices(int idVertice);
        // void partitionGraph();
        // vector<vector<int>> graphPartitions;
        int findAugmentingPath(vector<vector<int>> &currentMatching, vector<int> &freeVertices);    
        vector<vector<int>> matrizDeAdjacencia;
        int numVertices;
};

Grafo::Grafo(int _numVertices){
    numVertices = _numVertices;
    int i = 0;
    // int j = 0;
    for(i = 0; i < numVertices; i++){
        matrizDeAdjacencia.push_back(vector<int>(numVertices, 0));
    }
}

vector<int> Grafo::getNeighbouringVertices(int idVertice){
    vector<int> resposta;
    int i = 0;
    for(i - 0; i < numVertices; i++){
        if(contemAresta(idVertice, i))
            resposta.push_back(i);
    }
    return resposta;
}





void Grafo::construirAresta(int origem, int destino){
    matrizDeAdjacencia[origem - 1][destino - 1] = 1;
    matrizDeAdjacencia[destino - 1][origem - 1] = 1;
}

int Grafo::contemAresta(int origem, int destino){
    return matrizDeAdjacencia[origem][destino];
}



vector<int> Grafo::dfs(int verticeAtual, vector<int> &verticesVisitados, stack<int> &verticesParaKosaraju){
    verticesVisitados.push_back(verticeAtual);
    int i = 0;
    for(i = 0; i < numVertices; i++){
        if(matrizDeAdjacencia[verticeAtual][i] == 1 && !vectorContainsElement(verticesVisitados, i)){
            dfs(i, verticesVisitados, verticesParaKosaraju);
        }
    }
    verticesParaKosaraju.push(verticeAtual);
    return copyOfVector(verticesVisitados);
}


void Grafo::imprimirMatrizDeAdjacencia(){
    imprimirMatriz(matrizDeAdjacencia);
}

int Grafo::findAugmentingPath(vector<vector<int>> &currentMatching, vector<int> &freeVertices){
    int i = 0, j = 0;
    // int augmentingPathFound = 0;
    vector<vector<int>> alteredBfsTree;
    int nextEdgeShouldBeMatched = 0;
    vector<int> neighbours;
    queue<int> filaDeVertices;
    int treeLevel = 0;

    vector<int> currentEdge;

    if(freeVertices.size() <= 0)
        return 0;

    int origem = freeVertices[0];

    for(i = 0; i < freeVertices.size(); i++){
        
        treeLevel = 0;
        alteredBfsTree.clear();
        filaDeVertices.push(freeVertices[i]);
        alteredBfsTree[0].push_back(freeVertices[i]);

        do{
            neighbours = getNeighbouringVertices(filaDeVertices.front());
            treeLevel++;

            for(j = 0; j < neighbours.size(); j++){
                
                if(nextEdgeShouldBeMatched){

                    currentEdge[0] = filaDeVertices.front();
                    currentEdge[1] = neighbours[j];

                    if(matrixContainsPair(currentMatching, currentEdge) && !matrixContainsElement(alteredBfsTree, neighbours[j])){
                        alteredBfsTree[treeLevel].push_back(neighbours[j]);
                        filaDeVertices.push(neighbours[j]);
                    }

                } else{

                    currentEdge[0] = filaDeVertices.front();
                    currentEdge[1] = neighbours[j];

                    if(!matrixContainsPair(currentMatching, currentEdge) && !matrixContainsElement(alteredBfsTree, neighbours[j])){
                        
                        alteredBfsTree[treeLevel].push_back(neighbours[j]);
                        filaDeVertices.push(neighbours[j]);

                        if(vectorContainsElement(freeVertices, neighbours[j])){
                            updateMatching(currentMatching, retrievePathFromTree(alteredBfsTree, neighbours[j]));
                            return 1;
                        }
                    }
                }
            }

            filaDeVertices.pop();

        } while(!filaDeVertices.empty());
    }

    return 0;
}

vector<vector<int>> Grafo::findMaximumMatching(){

}



#endif