#include <iostream>
#include <vector>
using namespace std;

struct Object{
    int profit;
    int weight;

    Object(){
        profit = 0;
        weight = 0;
    }

    Object(int profit, int weight){
        this->profit = profit;
        this->weight = weight;
    }
};


class Util{
public:
    vector<Object> items;
    int capacity;
    vector<vector<int>> array;

    Util(){
        capacity = 0;
    }

    Util(vector<Object> items, int capacity){
        this->items = items;
        this->capacity = capacity;

        vector<int> temp(capacity + 1, 0);
        array = vector<vector<int>>(items.size() + 1, temp);
    }

    void printArray(){
        cout<<"X";
        for(int i = 0; i < capacity + 1; i++){
            cout<<"\t"<<i;
        }
        cout<<endl;
        for(int i = 0; i <= items.size(); i++){
            cout<<i<<"\t";
            for(int j = 0; j <= capacity; j++){
                cout<<array[i][j]<<"\t";
            }
            cout<<endl;
        }
    }
};

class DynamicKnapsack{
public:
    Util util;
    vector<int> selection;

    DynamicKnapsack(Util util){
        this->util = util;
    }

    void fillTable(){
        for(int i = 0; i <= util.items.size(); i++){
            for(int j = 0; j <= util.capacity; j++){
                if(i == 0 || j == 0){
                    util.array[i][j] = 0;
                }
                else if(util.items[i - 1].weight <= j){
                    util.array[i][j] = max(util.array[i - 1][j], util.items[i - 1].profit + util.array[i - 1][j - util.items[i - 1].weight]);
                }
                else {
                    util.array[i][j] = util.array[i - 1][j];
                }
            }
        }

    }

    void traceBack(int i, int j){
        if(i == 0){
            return;
        }

        if(util.array[i - 1][j] < util.array[i][j]){
            selection.push_back(i);
            traceBack(i - 1, j - util.items[i - 1].weight);
        }
        else {
            traceBack(i - 1, j);
        }
    }

    void traceBackHandler(){
        traceBack(util.items.size() , util.capacity);
        cout<<"Selection is : ";
        for(auto x : selection){
            cout<<x<<" ";
        }
    }

    void runApp(){
        fillTable();
        util.printArray();
        traceBackHandler();
    }

};

int main(){
    vector<Object> items = {
            Object(10,2),
            Object(5,3),
            Object(15,5),
            Object(7,7),
            Object(6,1),
            Object(18,4),
            Object(3,1),
    };
    Util util(items, 5);
    DynamicKnapsack dk(util);
    dk.runApp();
    return 0;

}
