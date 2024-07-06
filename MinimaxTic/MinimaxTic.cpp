#include <iostream>
#include <limits.h>
using namespace std;

const int SIZE = 3;
char board[SIZE][SIZE];
char player = 'X', opponent = 'O';


// Function to print the board
void drawBoard() {
    
    for (int i = 0; i < SIZE * 4; i++) {
        cout << "-";
    }
    cout << "-\n";

    for (int i = 0; i < SIZE; i++) {
        cout << "| ";
        for (int j = 0; j < SIZE; j++) {
            cout << board[i][j] << " | ";
        }
        cout << "\n";
        for (int i = 0; i <= SIZE * 4; i++) {
            cout << "-";
        }
        cout << "-\n";
    }
}

// Function to check if there are any moves left on the board
bool isMovesLeft() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return true;
    return false;
}

// Evaluation function
int evaluate() {

    // Checking for Rows for X or O victory
    for (int row = 0; row < SIZE; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == player)
                return +10;
            else if (board[row][0] == opponent)
                return -10;
        }
    }

    // Checking for Columns for X or O victory
    for (int col = 0; col < SIZE; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == player)
                return +10;
            else if (board[0][col] == opponent)
                return -10;
        }
    }

    // Checking for Diagonals for X or O victory
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == player)
            return +10;
        else if (board[0][0] == opponent)
            return -10;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == player)
            return +10;
        else if (board[0][2] == opponent)
            return -10;
    }

    // Else if none of them have won then return 0
    return 0;
}

// Minimax algorithm
int minimax(int depth, bool isMax) {
    int score = evaluate();

    // If Maximizer has won the game return his/her evaluated score
    if (score == 10)
        return score - depth;

    // If Minimizer has won the game return his/her evaluated score
    if (score == -10)
        return score + depth;

    // If there are no more moves and no winner then it is a tie
    if (!isMovesLeft())
        return 0;

    // If this maximizer's move
    if (isMax) {
        int best = INT_MIN;

        // Traverse all cells
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                // Check if cell is empty
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    // Make the move
                    char backup = board[i][j];
                    board[i][j] = player;

                    // Call minimax recursively and choose the maximum value
                    best = max(best, minimax(depth + 1, !isMax));

                    // Undo the move
                    board[i][j] = backup;
                }
            }
        }
        return best;
    }

    // If this minimizer's move
    else {
        int best = INT_MAX;

        // Traverse all cells
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                // Check if cell is empty
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    // Make the move
                    char backup = board[i][j];
                    board[i][j] = opponent;

                    // Call minimax recursively and choose the minimum value
                    best = min(best, minimax(depth + 1, !isMax));

                    // Undo the move
                    board[i][j] = backup;
                }
            }
        }
        return best;
    }
}


// Find the best possible move for the computer
pair<int, int> findBestMove() {
    int bestVal = INT_MIN;
    pair<int, int> bestMove = { -1, -1 };

    // Traverse all cells, evaluate minimax function for all empty cells, and return the cell with optimal value.
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // Check if cell is empty
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                // Make the movex
                char backup = board[i][j];
                board[i][j] = player;

                // Compute evaluation function for this move.
                int moveVal = minimax(0, false);

                // Undo the move
                board[i][j] = backup;

                // If the value of the current move is more than the best value, then update best
                if (moveVal > bestVal) {
                    bestMove = { i, j };
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

bool placeMarker(int slot, char marker) {
    int row = (slot - 1) / SIZE;
    int col = (slot - 1) % SIZE;

    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = marker;
        return true;
    }
    return false;
}

int winner() {
    int score = evaluate();
    if (score == 10)
        return 1;
    else if (score == -10)
        return 2;
    return 0;
}

void game() {
    drawBoard();
    int player_won;
    for (int i = 0; i < SIZE * SIZE; i++) {
        if ((i % 2) == 0) {
            cout << "Player's turn. Enter your slot: ";
            int slot;
            cin >> slot;

            if (slot < 1 || slot > 9) {
                cout << "Invalid slot! Choose another slot!\n";
                i--;
                continue;
            }

            if (!placeMarker(slot, opponent)) {
                cout << "This slot is occupied! Choose another slot!\n";
                i--;
                continue;
            }
        }
        else {
            cout << "Computer's turn.\n";
            pair<int, int> bestMove = findBestMove();
            placeMarker(bestMove.first * SIZE + bestMove.second + 1, player);
        }

        drawBoard();

        player_won = winner();
        if (player_won == 1) {
            cout << "Computer wins!\n";
            break;
        }
        else if (player_won == 2) {
            cout << "Player wins!\n";
            break;
        }

        if (!isMovesLeft()) {
            cout << "It's a tie!\n";
            break;
        }
    }
}

int main() {

    char mark = 0;
    for (int row = 0; row < SIZE; row++) {

        for (int column = 0; column < SIZE; column++) {

            board[row][column] = '0' + (mark + 1) % 10;

            mark++;
        }
    }

    drawBoard();

    game();
    return 0;
}
