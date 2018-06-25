#include <iostream>
#include <vector>
using namespace std;

class GameContents {
    int size; 
    vector<vector<char>> board;
    vector<pair<int, int>> starting_cells;
public:
    GameContents(int s);
    void initializeBoard();
    void printBoard();
};

GameContents::GameContents(int s) {
    size = s;
}

void GameContents::initializeBoard() {
    vector<vector<char>> initial_board(size, vector<char>('x'));
    board = initial_board;
}

int main() {
    GameContents mygame(10);



    return 0;
}
