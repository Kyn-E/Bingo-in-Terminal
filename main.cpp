#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

// Constants
const int SIZE = 5; // Bingo card is 5x5

// Function prototypes
void generateCard(int card[SIZE][SIZE]);
void printCard(int card[SIZE][SIZE]);
bool markNumber(int card[SIZE][SIZE], int number);
bool checkBingo(int card[SIZE][SIZE]);

int main() {
    srand(time(0)); // random number generation

    int card[SIZE][SIZE];
    generateCard(card);
    printCard(card);

    int number;
    while (true) {
        cout << "Mark your number (1-75): ";
        cin >> number;

        if (number == 0) {
            break;
        }

        if (markNumber(card, number)) {
            cout << "Number " << number << " marked on the card." << endl;
            printCard(card);

            if (checkBingo(card)) {
                cout << "Bingo! You've won!" << endl;
                break;
            }
        } else {
            cout << "Number " << number << " is not on the card or already marked." << endl;
        }
    }

    return 0;
}

void generateCard(int card[SIZE][SIZE]) {
    bool used[75] = {false}; // To keep track of used numbers
    int min = 1, max = 15;

    for (int col = 0; col < SIZE; col++) {
        int count = 0;
        while (count < SIZE) {
            int num = rand() % (max - min + 1) + min;
            if (!used[num - 1]) {
                card[count][col] = num;
                used[num - 1] = true;
                count++;
            }
        }
        min += 15;
        max += 15;
    }

    card[2][2] = 0;
}

void printCard(int card[SIZE][SIZE]) {
    cout << "\nBingo Card:\n";
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (card[row][col] == 0)
                cout << setw(4) << "FREE";
            else
                cout << setw(4) << card[row][col];
        }
        cout << endl;
    }
    cout << endl;
}

bool markNumber(int card[SIZE][SIZE], int number) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (card[row][col] == number) {
                card[row][col] = -1; // Mark the number
                return true;
            }
        }
    }
    return false;
}

bool checkBingo(int card[SIZE][SIZE]) {
    // Check rows
    for (int row = 0; row < SIZE; row++) {
        bool rowBingo = true;
        for (int col = 0; col < SIZE; col++) {
            if (card[row][col] != -1 && (row != 2 || col != 2)) { // Free space in center
                rowBingo = false;
                break;
            }
        }
        if (rowBingo) return true;
    }

    // Check columns
    for (int col = 0; col < SIZE; col++) {
        bool colBingo = true;
        for (int row = 0; row < SIZE; row++) {
            if (card[row][col] != -1 && (row != 2 || col != 2)) { // Free space in center
                colBingo = false;
                break;
            }
        }
        if (colBingo) return true;
    }

    // Check diagonals
    bool diag1Bingo = true;
    for (int i = 0; i < SIZE; i++) {
        if (card[i][i] != -1 && (i != 2 || i != 2)) {
            diag1Bingo = false;
            break;
        }
    }
    if (diag1Bingo) return true;

    bool diag2Bingo = true;
    for (int i = 0; i < SIZE; i++) {
        if (card[i][SIZE - i - 1] != -1 && (i != 2 || SIZE - i - 1 != 2)) {
            diag2Bingo = false;
            break;
        }
    }
    if (diag2Bingo) return true;

    return false;
}
