#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cctype>

using namespace std;

class HangmanGame {
public:
    HangmanGame() {
        srand(static_cast<unsigned int>(time(nullptr)));
    }

    void play() {
        do {
            setDifficulty();
            initializeGame();
            gameLoop();
        } while (replay());
    }

private:
    string secretWord;
    string currentWord;
    int attemptsLeft;
    int maxAttempts;
    string category;
    string difficulty;
    vector<char> guessedLetters;
    vector<char> incorrectGuesses;

    void setDifficulty() {
        cout << "Select Difficulty: \n1. Easy (8 attempts, category shown)\n2. Medium (6 attempts, category shown)\n3. Hard (4 attempts, no category shown)\n";
        int choice;
        while (true) {
            cin >> choice;
            if (choice == 1) {
                maxAttempts = 8;
                difficulty = "Easy";
                break;
            } else if (choice == 2) {
                maxAttempts = 6;
                difficulty = "Medium";
                break;
            } else if (choice == 3) {
                maxAttempts = 4;
                difficulty = "Hard";
                break;
            } else {
                cout << "Invalid choice. Please enter 1, 2, or 3: ";
            }
        }
    }

    void initializeGame() {
        secretWord = getRandomWord();
        currentWord = string(secretWord.length(), '_');
        attemptsLeft = maxAttempts;
        guessedLetters.clear();
        incorrectGuesses.clear();

        cout << "\nWelcome to Hangman!\n" << endl;
        if (difficulty != "Hard") {
            cout << "Category: " << category << "\n" << endl;
        }
    }

    string getRandomWord() {
        vector<pair<string, string>> words = {
            {"apple", "Fruits"}, {"banana", "Fruits"}, {"cherry", "Fruits"},
            {"lion", "Animals"}, {"tiger", "Animals"}, {"giraffe", "Animals"},
            {"teacher", "Professions"}, {"doctor", "Professions"}, {"engineer", "Professions"}
        };
        auto wordPair = words[rand() % words.size()];
        category = wordPair.second;
        return wordPair.first;
    }

    void gameLoop() {
        while (attemptsLeft > 0) {
            displayGameState();
            char guess = getUserGuess();

            if (alreadyGuessed(guess)) {
                cout << "You already guessed that letter. Try again!\n" << endl;
                continue;
            }

            guessedLetters.push_back(guess);

            if (updateCurrentWord(guess)) {
                cout << "Good guess!\n" << endl;
                if (currentWord == secretWord) {
                    cout << "Congratulations! You guessed the word \"" << secretWord << "\" correctly!\n" << endl;
                    return;
                }
            } else {
                incorrectGuesses.push_back(guess);
                attemptsLeft--;
                cout << "Incorrect guess!\n" << endl;
            }
        }

        cout << "Game over! The word was: " << secretWord << "\n" << endl;
    }

    char getUserGuess() {
        char guess;
        while (true) {
            cout << "Guess a letter: ";
            cin >> guess;
            if (isalpha(guess)) {
                return tolower(guess);
            }
            cout << "Invalid input. Please enter a letter.\n";
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
        cout << "\nWord: ";
        for (char c : currentWord) {
            cout << c << " ";
        }
        cout << "\nIncorrect Guesses: ";
        for (char c : incorrectGuesses) {
            cout << c << " ";
        }
        cout << "\nGuesses Left: " << attemptsLeft << "\n" << endl;
    }

    bool replay() {
        char choice;
        while (true) {
            cout << "Do you want to play again? (y/n): ";
            cin >> choice;
            if (tolower(choice) == 'y') return true;
            if (tolower(choice) == 'n') {
                cout << "Thank you for playing Hangman! Goodbye!\n";
                return false;
            }
            cout << "Invalid choice. Please enter 'y' or 'n'.\n";
        }
    }
};

int main() {
    HangmanGame game;
    game.play();
    return 0;
}