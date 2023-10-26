#include <iostream>
#include <vector>
using namespace std;

class Block{
public:
    int occupancy;

    Block(){
        occupancy = 0;
    }

};

class Config{
public:
    int size;

    vector<vector<Block>> grid;

    Config(int size){
        this->size = size;
        vector<Block> temp;
        for (int i = 0; i < size; i++) {
            temp.push_back(Block());
        }

        for (int i = 0; i < size; i++) {
            grid.push_back(temp);
        }
    }

    Config() {
        size = 0;
    }

    void printOccupancy(){
        cout<<"X\t";
        for (int i = 0; i < size; i++) {
            cout<<i<<"\t";
        }
        cout<<endl;
        for (int i = 0; i < size; i++) {
            cout<<i<<"\t";
            for (int j = 0; j < size; j++) {
                cout<<grid[i][j].occupancy<<"\t";
            }
            cout<<endl;
        }cout<<endl;
    }
};

struct Position{
    int x;
    int y;

    Position(int x, int y){
        this->x = x;
        this->y = y;
    }
};

class Solution{
public:
    Config config;
    vector<Config> solutions;
    Solution(int size){
        config = Config(size);
    }

    bool isSafe(Position pos){
        for (int i = 0; i < config.size; i++) {
            // Horizontal Check
            if (config.grid[i][pos.y].occupancy > 0){
                return false;
            }

            // Vertical check
            if (config.grid[pos.x][i].occupancy > 0){
                return false;
            }
        }

        // Upper left
        for (int i = pos.x, j = pos.y; i >= 0 && j >= 0; i--, j--) {
            if (config.grid[i][j].occupancy > 0){
                return false;
            }
        }

        // Upper right
        for (int i = pos.x, j = pos.y; i >= 0 && j < config.size; i--, j++) {
            if (config.grid[i][j].occupancy > 0){
                return false;
            }
        }

        // lower left
        for (int i = pos.x, j = pos.y; i < config.size && j >= 0; i++, j--) {
            if (config.grid[i][j].occupancy > 0){
                return false;
            }
        }

        // Upper left
        for (int i = pos.x, j = pos.y; i < config.size  && j < config.size; i++, j++) {
            if (config.grid[i][j].occupancy > 0){
                return false;
            }
        }
        return true;
    }


    void saveState(){
        solutions.push_back(config);
    }

    void placeQueen(Position pos, int queen){
        config.grid[pos.x][pos.y].occupancy = queen;
    }

    void unplaceQueen(Position pos){
        config.grid[pos.x][pos.y].occupancy = 0;
    }

    void placeNQueens(int row, int queen){
        if(row == config.size){
            saveState();
            return;
        }

        for (int i = 0; i < config.size; i++) {
            if(isSafe(Position(row, i))){
                placeQueen(Position(row, i), queen);
                placeNQueens(row+1, queen + 1);
                unplaceQueen(Position(row,i));
            }
        }
    }

    void runApp(){
        placeNQueens(0,1);
        cout<<"Number of solutions : "<<solutions.size()<<endl;
        for (int i = 0; i < solutions.size(); i++) {
            solutions[i].printOccupancy();
        }
    }
};


int main() {
    Solution solution(10);
    solution.runApp();
    return 0;
}
