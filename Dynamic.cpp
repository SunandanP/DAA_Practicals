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

        vector<int> temp(capacity);

        for (int i = 0; i <= capacity; i++){
            temp[i] = 0;
        }

        for (int i = 0; i <= items; i++){
            array.push_back(temp);
        }  
    }


    void init(){
        for (int i = 0; i < array.size(); i++){
            array[i][0] = 0;
        }

        for (int i = 0; i < array[0].size(); i++){
            array[0][i] = 0;
        }

    }

    void printArray(){
        for (int i = 0; i < array.size(); i++){
            for(int j = 0; j < array[0].size(); j++){
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

};

class calculator{
    Array array;
    Container *containers;

    calculator(){}

    calculator(Array array, Container container[]){

    }

};

int main()
{
    Array array(4, 8);
    array.init();
    array.printArray();
    return 0;
}
