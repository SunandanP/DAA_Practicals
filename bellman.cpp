#include <iostream>
#include <vector>
#define INF 99999

using namespace std;

class Edge{
public:
    int start;
    int end;
    int cost;

    Edge(){
        start = 0;
        end = 0;
        cost = 0;
    }

    Edge(int start, int end, int cost){
        this->start = start - 1;
        this->end = end - 1;
        this->cost = cost;
    }
};

class BellmanFord{
public:
    int vertices;
    vector<Edge> edges;
    vector<int> costs;
    vector<int> snapShot;
    int source;

    BellmanFord(vector<Edge> edges, int vertices, int source){
        this->source = source - 1;
        costs = vector<int>(vertices , INF);
        costs[this->source] = 0;

        snapShot = vector<int>(vertices , INF);
        snapShot[this->source] = 0;

        this->edges = edges;
        this->vertices = vertices;
    }

    int findEdge(int start, int end){
        for (int i = 0; i < edges.size(); i++) {
            Edge e = edges[i];
            if(e.start == start && e.end == end){
                return i;
            }
        }
        return -1;
    }

    // d[u] + cost(u,v) < d[v] : d[v] =
    void relax(int start, int end){
        if (costs[start] + edges[findEdge(start, end)].cost < costs[end]){
            costs[end] = costs[start] + edges[findEdge(start, end)].cost;
        }
    }

    void relaxEdges(int iterations){
        // performing n iterations
        for (int i = 1; i <= iterations; i++) {
            // Starting to look for negative cycles
            if(i == iterations - 1){
                cout<<"Monitoring for Negative Weight Cycles"<<endl;
            }
            // relax all edges one by one
            for (int j = 0; j < edges.size(); j++) {
                Edge e = edges[j];
                relax(e.start, e.end);
            }
            // display the table with changes if any
            displayTable(i);

            // if no changes are observed then terminate the algorithm
            if (checkSimilarities()){
                cout<<"The costs are stabilized hence correct costs are identified,"
                      " terminating the algorithm at iteration : "<<i<<endl;
                break;
            }
            // if values have changed
            else{
                // at n(th) iteration values have changed meaning negative edge cycle is detected.
                if (i == iterations){
                    cout<<"Negative cycle is detected.\nThe cost for nodes is changing, "
                          "hence above solution is Incorrect."
                          "\nThis problem cannot be solved by Bellman ford Algorithm."<<endl;
                }
                // store the changes into snapShot so that current and previous changes can be compared.
                else {
                    snapShot = costs;
                }
            }
        }
    }

    // to check if previous costs and current costs are varying or not
    bool checkSimilarities(){
        if (costs == snapShot){
            return true;
        }
        return false;
    }

    void displayTable(int it){
        (it != -1)? cout<<"Iteration : "<<it<<endl : cout<<"";
        cout<<"Label\t   Cost"<<endl;
        for (int i = 0; i < costs.size(); i++) {
            cout<<i<<"\t | "<<costs[i]<<endl;
        }
    }

    void runApp(){
        displayTable(-1);
        relaxEdges(vertices);
    }

};

int main() {
    vector<Edge> edges =
                        {Edge(1, 2, 6),
                          Edge(1, 3, 5),
                          Edge(1, 4, 5),
                          Edge(2, 5, -1),
                          Edge(3, 2, -2),
                          Edge(3, 5, 1),
                          Edge(4, 3, -2),
                          Edge(4, 6, -1),
                          Edge(5, 7, 3),
                          Edge(6, 7, 3)};
//            {Edge(2, 1 ,4),
//             Edge(2, 3, -6),
//             Edge(3, 4, 5),
//             Edge(4, 2, -2)};


    BellmanFord bellmanFord(edges, 7,1);
    bellmanFord.runApp();
    return 0;
}


/*
 *
 * OUTPUT FOR EDGE SET :
 *          {
 *           Edge(2, 1 ,4),
             Edge(2, 3, -6),
             Edge(3, 4, 5),
             Edge(4, 2, -2)
             };
 Label      Cost
0        | 99999
1        | 0
2        | 99999
3        | 99999
Iteration : 1
Label      Cost
0        | 4
1        | -3
2        | -6
3        | -1
Iteration : 2
Label      Cost
0        | 1
1        | -6
2        | -9
3        | -4
Monitoring for Negative Weight Cycles
Iteration : 3
Label      Cost
0        | -2
1        | -9
2        | -12
3        | -7
Iteration : 4
Label      Cost
0        | -5
1        | -12
2        | -15
3        | -10
Negative cycle is detected.
The cost for nodes is changing, hence above solution is Incorrect.
This problem cannot be solved by Bellman ford Algorithm.

OUTPUT FOR EDGESET : {
                          Edge(1, 2, 6),
                          Edge(1, 3, 5),
                          Edge(1, 4, 5),
                          Edge(2, 5, -1),
                          Edge(3, 2, -2),
                          Edge(3, 5, 1),
                          Edge(4, 3, -2),
                          Edge(4, 6, -1),
                          Edge(5, 7, 3),
                          Edge(6, 7, 3)
                          };
 Label      Cost
0        | 0
1        | 99999
2        | 99999
3        | 99999
4        | 99999
5        | 99999
6        | 99999
Iteration : 1
Label      Cost
0        | 0
1        | 3
2        | 3
3        | 5
4        | 5
5        | 4
6        | 7
Iteration : 2
Label      Cost
0        | 0
1        | 1
2        | 3
3        | 5
4        | 2
5        | 4
6        | 5
Iteration : 3
Label      Cost
0        | 0
1        | 1
2        | 3
3        | 5
4        | 0
5        | 4
6        | 3
Iteration : 4
Label      Cost
0        | 0
1        | 1
2        | 3
3        | 5
4        | 0
5        | 4
6        | 3
The costs are stabilized hence correct costs are identified, terminating the algorithm at iteration : 4
 */
