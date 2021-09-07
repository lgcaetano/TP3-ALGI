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
    for(i = 0; i < (int)matrix.size(); i++){
        if(matrix[i][0] == pair[0] && matrix[i][1] == pair[1])
            return 1;
        if(matrix[i][0] == pair[1] && matrix[i][1] == pair[0])
            return 1;
    }
    return 0;
}


void updateMatching(vector<vector<int>> &currentMatching, vector<vector<int>> augmentingPath){
    
    int i = 0;
    for(i = 0; i < (int)currentMatching.size(); i++){
        if(matrixContainsPair(augmentingPath, currentMatching[i])){
            currentMatching.erase(currentMatching.begin() + i);
            i--;
        }
    }

    for(i = 0; i < (int)augmentingPath.size(); i+=2){
        currentMatching.push_back(augmentingPath[i]);
    }
}

int findPartition(vector<int> vetor, int elemento){
    int i = 0;
    int count = 0;
    for(i = 0; i < (int)vetor.size(); i++){
        if(vetor[i] == -1)
            count++;
        else if(vetor[i] == elemento)
            return count;
    }
    return -1;
}

vector<int> filterVector(vector<int> vetor){

    vector<int> copia;
    copia = copyOfVector(vetor);
    int i;
    for(i = 0; i < (int)copia.size(); i++){
        if(copia[i] == -1){
            copia.erase(copia.begin() + i);
            i--;
        }
    }
    return copia;
}



vector<vector<int>> retrievePathFromTree(vector<vector<int>> alteredBfsTree, int destino){

    

    int treeDepht = (int)alteredBfsTree.size();
    int currentVertice = destino;
    int parentVertice;
    vector<vector<int>> augmentingPath;
    int i;
    vector<int> currentEdge(2, 0);

    

    for(i = treeDepht - 1; i > 0; i--){
        parentVertice = filterVector(alteredBfsTree[i - 1])[findPartition(alteredBfsTree[i], currentVertice)];;
        currentEdge[0] = currentVertice;
        currentEdge[1] = parentVertice;
        augmentingPath.push_back(currentEdge);
        currentVertice = parentVertice;
    }

    return augmentingPath;
}



class Grafo{

    public:
        Grafo(int _numVertices);

        int contemAresta(int origem, int destino);
        
        void construirAresta(int origem, int destino);
        
        vector<int> dfs(int verticeAtual, vector<int> &verticesVisitados, stack<int> &verticesParaKosaraju);

        void imprimirMatrizDeAdjacencia();

        vector<vector<int>> findMaximumMatching();

        int getSizeOfMinVertexCover();

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
    for(i = 0; i < numVertices; i++){
        if(contemAresta(idVertice, i))
            resposta.push_back(i);
    }
    return resposta;
}





void Grafo::construirAresta(int origem, int destino){
    matrizDeAdjacencia[origem][destino] = 1;
    matrizDeAdjacencia[destino][origem] = 1;
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

    bool nextEdgeShouldBeMatched = false;
    vector<int> neighbours;
    queue<int> filaDeVertices, filaSecundaria;
    int treeLevel = 0;

    vector<int> currentEdge(2, 0);

    if(freeVertices.size() <= 0)
        return 0;


    for(i = 0; i < (int)freeVertices.size(); i++){
        
        treeLevel = 0;
        alteredBfsTree.clear();
        alteredBfsTree.push_back(vector<int>(0, 0));
        filaDeVertices.push(freeVertices[i]);
        alteredBfsTree[0].push_back(freeVertices[i]);

        do{
            neighbours = getNeighbouringVertices(filaDeVertices.front());

            treeLevel++;

            nextEdgeShouldBeMatched = !nextEdgeShouldBeMatched;

            alteredBfsTree.push_back(vector<int>(0, 0));

            for(j = 0; j < (int)neighbours.size(); j++){
                
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

                            imprimirMatriz(alteredBfsTree);

                            return 1;
                        }
                    }
                }
            }

            alteredBfsTree[treeLevel].push_back(-1);
            filaDeVertices.pop();

        } while(!filaDeVertices.empty());
    }

    return 0;
}

vector<vector<int>> Grafo::findMaximumMatching(){

    vector<int> freeVertices;
    int i;
    vector<vector<int>> matching;

    for(i = 0; i < numVertices; i++){
        freeVertices.push_back(i);
    }

    int pathFound = 1;

    while(pathFound){

        pathFound = findAugmentingPath(matching, freeVertices);
        
        freeVertices.clear();
        
        for(i = 0; i< numVertices; i++){
            if(!matrixContainsElement(matching, i))
                freeVertices.push_back(i);
        }

    }

    return matching;
}


int Grafo::getSizeOfMinVertexCover(){
    vector<vector<int>> result = findMaximumMatching();
    // imprimirMatriz(result);
    return result.size();
}


#endif