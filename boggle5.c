#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Defines Macro Constants

#define ROWS 4
#define COLS 4
#define LETTERS 26
#define DICE 16
#define SIDES 6
#define TRUE 1
#define FALSE 0
#define SPACE ' '
#define NAME 20
#define WORDS 100
#define LENGTH 17
#define MAX 10
#define TIME 180

// Function prototypes

struct Player{ //creates an user's profile
    char name[NAME];
    char words[WORDS][LENGTH];
    int score;
    int count;
};

void welcomeScreen();
void clearScreen();
void displayExplicitBoard();
void displayBoard(char board[ROWS][COLS]);
void displayDice(char dice[DICE][SIDES]);
void createBoard(char dice[DICE][SIDES], char board[ROWS][COLS], int usedDie[DICE]);
char getLetter(char dice[DICE][SIDES], int row);
void playGame(struct Player *Ernesto, char board[ROWS][COLS]);
void displayWordsFound(struct Player *Ernesto);
void scoreWords(struct Player *Ernesto);
int getWordLength(char word[LENGTH]);

//Main function that executes program

int main(){
    //declared local variables
    char dice[DICE][SIDES] = { //initialized 16 x 6 array
        {'D', 'R', 'L', 'X', 'E', 'I'},
        {'C', 'P', 'O', 'H', 'S', 'A'},
        {'N', 'H', 'N', 'L', 'Z', 'R'},
        {'W', 'T', 'O', 'O', 'T', 'A'},
        {'I', 'O', 'S', 'S', 'E', 'T'},
        {'N', 'W', 'E', 'G', 'H', 'E'},
        {'B', 'O', 'O', 'J', 'A', 'B'},
        {'U', 'I', 'E', 'N', 'E', 'S'},
        {'P', 'S', 'A', 'F', 'K', 'F'},
        {'I', 'U', 'N', 'H', 'M', 'Q'},
        {'Y', 'R', 'D', 'V', 'E', 'L'},
        {'V', 'E', 'H', 'W', 'H', 'R'},
        {'I', 'O', 'T', 'M', 'U', 'C'},
        {'T', 'Y', 'E', 'T', 'T', 'R'},
        {'S', 'T', 'I', 'T', 'Y', 'D'},
        {'A', 'G', 'A', 'E', 'E', 'N'},
    };
    char board[ROWS][COLS];
    int usedDie[DICE];
    struct Player Ernesto;
    memset(usedDie, FALSE, sizeof(usedDie)); //initializes usedDie array with all elements being 0
    memset(board, SPACE, sizeof(board)); //initializes board array with all elements being ' '
    srand(time(0)); //ensures every sequence is unique

    //calls function welcomeScreen
    welcomeScreen();
    //calls function clearScreen
    clearScreen();
    //calls function createBoard with char dice & board array, and int usedDie array as arguments
    createBoard(dice, board, usedDie);
    //calls function playGame
    playGame(&Ernesto, board);

    return 0;
}

//Generates the welcome screen

void welcomeScreen(){
    printf("                BBBBB    OOOO    GGGGG    GGGGG   LL      EEEEEE\n");
    printf("                BB  BB  OO  OO  GG       GG       LL      EE\n");
    printf("                BBBBB   OO  OO  GG       GG       LL      EEEE\n");
    printf("                BB  BB  OO  OO  GG  GGG  GG  GGG  LL      EE\n");
    printf("                BBBBB    OOOO    GGGGGG   GGGGGG  LLLLLL  EEEEEE\n\n\n");
    printf("RULES OF THE GAME:\n");
    printf("        1. The player is presented with a Boggle board\n");
    printf("        2. The player will have three minutes to find as many words as possible.\n");
    printf("        3. Words must contain three letters or more.\n");
    printf("        4. Words are formed from adjoining letters.\n");
    printf("        5. Letters must join in the proper sequence to spell a word.\n");
    printf("        6. Letters may join horizontally, vertically, or diagonally, to the left, right, up or down.\n");
    printf("        7. No letter cube may be used more than once in a single word.\n");
    printf("        8. Words submitted will be scored accordingly.\n");
    printf("        9. Good luck!\n\n");
}

//Asks the user to hit enter, which then proceeds to clear user's current screen and moves the user to next screen

void clearScreen(){
    char enter;
    printf("\tHit <ENTER> to continue!");
    scanf("%c", &enter);
    system("cls");
}

//Displays the explicit boggle board to the user

void displayExplicitBoard(){
    printf("|-------------------------------|\n");
    printf("|          BOGGLE BOARD         |\n");
    printf("|-------------------------------|\n");
    printf("|   T   |   A   |   O   |   C   |\n");
    printf("|-------------------------------|\n");
    printf("|   L   |   I   |   S   |   M   |\n");
    printf("|-------------------------------|\n");
    printf("|   U   |   N   |   B   |   I   |\n");
    printf("|-------------------------------|\n");
    printf("|   B   |   O   |   G   |   D   |\n");
    printf("|-------------------------------|\n");
}

