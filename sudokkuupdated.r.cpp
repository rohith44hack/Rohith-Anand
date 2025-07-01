#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>  // Needed for string
#include <cstdlib> // For atoi
using namespace std;

#define N 9
#define EMPTY 0
#define REMOVED_CELLS 40

int board[N][N];

void printBoard() {
    cout << "\n ";
    for (int j = 0; j < N; j++) {
        cout << j + 1 << " ";
        if ((j + 1) % 3 == 0 && j != N - 1) cout << "| ";
    }
    cout << "\n -------------------------\n";

    for (int i = 0; i < N; i++) {
        cout << i + 1 << "  | ";
        for (int j = 0; j < N; j++) {
            if (board[i][j] == EMPTY)
                cout << ". ";
            else
                cout << board[i][j] << " ";
            if ((j + 1) % 3 == 0 && j != N - 1) cout << "| ";
        }
        cout << endl;
        if ((i + 1) % 3 == 0 && i != N - 1) {
            cout << "   -------------------------\n";
        }
    }
}

bool isValid(int row, int col, int num) {
    for (int x = 0; x < N; x++) {
        if (board[row][x] == num || board[x][col] == num)
            return false;
    }

    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[startRow + i][startCol + j] == num)
                return false;

    return true;
}

bool isComplete() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (board[i][j] == EMPTY)
                return false;
    return true;
}

void shuffle(int array[], int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

bool fillBoard() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == EMPTY) {
                int nums[9] = {1,2,3,4,5,6,7,8,9};
                shuffle(nums, 9);

                for (int k = 0; k < 9; k++) {
                    int num = nums[k];
                    if (isValid(i, j, num)) {
                        board[i][j] = num;
                        if (fillBoard())
                            return true;
                        board[i][j] = EMPTY;
                    }
                }

                return false;
            }
        }
    }
    return true;
}

void removeCells() {
    int count = REMOVED_CELLS;
    while (count > 0) {
        int i = rand() % N;
        int j = rand() % N;

        if (board[i][j] != EMPTY) {
            board[i][j] = EMPTY;
            count--;
        }
    }
}

void generateSudoku() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = EMPTY;

    srand((unsigned int)time(NULL));
    fillBoard();
    removeCells();
}

bool solveSudoku() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == EMPTY) {
                for (int num = 1; num <= 9; num++) {
                    if (isValid(i, j, num)) {
                        board[i][j] = num;
                        if (solveSudoku())
                            return true;
                        board[i][j] = EMPTY;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

int main() {
    int row, col, num;
    string input;

    cout << "=== Sudoku Game (C++) ===\n";
    cout << "Type 'solve' at any time to auto-complete the puzzle.\n";

    generateSudoku();

    while (!isComplete()) {
        printBoard();
        cout << "\nEnter row (1-9), column (1-9), and number (1-9) to place (e.g. 3 4 5), or type 'solve': ";

        cin >> input;

        if (input == "solve") {
            if (solveSudoku()) {
                printBoard();
                cout << "\n? Puzzle solved automatically!\n";
            } else {
                cout << "\n? Could not solve the puzzle.\n";
            }
            break;
        } else {
            // convert input to int with atoi to avoid stoi error
            row = atoi(input.c_str());
            cin >> col >> num;
        }

        row--;
        col--;

        if (row < 0 || row >= 9 || col < 0 || col >= 9 || num < 1 || num > 9) {
            cout << "? Invalid input. Please enter numbers between 1 and 9.\n";
            continue;
        }

        if (board[row][col] != EMPTY) {
            cout << "? Cell already filled. Choose an empty cell.\n";
            continue;
        }

        if (isValid(row, col, num)) {
            board[row][col] = num;
            cout << "? Placed successfully.\n";
        } else {
            cout << "? Invalid move. Number violates Sudoku rules.\n";
        }
    }

    if (isComplete()) {
        printBoard();
        cout << "\n?? Congratulations! You completed the Sudoku puzzle!\n";
    }

    return 0;
}


