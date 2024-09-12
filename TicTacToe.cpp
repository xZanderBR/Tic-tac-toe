#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class TicTacToe {
public:
    int moves;
    char winner;
    /* Constructor */
    TicTacToe() {
        /* Initialize defaults here */
        moves = 0;
        winner = '\0';
    }

    /* This is your game board */
    vector<vector<char> > gameBoard
    {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };

    /* This prints your game board */
    void printGameBoard() const {
        for (int i = 0; i < gameBoard.size(); i++) {
            for (int j = 0; j < gameBoard[i].size(); j++) {
                cout << gameBoard[i][j] << " ";
            }
            cout << endl;
        }
    }

    /* Check if the game has a winner */
    char check_winner() const {
        /* Iterate through rows and columns */
        for (int i = 0; i < gameBoard.size(); i++) {
            if (gameBoard[i][0] == gameBoard[i][1] && gameBoard[i][1] == gameBoard[i][2]) {
                return gameBoard[i][0];
            } else if (gameBoard[0][i] == gameBoard[1][i] && gameBoard[1][i] == gameBoard[2][i]) {
                return gameBoard[0][i];
            }
        }

        /* Check diagonals */
        if (gameBoard[0][0] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][2]) {
            return gameBoard[0][0];
        } else if (gameBoard[0][2] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][0]) {
            return gameBoard[0][2];
        }

        return '\0';
    }

    /* Ask player to make a turn and update game board */
    void ask_player(const int moves) {
        char player = 'O';
        int pos;

        printGameBoard();

        if (moves == 0 || moves % 2 == 0) {
            player = 'X';
        }

        cout << "Player " << player << " Enter Position: ";
        cin >> pos;

        /* Check if the inputted position is valid */
        if ((pos > 9) || (pos < 1) || cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid position! Try again!\n";
            return;
        }

        modifyGameBoard(player, pos);
    }

    /* This method modifies the game board*/
    void modifyGameBoard(char player, int position) {
        int row, col;

        /* Parse row and column vals from raw position */
        if (position < 4) {
            row = 0;
            col = position - 1;
        } else if (position < 7) {
            row = 1;
            col = position - 4;
        } else {
            row = 2;
            col = position - 7;
        }

        /* Check if position is already occupied */
        if (gameBoard[row][col] == 'X' || gameBoard[row][col] == 'O') {
            cout << "Position already taken! Try again!\n";
            return;
        }

        /* Update position and increase moves */
        gameBoard[row][col] = player;
        moves++;
    }
};

int main() {
    auto game = TicTacToe(); // Create a new game object

    cout << "Welcome to TIC TAC TOE!\n";

    /* Loop the game until all moves were made or winner was found */
    while (game.moves < 9 && game.winner == '\0') {
        game.ask_player(game.moves);
        game.winner = game.check_winner();
    }

    game.printGameBoard();

    /* Print end status of match */
    if (game.winner != '\0') {
        cout << "Player " << game.winner << " Wins!!!\n";
    } else {
        cout << "Match Resulted in a Draw!!!\n";
    }

    cout << "GAME OVER";

    return 0;
}
