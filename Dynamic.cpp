#include<iostream>
#include <vector>

using namespace std;

class Array{
    public:
    vector<vector<int>> array;
    int items;
    int capacity;

    

    Array(int items, int capacity){
        this->items = items;
        this->capacity = capacity;

        vector<int> temp(capacity + 1);

        for (int i = 0; i <= capacity + 1; i++){
            temp[i] = 0;
        }

        for (int i = 0; i < items; i++){
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

class Container{
    public:

    int index;
    int profit;
    int weight;

    Container(){
        index = 0;
        profit = 0;
        weight = 0;
    }

    Container(int index, int profit, int weight){
        this->index = index;
        this->profit = profit;
        this->weight = weight;
    }

    void printContainer(){
        cout<<"index : "<<index<<"\tprofit : "<<profit<<"\tweight : "<<weight<<endl;
    }

};

class Solution{
public:
    Array *table;

    vector<Container> items;

    void printSolution(){
        cout<<"Table : "<<endl;
        table->printArray();

    }


    Solution(vector<Container> items, int capacity, int totalItems){
        this->items = items;
        table = new Array(totalItems, capacity);
    }

    int getMax(int first, int second){
        return (first > second)? first : second;
    }


    int searchByProfit(int profit){
        for (int i = 0; i < items.size(); i++) {
            if (profit == items[i].profit){
                return i;
            }
        }
        return -1;
    }


    void fillTable(){
        for (int i = 1; i < table->items; i++) {
            for (int j = 1; j <= table->capacity; j++) {
                if (items[i].weight > j){
                    table->array[i][j] = table->array[i - 1][j];
                }
                else{
                    if(items[i].profit + table->array[i - 1][j - items[i].weight] > table->array[i - 1][j]){
                        table->array[i][j] = items[i].profit + table->array[i - 1][j - items[i].weight];
                    } else {
                        table->array[i][j] = table->array[i - 1][j];
                    }
                }
            }
        }
    }
};



int main()
{
    vector<Container> containers;
    containers.push_back(Container(0,2,3));
    containers.push_back(Container(1,3,4));
    containers.push_back(Container(2,4,5));
    containers.push_back(Container(3,5,6));

    Solution solution(containers, 7, 4);
    solution.fillTable();
    solution.printSolution();
    return 0;
}
