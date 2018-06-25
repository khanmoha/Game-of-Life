#include <iostream>
#include <vector>
#include <utility>
using namespace std;

class GameContents {
    int size; 
    vector<vector<char>> board;
    //vector<pair<int, int>> starting_cells;
public:
    GameContents(int s, vector<pair<int, int>> starting_cells);
    void printBoard();
};

GameContents::GameContents(int s, vector<pair<int, int>> starting_cells) {
    size = s;
    vector<vector<char>> initial_board(size, vector<char>(size, '+'));
    for (int i = 0; i < starting_cells.size(); ++i) {
        int row = starting_cells[i].first;
        int col = starting_cells[i].second;
        initial_board[row][col] = 'o';
    }
    board = initial_board;
}

void GameContents::printBoard() {
    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            cout << board[row][col] << " ";
        }
        cout << endl;
    }
}

int main() {
    pair<int, int> pos1(1, 2);
    pair<int, int> pos2(1, 3);
    vector<pair<int, int>> starting_cells = { pos1, pos2 };
    GameContents mygame(10, starting_cells);
    mygame.printBoard();


    return 0;
}
