#include<iostream>
#include<vector>

using namespace std;

struct Edge{
    int index;
    int start;
    int end;
    int cost;

    Edge(int index, int start, int end, int cost){
        this->index = index;
        this->start = start;
        this->cost = cost;
        this->end = end;
    }

    Edge(){
        this->index = 0;
        this->start = 0;
        this->cost = 0;
        this->end = 0;
    }
};


class Solution{
    vector<string> labels;
    vector<int> distance;
    vector<Edge> edges;

    Solution(vector<string> labels, vector<int> distance, vector<Edge> cost){
        this->edges = cost;
        this->distance = distance;
        this->labels = labels;
    }
    

    void calculateCost(){
        int infinity = 9999999;
        for (int i = 0; i < distance.size(); i++){
            distance[i] = infinity;
        }

        for (int i = 0; i < edges.size(); i++){
            if(edges[i].start == 1 && distance[edges[i].index] < edges[i].cost){
                distance[edges[i].index] = edges[i].cost;
            }
            else{
                if (distance[i] + edges[i].cost < distance[i]){
                    distance[i] = distance[i] + edges[i].cost;
                }
            }
        }
        
        for (int i = 0; i < distance.size(); i++){
            cout<<
        }
        

    }


    

};

int main(int argc, char const *argv[])
{
    
    return 0;
}
