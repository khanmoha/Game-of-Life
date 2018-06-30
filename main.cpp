#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <sstream>

using namespace std;

// Prevents indexing out of range when looking for live neighbors
char safeSubscript(vector<vector<char>>& matrix, int row, int col) {
    int size = matrix[0].size();
    if (row < 0 || row > size - 1 || col < 0 || col > size - 1) return 'x';
    return matrix[row][col];
}

// Parse user input for starting live cells
pair<int, int> readPair(string coordinate) {
    vector<int> coordinate_vec;
    pair<int, int> coordinate_pair;
    string str;
    istringstream iss(coordinate);
    try {
        while (getline(iss, str, ',')) {
            try {
                coordinate_vec.push_back(stoi(str));
            }
            catch (...) {
                cerr << "Please only use integers for the coordinates, i.e. 1,2\n";
                exit(1);
            }
        }
        if (coordinate_vec.size() != 2) throw "Please separate input by commas\n";
    }
    catch (const char* msg) {
        cerr << msg;
        exit(1);
    }
    catch (...) {
        cerr << "Initial positions must be of form x,y where x and y are integers\n";
        exit(1);
    }

    coordinate_pair.first = coordinate_vec[0];
    coordinate_pair.second = coordinate_vec[1];
    return coordinate_pair;
}

class GameContents {
    int size; 
    int num_alive;
    vector<vector<char>> board;
public:
    GameContents(string s, vector<pair<int, int>> starting_cells);
    int returnLiveNeighbors(int row, int col);
    void printBoard();
    void runGame();
};

GameContents::GameContents(string s, vector<pair<int, int>> starting_cells) {
    try {
        size = stoi(s);
    }
    catch (...) {
        cerr << "Please input integers for side length of square board\n";
        exit(1);
    }
    num_alive = starting_cells.size();
    vector<vector<char>> initial_board(size, vector<char>(size, '.'));
    for (int i = 0; i < num_alive; ++i) {
        int row = starting_cells[i].first;
        int col = starting_cells[i].second;
        initial_board[row][col] = 'o';
    }
    board = initial_board;
}

int GameContents::returnLiveNeighbors(int row, int col) {
    int live_neighbors = 0;
    if (safeSubscript(board, row, col + 1) == 'o') ++live_neighbors;
    if (safeSubscript(board, row + 1, col) == 'o') ++live_neighbors;
    if (safeSubscript(board, row + 1, col + 1) == 'o') ++live_neighbors;
    if (safeSubscript(board, row, col - 1) == 'o') ++live_neighbors;
    if (safeSubscript(board, row - 1, col) == 'o') ++live_neighbors;
    if (safeSubscript(board, row - 1, col - 1) == 'o') ++live_neighbors;
    if (safeSubscript(board, row + 1, col - 1) == 'o') ++live_neighbors;
    if (safeSubscript(board, row - 1, col + 1) == 'o') ++live_neighbors;
    return live_neighbors;
}

void GameContents::printBoard() {
    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            cout << board[row][col] << " ";
        }
        cout << endl;
    }
}

void GameContents::runGame() {
    string next_step;
    int live_neighbors = 0; //Life dependant on status of neighbors
    vector<vector<char>> next_board = board;
    while (num_alive > 0) {
        this->printBoard();
        for (int row = 0; row < size; ++row) {
            for (int col = 0; col < size; ++col) {
                live_neighbors = returnLiveNeighbors(row, col);
                if (board[row][col] == 'o') { //Alive cell
                    if (live_neighbors < 2 || live_neighbors > 3) {
                        next_board[row][col] = '.';
                        --num_alive;
                    }
                }
                else { //Dead cell
                    if (live_neighbors == 3) {
                        next_board[row][col] = 'o';
                        ++num_alive;
                    }
                }
            }
        }
        board = next_board;
        cout << "Hit enter for next step";
        getline(cin, next_step);
    }
}

int main() {
    string coordinate;
    vector<pair<int, int>> starting_cells;
    string side_len;
    cout << "Please enter side length of square game board: ";
    getline(cin, side_len);
    cout << "Please enter initial live cells in the form x,y (each followed by an ENTER):\n";
    cout << "When you are finished, hit ENTER again\n";
    while (getline(cin, coordinate)) {
        if (coordinate == "") {
            break;
        }
        starting_cells.push_back(readPair(coordinate));
    }
    GameContents mygame(side_len, starting_cells);
    mygame.runGame();
    return 0;
}
