#include "AStar.h"
#include <WorldEngine/WorldGeometry.h>
#include <WorldEngine/Cell.h>
#include <priorityqueue/PriorityQueue.h>
#define MAX 16384
AStar::AStar(Cell* source, Cell* target) {
    worldGeometry = WorldGeometry::Instance();
    
    sourceCell = source;
    targetCell = target;
    sourceIndex = source->getIndex();
    targetIndex = target->getIndex();
    
    GCosts = std::vector<f32>(MAX, 0);
    FCosts = std::vector<f32>(MAX, 0);

    shortestPath = std::vector<Cell*>(MAX, nullptr);
    searchFrontier = std::vector<Cell*>(MAX, nullptr);
}
AStar::~AStar() {
    shortestPath.clear();
    searchFrontier.clear();
    GCosts.clear();
    FCosts.clear();
}

void AStar::Search() {
    IndexedPriorityQLow<f32> pq(FCosts, MAX);
    pq.insert(sourceIndex);
    while(!pq.empty()) {
        i32 closestIndex = pq.Pop();
        //std::cout << "Selected index: " << closestIndex << "\n";
    /* Adds the cell to the path vector */
        shortestPath[closestIndex] = searchFrontier[closestIndex];

    /* Stop condition, research about a system of conditions */
        if (closestIndex == targetIndex) {
            //std::cout << "Path finded. \n";
            return ;
        }
    /* Get neighbors of the chosen cell */
        std::vector<Cell*> neighbors = worldGeometry->getNeighbors(closestIndex);
        //std::cout << "Checking neighbors \n";
    /* Calculate the cost for each neighbor to the targetCell */
        for (i32 i = 0; i < neighbors.size(); i++) {
            if (!neighbors[i]->isBlocked()) {
                i32 potentialNode = neighbors[i]->getIndex();
                f32 HCost = worldGeometry->calculateDistance(neighbors[i]->getPosition(), targetCell->getPosition());
                f32 GCost = GCosts[closestIndex] + worldGeometry->getCost(closestIndex, i);
                //std::cout << "Distancia H: " << HCost << "\n";
                //std::cout << "Distancia G: " << GCost << "\n";
                if (searchFrontier[potentialNode] == nullptr) {
                    FCosts[potentialNode] = GCost + HCost;
                    GCosts[potentialNode] = GCost;

                    pq.insert(potentialNode);
                    searchFrontier[potentialNode] = worldGeometry->indexToCell(closestIndex);
                }
            /* Fix this method, isn't working properly */
                else if ((GCost < GCosts[potentialNode]) && (shortestPath[potentialNode] == nullptr)) {
                    FCosts[potentialNode] = GCost + HCost;
                    GCosts[potentialNode] = GCost;

                    searchFrontier[potentialNode] = worldGeometry->indexToCell(closestIndex);
                }    
            }
        }
    }
}
std::list< Vector2<f32> > AStar::getPath() {
    std::list< Vector2<f32> > dummyPath;
/* Maybe there's no need to include this if */
    if (targetIndex < 0)  return dummyPath;    

    i32 nd = targetIndex;
    //std::cout << "The path is: " << nd << "\n";
    dummyPath.push_front(targetCell->getPosition());

    while ((nd != sourceIndex) && ( searchFrontier[nd] != 0))
    {
        nd =  shortestPath[nd]->getIndex();
        //std::cout << "The path is: " << nd << "\n";

        dummyPath.push_front(worldGeometry->indexToCell(nd)->getPosition());
    }

    return dummyPath;
}