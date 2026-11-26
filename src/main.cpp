#include <iostream>
#include <conio.h>

using namespace std;
#define H 20
#define W 15
char board[H][W] = {};

int x, y, b;
char blocks[][4][4] ={
        {{' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '}},

        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},

        {{' ',' ',' ',' '},
         {' ','T',' ',' '},
         {'T','T','T',' '},
         {' ',' ',' ',' '}},

        {{' ',' ',' ',' '},
         {' ','S','S',' '},
         {'S','S',' ',' '},
         {' ',' ',' ',' '}},

        {{' ',' ',' ',' '},
         {'Z','Z',' ',' '},
         {' ','Z','Z',' '},
         {' ',' ',' ',' '}},

        {{' ',' ',' ',' '},
         {'J',' ',' ',' '},
         {'J','J','J',' '},
         {' ',' ',' ',' '}},

        {{' ',' ',' ',' '},
         {' ',' ','L',' '},
         {'L','L','L',' '},
         {' ',' ',' ',' '}}
};

char curblocks[4][4];

void rotateBlock() {
    char tmp[4][4];
    for (int i = 0; i < 4; i++) 
        for (int j = 0; j < 4; j++) 
            tmp[j][3-i] = curblocks[i][j];
        
    for (int i = 0; i < 4; i++) 
        for (int j = 0; j < 4; j++) 
            curblocks[i][j] = tmp[i][j];
}

bool canMove(int dx, int dy, bool Rotated = false){

    for (int i = 0; i < 4; i++ )
        for (int j = 0; j < 4; j++ ) {
            int ni = Rotated ? j : i;
            int nj = Rotated ? 3-i : j;
            if (curblocks[i][j] != ' ') {
                int xt = x + nj + dx;
                int yt = y + ni + dy;
                if (xt < 1 || xt >= W-1 || yt >= H-1 ) return false;
                if (board[yt][xt] != ' ') return false;
            }
        }
    return true;
}
void block2Board(){
    for (int i = 0; i < 4; i++ )
        for (int j = 0; j < 4; j++ )
            if (curblocks[i][j] != ' ')
                board[y+i][x+j] = curblocks[i][j];
}
void boardDelBlock(){
    for (int i = 0; i < 4; i++ )
        for (int j = 0; j < 4; j++ )
            if (curblocks[i][j] != ' ')
                board[y+i][x+j] = ' ';
}
void initBoard(){
    for (int i = 0 ; i < H ; i++)
        for (int j = 0 ; j < W ; j++)
            if (i == 0 || i == H-1 || j ==0 || j == W-1) board[i][j] = '#';
            else board[i][j] = ' ';
}
void draw(){
    system("cls");

    for (int i = 0 ; i < H ; i++, cout<<endl)
        for (int j = 0 ; j < W ; j++) cout<<board[i][j];
}
void removeLine(){
    int i,j;
    for (i = H-2 ; i > 0 ; i-- ){
        for (j = 0 ; j < W ; j++)
            if (board[i][j] == ' ') break;
        if (j == W){
            for (int ii = i ; ii > 0 ; ii--)
                for (int jj = 0; jj < W; jj++)
                    board[ii][jj] = board[ii-1][jj];
            i++;
            draw();
            _sleep(200);
        }
    }
}

void spawnBlock() {
    x = 5; y = 1; b = rand()%7;
    for (int i = 0; i < 4; i++) 
        for (int j = 0; j < 4; j++)
            curblocks[i][j] = blocks[b][i][j];
}

int main()
{
    srand(time(0));
    spawnBlock();
    initBoard();
    while (1){
        boardDelBlock();
        if (kbhit()){
            char c = getch();
            if (c == 'a' && canMove(-1,0)) x--;

            if (c == 'd' && canMove( 1,0)) x++;
            if (c == 'x' && canMove( 0,1)) y++;
            if (c == 'w') {
                if (canMove(0, 0, true)) rotateBlock();
                else if (canMove(1, 0, true)) { x++; rotateBlock(); }
                else if (canMove(-1, 0, true)) { x--; rotateBlock(); }
                else if (canMove(2, 0, true)) { x += 2; rotateBlock(); } 
                else if (canMove(-2, 0, true)) { x -= 2; rotateBlock(); }
            }

            if (c == 'q') break;
        }
        if (canMove(0,1)) y++;
        else{
            block2Board();
            removeLine();
            spawnBlock();
        }
        block2Board();
        draw();
        _sleep(500);
    }
    return 0;
}
