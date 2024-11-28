#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cctype>

#define MAX_ATTEMPTS 6

using namespace std;

class HangmanGame {
public:
    HangmanGame() {
        srand(static_cast<unsigned int>(time(nullptr)));
    }

    void play() {
        do {
            initializeGame();
            gameLoop();
        } while (replay());
    }

private:
    string secretWord;
    string currentWord;
    int attemptsLeft;
    vector<char> guessedLetters;

    void initializeGame() {
        secretWord = getRandomWord();
        currentWord = string(secretWord.length(), '_');
        attemptsLeft = MAX_ATTEMPTS;
        guessedLetters.clear();
        cout << "\nWelcome to Hangman!" << endl;
        cout << "Category: Fruits" << endl;
        cout << "You have " << attemptsLeft << " attempts to guess the word." << endl;
    }

    string getRandomWord() {
        vector<string> words = {"apple", "banana", "cherry", "grape", "kiwi", "mango", "peach", "pear"};
        return words[rand() % words.size()];
    }

    void gameLoop() {
        while (attemptsLeft > 0) {
            displayGameState();
            char guess = getUserGuess();

            if (alreadyGuessed(guess)) {
                cout << "You've already guessed that letter. Try again!" << endl;
                continue;
            }

            guessedLetters.push_back(guess);

            if (updateCurrentWord(guess)) {
                cout << "Good guess!" << endl;
                if (currentWord == secretWord) {
                    cout << "Congratulations! You guessed the word: " << secretWord << endl;
                    return;
                }
            } else {
                cout << "Incorrect guess!" << endl;
                attemptsLeft--;
                drawHangman();
            }
        }

        cout << "\nGame over! The word was: " << secretWord << endl;
    }

    char getUserGuess() {
        char guess;
        while (true) {
            cout << "Guess a letter: ";
            cin >> guess;
            if (isalpha(guess)) {
                return tolower(guess);
            }
            cout << "Invalid input. Please enter a letter." << endl;
        }
    }

    bool alreadyGuessed(char letter) {
        return find(guessedLetters.begin(), guessedLetters.end(), letter) != guessedLetters.end();
    }

    bool updateCurrentWord(char letter) {
        bool correctGuess = false;
        for (size_t i = 0; i < secretWord.length(); ++i) {
            if (secretWord[i] == letter) {
                currentWord[i] = letter;
                correctGuess = true;
            }
        }
        return correctGuess;
    }

    void displayGameState() {
        cout << "\nWord: " << currentWord << endl;
        cout << "Attempts left: " << attemptsLeft << endl;
        cout << "Guessed letters: ";
        for (char letter : guessedLetters) {
            cout << letter << " ";
        }
        cout << endl;
    }

    void drawHangman() {
        switch (attemptsLeft) {
            case 5: cout << " O\n"; break;
            case 4: cout << " O\n |\n"; break;
            case 3: cout << " O\n/|\n"; break;
            case 2: cout << " O\n/|\\\n"; break;
            case 1: cout << " O\n/|\\\n/\n"; break;
            case 0: cout << " O\n/|\\\n/ \\\n"; break;
            default: break;
        }
    }

    bool replay() {
        char choice;
        while (true) {
            cout << "\nDo you want to play again? (y/n): ";
            cin >> choice;
            if (tolower(choice) == 'y') {
                return true;
            } else if (tolower(choice) == 'n') {
                cout << "Thank you for playing Hangman! Goodbye!" << endl;
                return false;
            }
            cout << "Invalid choice. Please enter 'y' or 'n'." << endl;
        }
    }
};

int main() {
    HangmanGame game;
    game.play();
    return 0;
}