//Generates a new boggle board filled by random letters

void displayBoard(char board[ROWS][COLS]){
    //declares local variables
    int row, col;

    printf("|-------------------------------|\n");
    printf("|          BOGGLE BOARD         |\n");
    printf("|-------------------------------|\n");

    for(row = 0; row < ROWS; row ++){
        for(col = 0; col < COLS; col ++){
            printf("|   %c   ", board[row][col]);
        }
        printf("|\n");
        printf("|-------------------------------|\n");
    }
}

//Displays to the user all the different dices available

void displayDice(char dice[DICE][SIDES]){
    //declared local variables
    int row, col;
    printf("BOGGLE DICE\n\n");
    for(row = 0; row < DICE; row ++){
        printf("Die %d\n", row + 1);
        for(col = 0; col < SIDES; col ++){
            printf("%c ", dice[row][col]);
        }
        printf("\n");
    }
}

//Finds the letter assigned in dice[row][col]

char getLetter(char dice[DICE][SIDES], int row){
    char letter;
    int col;
    col = rand()%SIDES;
    letter = dice[row][col];
    return letter;
}

//Creates the boggle board

void createBoard(char dice[DICE][SIDES], char board[ROWS][COLS], int usedDie[DICE]){
    int row, col, die;
    char letter;
    for(row = 0; row < ROWS; row ++){
        col = 0;
        while (col < COLS){
            die = rand()%DICE;
            if(usedDie[die] == FALSE){
                letter = getLetter(dice, die);
                board[row][col] = letter;
                usedDie[die] = TRUE;
                col++;
            }
        }
    }
}

//Initiates boggle game by asking user for name, and words found in the board

void playGame(struct Player *Ernesto, char board[ROWS][COLS]){
    int play = TRUE;
    int idx = 0;
    unsigned int seconds = 0;
    unsigned int milliseconds = 0;
    int timeLeft = 0;
    unsigned int countDownTimeSecs = TIME;
    clock_t startTime;
    clock_t countTime;

    printf("Player, please enter your name\n");
    scanf("%s", (*Ernesto).name);
    (*Ernesto).count = 0;
    (*Ernesto).score = 0;
    clearScreen();

    printf("%s let's play Boggle\n\n", (*Ernesto).name);
    startTime = clock();
    timeLeft = countDownTimeSecs - seconds;
    displayBoard(board);
    while (timeLeft > 0){ //game stops when it reaches 0 seconds left
        countTime = clock();
        milliseconds = countTime - startTime;
        seconds = milliseconds/CLOCKS_PER_SEC;
        timeLeft = countDownTimeSecs - seconds;

        printf("\nType the word found and the <Enter> key\n");
        scanf("%s", (*Ernesto).words[idx]);
        (*Ernesto).count++;
        idx++;
    }
    printf("Time is up!\n");
    displayWordsFound(Ernesto);
    scoreWords(Ernesto);
}

//Goes through the word array found in Player's structure and print every word inputed

void displayWordsFound(struct Player *Ernesto){
    int w;
    printf("Words found %d:\n", (*Ernesto).count);
    for(w = 0; w < (*Ernesto).count; w++){
        printf("%s\n", (*Ernesto).words[w]);
    }
}

//Returns the amount of characters found in the word
int getWordLength(char word[LENGTH]){
    int count = 0;
    int idx = 0;
    while (word[idx] != '\0'){
        idx++;
        count++;
    }
    return count;
}

//Calculates the score of the user based on the rules of Boggle
void scoreWords(struct Player *Ernesto){
    for(int i = 0; i < (*Ernesto).count; i++){
        int length = getWordLength((*Ernesto).words[i]);
        if (length <= 2){
            (*Ernesto).score = (*Ernesto).score + 0;
        }
        else if (length == 3){
            (*Ernesto).score = (*Ernesto).score + 1;
        }
        else if (length == 4){
            (*Ernesto).score = (*Ernesto).score + 1;
        }
        else if (length == 5){
            (*Ernesto).score = (*Ernesto).score + 2;
        }
        else if (length == 6){
            (*Ernesto).score = (*Ernesto).score + 3;
        }
        else if (length == 7){
            (*Ernesto).score = (*Ernesto).score + 4;
        }
        else if(length >= 8 && length <= 17){
            (*Ernesto).score = (*Ernesto).score + 11;
        }
    }
    printf("%s's final score is: %d", (*Ernesto).name, (*Ernesto).score);
}
