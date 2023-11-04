#include <iostream>
#include <vector>
# define INF 99999
using namespace std;

class Node{
public:

    int currentCost;
    int previousCost;
    vector<int> path;
    vector<vector<int>> matrix;
    int totalPlaces;
    int nodeID;

    Node(){
        currentCost = 0;
        previousCost = 0;
        totalPlaces = 0;
        nodeID = 0;
    }

    Node(int currentCost, int previousCost, int totalPlaces, int nodeID, vector<vector<int>> matrix, vector<int> path){
        this->nodeID = nodeID;
        this->currentCost = currentCost;
        this->previousCost = previousCost;
        this->totalPlaces = totalPlaces;
        this->matrix = matrix;
        this->path = path;
    }

    //reducing rows or columns by finding the min out of the set and subtracting it from everybody except for infinity
    int reduce(int index, bool isRow){
        int min = INF;
        // row reduction
        if (isRow){
            //finding row minimum
            for (int i = 0; i < totalPlaces; i++) {
                if(min > matrix[index][i]){
                    min = matrix[index][i];
                }
            }
            // subtracting row minimum from elements
            if(min != INF){
                for (int i = 0; i < totalPlaces; i++) {
                    if( matrix[index][i] != INF)
                        matrix[index][i] -= min;
                }
            }
        }
        //column reduction
        else{
            //finding column minimum
            for (int i = 0; i < totalPlaces; i++) {
                if(min > matrix[i][index]){
                    min = matrix[i][index];
                }
            }
            // subtracting column minimum from column elements
            if(min != INF){
                for (int i = 0; i < totalPlaces; i++) {
                    if( matrix[i][index] != INF)
                        matrix[i][index] -= min;
                }
            }
        }
        // returning the cost of reduction for the row, 0 if all the values are infinity
        return (min == INF)? 0 : min;
    }

    void reduceMatrix(){
        int cost = 0;
        // Row reduction cost increment
        for (int i = 0; i < totalPlaces; i++) {
            cost += reduce(i, true);
        }
        // Column reduction cost increment
        for (int i = 0; i < totalPlaces; i++) {
            cost += reduce(i, false);
        }

        // incrementing the current cost with reduction cost
        currentCost += cost;
    }

    // incrementing current cost with previous cost and cost to visit from selected place to some other place
    // formula : cost = previousCost of reduction + cost of reduction + cost(a,b)
    void assignCosts(int start, int end, Node node){
        currentCost += previousCost + node.matrix[start][end];
    }

    // for marking starting index row, ending index column as infinity
    // and as we should not visit the original place so c(curr, 0) = INF as well
    void initNode(int start, int end){
        for (int i = 0; i < totalPlaces; i++) {
            matrix[start][i] = INF;
            matrix[i][end] = INF;
        }

        matrix[end][0] = INF;
    }

    void printMatrix(){
        cout<<"Node id : "<<nodeID<<" "<<endl;
        cout<<"cost : "<<currentCost<<" "<<endl;
        cout<<"Path : ";
        for (int i = 0; i < path.size(); i++) {
            cout<<path[i]<<" ";
        }
        cout<<endl;
        for (int i = 0; i < totalPlaces; i++) {
            for (int j = 0; j < totalPlaces; j++) {
                cout<<matrix[i][j]<<"\t\t  ";
            }
            cout<<endl;
        }
    }
};

class TSP{
    int upperBound;
    vector<Node> Nodes;
    Node root;
    vector<int> visited;

public:

    TSP(Node node){
        root = node;
        upperBound = INF;
        root.reduceMatrix();
        root.path.push_back(0);
    }

    // to apply Least cost branch and bound we need to find the node with the least cost from generated nodes
    int getLeastNode(){
        int min = INF, index;
        for (int i = 0; i < Nodes.size(); i++) {
            if(min > Nodes[i].currentCost && !isVisited(Nodes[i])){
                min = Nodes[i].currentCost;
                index = i;
            }
        }

        return index;
    }

    // to find a particular node index in the Nodes vector
    int getIndex(Node node){
        for (int i = 0; i < Nodes.size(); i++) {
            if(node.currentCost == Nodes[i].currentCost && node.matrix == Nodes[i].matrix){
                return i;
            }
        }
        return -1;
    }

    // if node has already covered the mentioned destination
    // (contained in path variable) the function will return true
    // false otherwise
    bool alreadyDone(Node node, int dest){
        for (int i = 0; i < node.path.size(); i++) {
            if (dest == node.path[i]){
                return true;
            }
        }
        return false;
    }

    // if node has been already explored by recursive call then returns true
    bool isVisited(Node node){
        for(int ele : visited){
            if (ele == getIndex(node))
                return true;
        }
        return false;
    }

    // Purge the nodes which have cost higher than the upperbound;
    void purgeNodes(){
        vector<Node> temp;
        for (int i = 0; i < Nodes.size(); i++) {
            if(Nodes[i].currentCost <= upperBound){
                temp.push_back(Nodes[i]);
            }
        }
        Nodes = temp;
    }

    // Purge the nodes which do not contain a complete path
    void cleanNodes(){
        vector<Node> temp;
        for(int i = 0; i < Nodes.size(); i++){
            Node e = Nodes[i];
            if (e.path.size() == root.totalPlaces){
                temp.push_back(e);
            }
        }
        Nodes = temp;
    }

    // recursive function to explore nodes in least cost manner
    void tracePath(Node node){
        // Base case
        if(node.path.size() == node.totalPlaces){
            if (upperBound > node.currentCost){
                upperBound = node.currentCost;
            }
            purgeNodes();
            return;
        }

        // explore all possible nodes
        for (int i = 0; i < root.totalPlaces; i++) {
            // if path between current node and node chosen for exploration exists
            // and the node to be explored hasn't visited current node
            if (root.matrix[node.nodeID][i] != INF && !alreadyDone(node, i)){
                Node temp(0,node.currentCost, node.totalPlaces, i, node.matrix, node.path);
                temp.initNode(node.nodeID, i);
                temp.assignCosts(node.nodeID, i,root);
                temp.reduceMatrix();
                temp.path.push_back(i);
                Nodes.push_back(temp);
            }
        }

        // once explored mark it as explored by pushing it into the visited vector
        if(getIndex(node) != -1)
            visited.push_back(getIndex(node));

        //recursive call if least node exists which hasn't been visited
        if (getLeastNode() > -1)
            tracePath(Nodes[getLeastNode()]);
    }

    void printSolutions(){
        for (int i = 0; i < Nodes.size(); i++) {
            Node e = Nodes[i];
            cout<<"Path : ";
            for (int j = 0; j < e.path.size(); j++) {
                cout<<e.path[j]<<((j < e.path.size() - 1)? " -> " : "");
            }
            cout<<endl;
            cout<<"Cost is : "<<e.currentCost<<endl;
        }
    }

    // run the main application, clean the nodes and print the solution
    void runApp() {
        Node node = root;
        tracePath(node);
        cleanNodes();
        printSolutions();
    }
};

int main() {
    vector<vector<int>> matrix = {
            {INF, 20, 30, 10, 11 },
            { 15, INF, 16, 4, 2},
            { 3, 5, INF, 2, 4},
            { 19, 6, 18, INF, 3},
            {16, 4, 7, 16, INF}
    };
    vector<int> path = {};
    Node node(0,0,5,0,matrix,path);
    TSP tsp(node);
    tsp.runApp();
    return 0;
}
/*
OUTPUT
Path : 0 -> 3 -> 1 -> 4 -> 2
Cost is : 28
*/
