#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void instructions(char board[3][3]){
    // Print game instructions 

    printf("\nWelcome to Tic Tac Toe\n");
    printf("The move positions of this game are as follows:\n");
    printf("Enter 'quit' to exit the game early\n");

    char position = '0';
    for (int row = 0; row < 3; row++){
        for (int col = 0; col < 3; col++){
            position++;
            board[row][col] = position;
        }
    }
}

void initialize_board(char board[3][3]){
    // set up initial game board 

    for (int row = 0; row < 3; row++){
        for (int col = 0; col < 3; col++){
            board[row][col] = ' ';
        }
    }
}

void print_board(char board[3][3]){
    // Given board array, render the game board

    printf("\n -----------\n");
    for (int row = 0; row < 3; row++){
        printf("| %c | %c | %c |\n", board[row][0], board[row][1], board[row][2]);
        printf(" -----------\n");
    }
    printf("\n");
}

void get_coor(int sequential_index, int* x, int* y){
    // Given a sequential number, convert it to 3x3 x,y coordinate position
    // Then update the corresponding values in memory
    
    *x = (sequential_index-1) / 3;
    *y = (sequential_index-1) % 3;
}

int check_win(char board[3][3]){
    // Given a 3x3 board, check all possible winning combinations
    // Return outcome

    for (int i = 0; i < 3; i++){
        // Check horitzontals
        if (board[i][0] != ' '){
            if (board[i][0] == board[i][1] && board[i][1] == board[i][2]){
                return 1;
            }
        }

        // check verticals
        if (board[0][i] != ' '){
            if (board[0][i] == board[1][i] && board[1][i] == board[2][i]){
                return 1;
            }
        }
    }

    // check diagonal
        if (board[0][0] != ' '){
            if (board[0][0] == board[1][1] && board[1][1] == board[2][2]){
                return 1;
            }
        }

    // check anti-diagonal
    if (board[0][2] != ' '){
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0]){
            return 1;
        }
    }

    return 0;
}

int check_filled(char board[3][3]){
    // Checks board for open spots

    for (int row = 0; row < 3; row++){
        for (int col = 0; col < 3; col++){
            if (board[row][col] != 'X' && board[row][col] != 'O'){
                return 0;
            }
        }
    }
    return 1;
}

void switch_player(char* player){
    // switch between player 1 and 2

    if (*player == 'O'){
        *player = 'X';
    }
    else{
        *player = 'O';
    }
}

int play_tictactoe(){
    int move;
    char input[6];
 
    int game = 0;
    char player = 'O';
    
    char board[3][3];
    int row, col;

    // initialize game
    instructions(board);
    print_board(board);

    initialize_board(board);

    // Game loop
    while (game == 0){
        printf("Current Player is %c\n", player);
        printf("Enter a move: ");

        // Read line using fgets
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break; 
        }

        // strip newline from input buffer
        input[strcspn(input, "\r\n")] = '\0';

        // check for text command
        if (strcmp(input, "quit") == 0){
            printf("\033[2J\033[H");
            break;

        }
        
        // else try parsing as a number
        if (sscanf(input, "%d", &move) == 1){
            if (move < 0 || move > 9){
                print_board(board);
                printf("\nIssue: Move out of bounds. Try again\n\n");
                continue;
            }
        }
        else{
            print_board(board);
            printf("Invalid input, try again\n");
            continue;
        }

        // Update board
        get_coor(move, &row, &col);
        if ((board[row][col]) == ' '){
            board[row][col] = player;
            print_board(board);
        }
        else{
            print_board(board);
            printf("\nSpot already occupied by %c\n\n", board[row][col]);
            continue;
        }

        // Game Conditions
        // Check win
        if (check_win(board)){
            printf("Player %c WINS!\n", player);
            break;
        }

        // Check tie
        // if one won and board is filled, then tie.
        if (check_filled(board)){
            printf("Game has tied\n");
            break;
        }

        // Switch player
        switch_player(&player);
    }
    return 0;
}

int main(){
    play_tictactoe();
}
