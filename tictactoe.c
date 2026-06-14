#include <stdio.h>
#include <stdlib.h>

void initialize_board(char board[3][3]){
    // set up initial board 

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

void update_board(char board[3][3], char player, int x, int y){
    // update position of board array

    board[x][y] = player;
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
    // Checks all positions of board for 
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

int main(){
    char board[3][3];
    char player = 'O';
    int game = 0;
    char buffer[10];
    int row, col;

    // initialize game
    initialize_board(board);
    print_board(board);

    // Game loop
    while (game == 0){
        int move;

        printf("Enter a move: ");

        // Validate input
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            break; // Handle potential EOF/error
        }

        if (sscanf(buffer, "%d", &move) != 1){
            printf("Issue: That is not a number\n");
            continue;
        }

        if (move < 0 || move > 9){
            printf("Issue: Move is out of bounds\n");
            continue;
        }
 
        // Update board
        get_coor(move, &row, &col);
        if ((board[row][col]) == ' '){
            update_board(board, player, row, col);
        }
        else{
            printf("Spot already occupied by %c\n", board[row][col]);
            continue;
        }

        print_board(board);

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
