//
// Created by tiago on 04/05/2023.
//

#include <iostream>

using namespace std;

unsigned int tspBTRec(const unsigned int **dists, unsigned int n, unsigned int path[], unsigned int min, unsigned int curCost,unsigned int curPath[], unsigned int i, unsigned int curPathSize, unsigned int visited[], bool ended) {

    if(visited[i] == 0){
        visited[i] = 1;
        if(curPathSize == (n-1)){
            visited[i] = 0;
            int sum = tspBTRec(dists,n,path,min,curCost+dists[i][0],curPath,0,curPathSize,visited, true);
            if(sum < min){
                min = sum;
                path[curPathSize] = i;
            }
            return min;
        }
    }
    else if(i==0 && ended){
        min = (curCost < min) ? curCost : min;
        return min;
    }
    else return min;

    unsigned int localCost;

    for(int j = 0; j < n; j++){
        if(i==j) continue;
        localCost=tspBTRec(dists,n,path,min,curCost+dists[i][j],curPath,j,curPathSize+1, visited, false);
        if(localCost < min){
            min = localCost;
            path[curPathSize] = i;
        }
    }
    visited[i] = 0;
    return min;
}

unsigned int tspBT(const unsigned int **dists, unsigned int n, unsigned int path[]) {
    unsigned int visited[n];
    unsigned int curPath[n];
    for(int i = 0; i < n; i++){
        visited[i]=0;
        curPath[i] = 0;
        path[i] = 0;
    }

    return tspBTRec(dists,n,path,INT_MAX,0, curPath, 0, 0, visited, false);
}
