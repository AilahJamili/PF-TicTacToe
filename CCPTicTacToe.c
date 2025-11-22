#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#define size 3

char board[size][size];

void initialize(char (*board)[size]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            *(*(board + i) + j) = ' ';
        }
    }
}

void displayBoard(char (*board)[size]) {
    int num = 1;

    for (int i = 0; i < size; i++) {

        for (int j = 0; j < size; j++) {

            if (*(*(board + i) + j) == ' ')
                printf("%2d", num);
            else
                printf(" %c", *(*(board + i) + j));

            if (j < size - 1)
                printf(" |");

            num++;
        }

        printf("\n");

        if (i < size - 1) {
            for (int k = 0; k < size; k++) {
                printf("---");
                if (k < size - 1)
                    printf("+");
            }
            printf("\n");
        }
    }

    printf("\n");
}

void GameMode(int *mode) {
    printf("Choose game mode:\n");
    printf("1. Player vs Player\n");
    printf("2. Player vs AI\n");
    scanf("%d", mode);
    while (*mode != 1 && *mode != 2) {
        printf("Invalid choice! Enter 1 or 2: ");
        scanf("%d", mode);
    }
}

void chooseSymbol(char *player, char *ai) {
    char choice;
    printf("Choose your symbol (X or O): ");
    scanf(" %c", &choice);
    choice = toupper(choice);
    *player = choice;
    *ai = (choice == 'X') ? 'O' : 'X';
    printf("Player: %c, AI: %c\n", *player, *ai);
}

void choosePvPSymbols(char *p1, char *p2) {
    char choice;
    printf("Player 1, choose your symbol (X or O): ");
    scanf(" %c", &choice);

    choice = toupper(choice);

    while (choice != 'X' && choice != 'O') {
        printf("Invalid! Choose X or O: ");
        scanf(" %c", &choice);
        choice = toupper(choice);
    }

    *p1 = choice;
    *p2 = (choice == 'X') ? 'O' : 'X';

    printf("Player 1: %c\n", *p1);
    printf("Player 2: %c\n", *p2);
}

int isWinnerHoriz(char (*board)[size], char Symb1, char Symb2) {
    for (int i = 0; i < size; i++) {
        int count1 = 0, count2 = 0;
        for (int j = 0; j < size; j++) {
            if (*(*(board + i) + j) == Symb1) count1++;
            else if (*(*(board + i) + j) == Symb2) count2++;
        }

        if (count1 == size) return 1;
        else if (count2 == size) return 2;
    }
    return 0;
}

int isWinnerVert(char (*board)[size], char Symb1, char Symb2) {
    for (int j = 0; j < size; j++) {
        int count1 = 0, count2 = 0;
        for (int i = 0; i < size; i++) {
            if (*(*(board + i) + j) == Symb1) count1++;
            else if (*(*(board + i) + j) == Symb2) count2++;
        }

        if (count1 == size) return 1;
        else if (count2 == size) return 2;
    }
    return 0;
}

int isWinnerDiag(char (*board)[size], char Symb1, char Symb2) {
    int count1 = 0, count2 = 0;

    for (int i = 0; i < size; i++) {
        if (*(*(board + i) + i) == Symb1) count1++;
        else if (*(*(board + i) + i) == Symb2) count2++;
    }

    if (count1 == size) return 1;
    if (count2 == size) return 2;

    count1 = 0;
    count2 = 0;

    for (int i = 0; i < size; i++) {
        int j = size - 1 - i;
        if (*(*(board + i) + j) == Symb1) count1++;
        else if (*(*(board + i) + j) == Symb2) count2++;
    }

    if (count1 == size) return 1;
    if (count2 == size) return 2;

    return 0;
}

int isWinner(char (*board)[size], char Symb1, char Symb2) {
    int winner;

    winner = isWinnerHoriz(board, Symb1, Symb2);
    if (winner != 0) return winner;

    winner = isWinnerVert(board, Symb1, Symb2);
    if (winner != 0) return winner;

    winner = isWinnerDiag(board, Symb1, Symb2);
    if (winner != 0) return winner;

    return 0;
}

int isDraw(char (*board)[size], char Symb1, char Symb2) {
    int i, j;
    if (isWinner(board, Symb1, Symb2) != 0) return 0;

    int spacefilled = 0;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (*(*(board + i) + j) != ' ') spacefilled++;
        }
    }
    if (spacefilled == size * size) return 1;
    else return 0;
}

void chooseAIDifficulty(int *difficulty) {
    printf("Choose difficulty:\n");
    printf("1. Easy\n");
    printf("2. Medium\n");
    printf("3. Hard\n");
    scanf("%d", difficulty);
}

void chooseFirstPlayer(int *first) {
    printf("Who wants to play first?\n");
    printf("1. Player\n");
    printf("2. AI\n");
    scanf("%d", first);
    while (*first != 1 && *first != 2) {
        printf("Invalid choice! Enter 1 for Player or 2 for AI: ");
        scanf("%d", first);
    }
}

void aiMoveEasy(char (*board)[size], char aiSymbol) {
    int r, c;
    do {
        r = rand() % size;
        c = rand() % size;
    } while (*(*(board + r) + c) != ' ');
    *(*(board + r) + c) = aiSymbol;
}

void aiMoveMedium(char (*board)[size], char aiSymbol, char playerSymbol) {
    int r, c;
    for (r = 0; r < size; r++) {
        for (c = 0; c < size; c++) {
            if (*(*(board + r) + c) == ' ') {
                *(*(board + r) + c) = aiSymbol;

                if (isWinner(board, playerSymbol, aiSymbol) == 2) return;
                *(*(board + r) + c) = ' ';
            }
        }
    }
    for (r = 0; r < size; r++) {
        for (c = 0; c < size; c++) {
            if (*(*(board + r) + c) == ' ') {
                *(*(board + r) + c) = playerSymbol;

                if (isWinner(board, playerSymbol, aiSymbol) == 1) {
                    *(*(board + r) + c) = aiSymbol;
                    return;
                }
                *(*(board + r) + c) = ' ';
            }
        }
    }

    aiMoveEasy(board, aiSymbol);
}

