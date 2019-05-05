/*
 * NAME: Eryl Kenner
 * EMAIL: eryl.kenner@gmail.com
 */

#include "AiMgr.h"
#include <iostream>
#include <fstream>
#include <vector>
#include<bits/stdc++.h>

AiMgr::AiMgr(Engine *eng) :
        Mgr(eng),
        numNodes(0){
}

AiMgr::~AiMgr(){
}

void AiMgr::Init(){

}

void AiMgr::Tick(float dt){

}
void AiMgr::LoadLevel(){
    std::fstream infile;
    infile.open("LevelOneNodes.txt", std::ios::in);
    infile >> numNodes;
    //nodes.resize(numNodes);

    std::string line;
    for(int i = 0; i < numNodes; ++i){
        getline(infile, line);
        if(line.empty()){
            i--;
            continue;
        }
        std::istringstream ss(line);
        int index;
        float vectorX;
        float vectorY;
        std::string remaining;
        char eater;

        ss >> index >> eater >> eater >> vectorX >> eater >> vectorY >> eater >> eater
                >> remaining;
        nodes.push_back(Ogre::Vector2(vectorX, vectorY));
        //Populate adjacencyList
        std::vector<int> adjacentItems;
        int left = 0;
        for(unsigned int j = 0; j < remaining.size(); ++j){
            if(remaining[j] == ','){
                adjacentItems.push_back(std::stoi(remaining.substr(left, j - left)));
                left = j + 1;
            }
        }
        adjacentItems.push_back(
                std::stoi(remaining.substr(left, remaining.size() - left)));
        adjacenyList.push_back(adjacentItems);
    }
    infile.close();

    for(int i = 0; i < numNodes; ++i){
        ShortestPathTrees.push_back(GenerateShortestPathTree(i));
        //std::cout << "------------------------" << std::endl;
    }
}

int AiMgr::GetClosestNode(Ogre::Vector2 point) const{
    int closestIndex;
    float closestNodeDistSqr = INT_MAX;
    for(int i = 0; i < numNodes; ++i){
        float distSqared = nodes[i].squaredDistance(point);
        if(distSqared < closestNodeDistSqr){
            closestNodeDistSqr = distSqared;
            closestIndex = i;
        }
    }
    return closestIndex;
}

int AiMgr::GetClosestNode(Ogre::Vector3 point) const{
    return GetClosestNode(Ogre::Vector2(point.x, point.z));
}

void AiMgr::Stop(){
}

std::vector<int> AiMgr::GenerateShortestPathTree(int targetNode) const{
    std::priority_queue<std::pair<float, int>, std::vector<std::pair<float, int>>,
            std::greater<std::pair<float, int>>> pq;
    std::vector<float> distanceList(numNodes, INT_MAX);
    std::vector<int> parentList(numNodes, targetNode);
    std::vector<bool> inSPT(numNodes, false);

    pq.push(std::make_pair(0.0, targetNode));
    distanceList[targetNode] = 0;

    while(!pq.empty()){
        int u = pq.top().second;
        pq.pop();
        inSPT[u] = true;

        for(unsigned int i = 0; i < adjacenyList[u].size(); ++i){
            int v = adjacenyList[u][i] - 1;
            float weight = nodes[u].distance(nodes[v]);

            if(!inSPT[v] && distanceList[v] > distanceList[u] + weight){
                distanceList[v] = distanceList[u] + weight;
                pq.push(std::make_pair(distanceList[v], v));
                parentList[v] = u;
            }
        }
    }
    return parentList;
    /*for(int i = 1; i < numNodes; ++i){
        printf("%d - %d\n", i + 1, parentList[i] + 1);
    }*/
}

