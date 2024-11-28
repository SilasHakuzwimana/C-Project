#include <iostream> 
#include <vector>
#include <algorithm>
#include<string>
using namespace std;
vector<string> board; // Game board
int scoreX = 0, scoreO = 0, ties = 0; // Score trackers
// Function to initialize the board 
void initializeBoard() { 
board = {"-", "-", "-", "-", "-", "-", "-", "-", "-"}; 
}
// Function to display the game board
void printBoard() { 
cout << "\n"; 
cout << " " << board[0] << " | " << board[1] << " | " << board[2] << "\n"; 
cout << "---+---+---\n"; 
cout << " " << board[3] << " | " << board[4] << " | " << board[5] << "\n"; 
cout << "---+---+---\n";
cout << " " << board[6] << " | " << board[7] << " | " << board[8] << "\n"; 
cout << "\n"; 
} 
// Function to display game instructions 
void displayInstructions() { 
cout << "Welcome to Tic-Tac-Toe!\n"; 
cout << "Players take turns choosing positions (1-9) to mark their symbol (X or O).\n";
cout << "The goal is to get three in a row horizontally, vertically, or diagonally.\n";
cout << "Here is the layout of the board:\n"; 
cout << " 1 | 2 | 3\n"; 
cout << "---+---+---\n"; 
cout << " 4 | 5 | 6\n"; 
cout << "---+---+---\n"; 
cout << " 7 | 8 | 9\n"; 
cout << "\nLet's begin!\n"; 
} 
// Function to display the score 
void displayScore() { 
cout << "Scoreboard:\n"; 
cout << "Player X: " << scoreX << " wins\n"; 
cout << "Player O: " << scoreO << " wins\n"; 
cout << "Ties: " << ties << "\n\n"; 
} 
// Function to handle a player's turn 
void takeTurn(string player) { 
cout << player << "'s turn. Choose a position (1-9): "; 
int position; 
cin >> position; 
position -= 1; 
while (position < 0 || position > 8 || board[position] != "-") { 
cout << "Invalid input or position already taken. Choose a different position: "; 
cin >> position; 
        position -= 1; 
    } 
    board[position] = player; 
    printBoard(); 
} 
 
// Function to check the game's status 
string checkGameOver() { 
    // Check for a win 
    if ((board[0] == board[1] && board[1] == board[2] && board[0] != "-") || 
        (board[3] == board[4] && board[4] == board[5] && board[3] != "-") || 
        (board[6] == board[7] && board[7] == board[8] && board[6] != "-") || 
        (board[0] == board[3] && board[3] == board[6] && board[0] != "-") || 
        (board[1] == board[4] && board[4] == board[7] && board[1] != "-") || 
        (board[2] == board[5] && board[5] == board[8] && board[2] != "-") || 
        (board[0] == board[4] && board[4] == board[8] && board[0] != "-") || 
        (board[2] == board[4] && board[4] == board[6] && board[2] != "-")) { 
        return "win"; 
    } 
    // Check for a tie 
    if (count(board.begin(), board.end(), "-") == 0) { 
        return "tie"; 
    } 
    return "play"; 
} 
 
// Main game loop
int main() {
    displayInstructions();
    bool playAgain = true; 
 
    cout<< "Enter your name: "<<"\t";
    string name;
    cin >> name;

    while (playAgain) {
        initializeBoard(); 
        printBoard();
        string currentPlayer = "X"; 
        bool gameOver = false;
 
        while (!gameOver) { 
            takeTurn(currentPlayer);
            string result = checkGameOver(); 
 
            if (result == "win") { 
                cout << currentPlayer << " wins!\n"; 
                if (currentPlayer == "X") { 
                    scoreX++; 
                } else { 
                    scoreO++; 
                } 
                gameOver = true; 
            } else if (result == "tie") { 
                cout << "It's a tie!\n";
                ties++; 
                gameOver = true; 
            } else { 
                currentPlayer = (currentPlayer == "X") ? "O" : "X"; 
            } 
        } 
 
displayScore();
char choice; 
cout << "Do you want to play again? (y/n): "; 
cin >> choice; 
playAgain = (choice == 'y' || choice == 'Y');
}
cout << "Thanks " << name <<" for playing Tic-Tac-Toe! Goodbye!\n";
return 0;
}