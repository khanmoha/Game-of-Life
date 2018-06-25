#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <sstream>
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
    vector<vector<char>> initial_board(size, vector<char>(size, '.'));
    for (size_t i = 0; i < starting_cells.size(); ++i) {
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

pair<int, int> readPair(string coordinate) {
    vector<int> coordinate_vec;
    pair<int, int> coordinate_pair;
    istringstream iss(coordinate);
    for (int i = 0; i < 2; ++i) {
        string str;
        int num;
        iss >> str;
        if (str.back() == ',') {
            str.pop_back();
        }
        num = stoi(str);
        coordinate_vec.push_back(num);
    }
    coordinate_pair.first = coordinate_vec[0];
    coordinate_pair.second = coordinate_vec[1];
    return coordinate_pair;
}

int main() {
    string coordinate;
    vector<pair<int, int>> starting_cells;
    cout << "Please enter you starting positions in the form x, y (with a space after the comma), each followed by an ENTER:\n";
    cout << "When you are finished, hit ENTER again\n";
    while (getline(cin, coordinate)) {
        if (coordinate == "") {
            break;
        }
        starting_cells.push_back(readPair(coordinate));
    }
    GameContents mygame(10, starting_cells);
    mygame.printBoard();


    return 0;
}
