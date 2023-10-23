#include<iostream>
#include <vector>

using namespace std;

class Util{
public:
    vector<vector<int>> array;
    int items;
    int capacity;

    Util(){
        items = 0;
        capacity = 0;
    }

    Util(int items, int capacity){
        this->items = items;
        this->capacity = capacity;

        vector<int> temp(capacity + 1);

        for (int i = 0; i <= capacity + 1; i++){
            temp[i] = 0;
        }

        for (int i = 0; i <= items; i++){
            array.push_back(temp);
        }
    }



    void printArray(){
        cout<<"X"<<"\t";
        for(int i = 0; i < array[0].size(); i++)
            cout<<i<<"\t";
        cout<<endl;
        int count = 0;
        for (int i = 0; i < array.size(); i++){
            for(int j = 0; j < array[0].size(); j++){
                if(count == i){
                    cout<<count<<"\t";
                    count++;
                }
                cout<<array[i][j]<<"\t";
            }
            cout<<endl;
        }
    }
};

class Item{
public:

    int profit;
    int weight;

    Item(){

        profit = 0;
        weight = 0;
    }

    Item(int profit, int weight){
        this->profit = profit;
        this->weight = weight;
    }

    void printContainer(){
        cout<<"\tprofit : "<<profit<<"\tweight : "<<weight<<endl;
    }

};

class Solution{
public:
    Util util;
    vector<int> selection;
    vector<Item> items;

    void printSolution(){
        cout<<"Table : "<<endl;
        util.printArray();
    }


    Solution(vector<Item> items, int capacity, int totalItems){
        this->items = items;
        util = Util(totalItems, capacity);
    }

    void fillTable(){
        for (int i = 0; i <= items.size(); i++) {
            for (int weight= 0; weight <= util.capacity; weight++) {
                //item or weight doesn't exist
                if (i == 0 || weight == 0){
                    util.array[i][weight] = 0;
                }
                // if there is a scope of adding some weight to the knapsack
                //weight being, the weight under consideration 0, 1, 2, 3...n
                else if(items[i - 1].weight <= weight){
                    util.array[i][weight] = max(util.array[i - 1][weight], 
                                                util.array[i - 1][weight - items[i-1].weight] + items[i - 1].profit);
                }
                // if there is no scope of adding anymore weight
                else {
                    util.array[i][weight] = util.array[i - 1][weight];
                }
            }
        }

    }

    void traceBack(int i, int j) {
        // item doesn't exist
        if (i == 0){
            return;
        }

        // element under consideration is bigger than the one above then subtract the items weight from column weight and jump to that index
        else if(util.array[i][j] > util.array[i - 1][j]){
            selection.push_back(i+1);
            traceBack(i - 1, j - items[i].weight);
        }
        
        // vertical traceback
        else{
            traceBack(i - 1, j);
        }
    }

    void traceBackHandler(){
        traceBack(util.items - 1 , util.capacity - 1);
        cout<<"Selected items are :\n";
        for (int i = 0; i < selection.size(); i++) {
            cout<<selection[i]<<" ";
        }
        cout<<endl;
    }


};

void runApp(){
    vector<Item> items;
    
    items.push_back(Item(1, 2));
    items.push_back(Item(2, 3));
    items.push_back(Item(5, 4));
    items.push_back(Item(6, 5));

    Solution solution(items, 8, 4);
    
    solution.fillTable();
    solution.printSolution();
    solution.traceBackHandler();
}


int main()
{
    runApp();
    return 0;
}


