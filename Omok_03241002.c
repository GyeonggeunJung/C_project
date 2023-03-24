#include<stdio.h>
#include<Windows.h>

#define BoardSize 19

int Max(int a, int b){
    return a>b ? a : b;
}

int Min(int a, int b){
    return a<b ? a : b;
}

int board[BoardSize][BoardSize];
// 빈 바둑판 구현
void Empty_Board(){
    int i, j;
    for(i=0; i<BoardSize; i++){
        for(j=0; j< BoardSize; j++)
            board[i][j] = 100;
    }
}

//바둑판 현재 상태 출력
void Print_Board(){
    int i, j;
    for(i=0; i<BoardSize; i++){
        for(j=0; j< BoardSize; j++){
            if(board[i][j] == 100) printf(".");
            else if(board[i][j] == 1) printf("W");
            else printf("B");
            }
            printf("\n");
    }   
}

//입력이 진행된 후 5개가 연달아 있는지 확인
int Check(int x, int y){
    int i;
    int check = 0;
    for(i=x; i<Min(x+5, BoardSize); i++){
        if(board[i][y] == 1) check++;
        else if(board[i][y] == 2) check--;
        else break;
    }
    if(check == 5) return 1;
    else if(check == -5) return 2;
    else check =0;

    for(i=y; i<Min(y+5, BoardSize); i++){
        if(board[x][i] == 1) check++;
        else if(board[x][i] == 2) check--;
        else break;
    }   
    if(check == 5) return 1;
    else if(check == -5) return 2;
    else check =0;

    for(i=x; i<Min(x+5, BoardSize); i++){
        if(y<BoardSize){
            if(board[i][y] == 1) check++;
            else if(board[i][y] == 2) check--;
            else break;
            y++;
        }
    }
    if(check == 5) return 1;
    else if(check == -5) return 2;
    else return 0;
}
//바둑판 전체 확인
int Check_All(){
    int i, j, tmp;
    for(i=0; i<BoardSize; i++){
        for(j=0; j<BoardSize; j++){
            tmp = Check(i, j);
            if(tmp) return tmp;
        }
    }
    return 0;
}

int Input(int x, int y){
    if(x>=19 || x<0 || y < 0 || y >= 19) return 0;
    //범위를 넘어서는 입력 불가능
    else{
        if(board[x][y] != 100) return 1;
        //이미 값이 입력된 경우 입력 불가능
        else return 2;
        //나머지는 뭐 그냥 입력하죠
    }
}

int main(){
    int x, y, turn = 0, end = 0, in;
    Empty_Board();
    Print_Board();

    while(!end){
        printf("Enter the location of the stone : ");
        scanf("%d %d", &x, &y);
        in = Input(x, y);
        if(in == 0) printf("Check the range of the checkerboard.\n");
        else if(in == 1) printf("This is the location where the go ball already exists.\n");
        else if(in == 2){
            if(turn %2 == 1){
                board[x][y] = 1;
            }
            else board[x][y] = 2;
            turn++;
                system("cls");
            Print_Board();
        }

        if(turn > BoardSize*BoardSize) break;
        end = Check_All();
    }
    if(end == 1) printf(" BLACK WIN ");
    else if(end == 2) printf(" WHITE WIN");
    else printf("DRAW");
    return 0;
}