int evaluate(char (*board)[size], char playerSymbol, char aiSymbol) {
    int winner = isWinner(board, playerSymbol, aiSymbol);

    if (winner == 2) return 1;
    if (winner == 1) return -1;

    return 0;
}

int RemainingMoves(char (*board)[size]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (*(*(board + i) + j) == ' ') return 1;
        }
    }
    return 0;
}

int minimax(char (*board)[size], int depth, int isMax, char playerSymbol, char aiSymbol) {
    int score = evaluate(board, playerSymbol, aiSymbol);

    if (score == 1) return score;
    if (score == -1) return score;
    if (!RemainingMoves(board)) return 0;

    if (isMax) {
        int best = -10000;

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (*(*(board + i) + j) == ' ') {
                    *(*(board + i) + j) = aiSymbol;
                    int val = minimax(board, depth + 1, 0, playerSymbol, aiSymbol);
                    *(*(board + i) + j) = ' ';

                    if (val > best) best = val;
                }
            }
        }
        return best;
    }

    else {
        int best = 10000;

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (*(*(board + i) + j) == ' ') {
                    *(*(board + i) + j) = playerSymbol;
                    int val = minimax(board, depth + 1, 1, playerSymbol, aiSymbol);
                    *(*(board + i) + j) = ' ';

                    if (val < best) best = val;
                }
            }
        }
        return best;
    }
}

void aiMoveHard(char (*board)[size], char aiSymbol, char playerSymbol) {
    int bestVal = -10000;
    int bestr = -1, bestc = -1;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (*(*(board + i) + j) == ' ') {
                *(*(board + i) + j) = aiSymbol;
                int move = minimax(board, 0, 0, playerSymbol, aiSymbol);
                *(*(board + i) + j) = ' ';

                if (move > bestVal) {
                    bestVal = move;
                    bestr = i;
                    bestc = j;
                }
            }
        }
    }

    *(*(board + bestr) + bestc) = aiSymbol;
}

int main() {
    int gamemode, difficulty, firstplayer;
    int move, row, col;
    char playerSymbol, aiSymbol;
    int turn = 1;

    srand(time(NULL));

    printf("Welcome to Tic-Tac-Toe!\n\n");

    initialize(board);

    // Choose game mode
    GameMode(&gamemode);

    // PvP symbol selection
    if (gamemode == 1) {
        choosePvPSymbols(&playerSymbol, &aiSymbol);
    }

    // PvAI setup
    if (gamemode == 2) {
        chooseSymbol(&playerSymbol, &aiSymbol);
        chooseAIDifficulty(&difficulty);
        chooseFirstPlayer(&firstplayer);
    }

    while (1) {
        displayBoard(board);

        // Player vs Player
        if (gamemode == 1) {
            char playerTurnSymbol;

            if (turn % 2 == 1) playerTurnSymbol = playerSymbol;
            else playerTurnSymbol = aiSymbol;

            printf("Player %c, enter your move (1-9): ", playerTurnSymbol);
            scanf("%d", &move);

            row = (move - 1) / 3;
            col = (move - 1) % 3;

            if (move < 1 || move > 9 || board[row][col] != ' ') {
                printf("Invalid move!Try again.\n");
                continue;
            }

            board[row][col] = playerTurnSymbol;
        }

        // Player vs AI
        else {
            int isPlayerTurn = (firstplayer == 1 && turn % 2 == 1) ||
                               (firstplayer == 2 && turn % 2 == 0);

            if (isPlayerTurn) {
                printf("Your move (1-9): ");
                scanf("%d", &move);

                row = (move - 1) / 3;
                col = (move - 1) % 3;

                if (move < 1 || move > 9 || board[row][col] != ' ') {
                    printf("Invalid move! Try again.\n");
                    continue;
                }

                board[row][col] = playerSymbol;
            }

            else {
                printf("AI's move:\n");

                if (difficulty == 1)
                    aiMoveEasy(board, aiSymbol);
                else if (difficulty == 2)
                    aiMoveMedium(board, aiSymbol, playerSymbol);
                else if (difficulty == 3)
                    aiMoveHard(board, aiSymbol, playerSymbol);
            }
        }

        // Check for winner
        int result = isWinner(board, playerSymbol, aiSymbol);

        if (gamemode == 1) {
            if (result == 1 || result == 2) {
                displayBoard(board);
                if (result == 1) 
                    printf("Player 1 (%c) wins!\n", playerSymbol);
                else 
                    printf("Player 2 (%c) wins!\n", aiSymbol);
                break;
            }
        } 
        else {
            if (result == 1) {
                displayBoard(board);
                printf("You win! Great job!\n");
                break;
            }
            if (result == 2) {
                displayBoard(board);
                printf("AI wins! Better luck next time.\n");
                break;
            }
        }

        // Check for draw
        if (isDraw(board, playerSymbol, aiSymbol)) {
            displayBoard(board);
            printf("It's a draw!\n");
            break;
        }

        turn++;
    }

    // Play again
    char replay;
    printf("Do you want to play again? (y/n): ");
    scanf(" %c", &replay);

    if (replay == 'y' || replay == 'Y') {
        initialize(board);
        main();  // restart game
    }
	else printf("Thankyou for playing! Goodbye!\n");
    
    return 0;
}


