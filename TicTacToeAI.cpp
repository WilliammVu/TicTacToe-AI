#include <iostream>
using namespace std;

struct Move{
    int row;
    int col;
};
char player = 'O';
char opponent = 'X';

//returns true if there are still moves left to play
//false if there are none left
bool gameNotFinished(char board[3][3]){
    for(int i=0;i<3;++i){
        for(int j=0;j<3;++j){
            if(board[i][j] == '_')
                return true;
        }
    }
    return false;
}

int checkWin(char b[3][3]){
    //check rows for victory
    for (int row = 0; row<3; row++){
        if (b[row][0]==b[row][1] &&
            b[row][1]==b[row][2])
        {
            if (b[row][0]==player)
                return +10;
            else if (b[row][0]==opponent)
                return -10;
        }
    }
    //check columns for victory
    for (int col = 0; col<3; col++)
        {
            if (b[0][col]==b[1][col] &&
                b[1][col]==b[2][col])
            {
                if (b[0][col]==player)
                    return +10;
      
                else if (b[0][col]==opponent)
                    return -10;
            }
        }
    //check diagnols for victory
    if (b[0][0]==b[1][1] && b[1][1]==b[2][2]){
        if (b[0][0]==player)
            return +10;
        else if (b[0][0]==opponent)
            return -10;
    }
    if (b[0][2]==b[1][1] && b[1][1]==b[2][0]){
        if (b[0][2]==player)
            return +10;
        else if (b[0][2]==opponent)
            return -10;
    }
    return 0;//if no one has won
}

int minimax(char board[3][3], int depth, bool isMax){
    int score = checkWin(board);
    if (score == 10)
        return score;
    if (score == -10)
        return score;
    //game is finished and no winner -> tie
    if (gameNotFinished(board)==false)
        return 0;
    if (isMax)
    {
        int best = -1000;
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                // Check if cell is empty
                if (board[i][j]=='_')
                {
                    // Make the move
                    board[i][j] = player;
                    best = max( best,
                        minimax(board, depth+1, !isMax) );
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
    else
    {
        int best = 1000;
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                if (board[i][j]=='_')
                {
                    // Make the move
                    board[i][j] = opponent;
                    best = min(best,minimax(board, depth+1, !isMax));
                    // Undo the move
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
}

//returns the best move
Move findBestMove(char board[3][3])
{
    int bestVal = -1000;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;
    // Traverse all elements of board, evaluate minimax function for
    // all empty cells. And return the cell with optimal
    // value.
    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            // Check if cell is empty
            if (board[i][j]=='_')
            {
                // Make the move
                board[i][j] = player;
  
                // compute evaluation function for this
                // move.
                int moveVal = minimax(board, 0, false);
  
                // Undo the move
                board[i][j] = '_';
  
                // If the value of the current move is
                // more than the best value, then update
                // best/
                if (moveVal > bestVal)
                {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

void printBoard(char board[3][3]){
    for(int i=0;i<3;++i){
        for(int j=0;j<3;++j){
            cout << board[i][j] << ' ';
        }
        cout << endl;
    }
}

int main() {
    char board[3][3];
    //initialize each element in board to '_'
    for(int i=0;i<3;++i){
        for(int j=0;j<3;++j){
            board[i][j] = '_';
        }
    }
    do{
        cout << "Enter your move (row col): ";
        int row,col;
        cin >> row >> col;
        board[row][col] = 'O';
        printBoard(board);
        if(checkWin(board) == 10){
            cout << "The game is over" << endl;
            break;
        }
        if(checkWin(board) == -10){
            cout << "The game is over" << endl;
            break;
        }
        cout << endl << "Now your AI opponent will move" << endl;
        Move AImove = findBestMove(board);
        board[AImove.row][AImove.col] = 'X';
        printBoard(board);
        if(checkWin(board) == 10){
            cout << "The game is over" << endl;
            break;
        }
        if(checkWin(board) == -10){
            cout << "The game is over" << endl;
            break;
        }
    }while(gameNotFinished(board));
    if(checkWin(board) == 0){
        cout << "The game finished with a tie" << endl;
    }
    return 0;
}

