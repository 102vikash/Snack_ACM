#include<iostream>
#include<conio.h>
#include<time.h>
#include<windows.h>
#define WIDTH 20
#define HEIGHT 20
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define MAX 100
#define SPEED 250
using namespace std;
void gotoxy(int y,int x)
{
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
struct Position
    {
        int X;
        int Y;
    };
class SnackGame
{
private:
    int fruitX,fruitY,fruit_status;
    int Length;
    int last_move;
    int score;
    Position snack_piece[MAX];

public:
    SnackGame()
    {
        fruit_status=0;
        last_move=DOWN;
        fruitX=rand()%(HEIGHT-1)+1;
        fruitY=rand()%(WIDTH-1)+1;
        srand(time(NULL));
        snack_piece[0].X=1;
        snack_piece[0].Y=1;
        Length=1;
        score=0;
    }
    void setGame();
    void oneStep();
    void inputGame();
    int speed();
    void fruitGame();
    int finishGame();
    void back_side();
    bool isEat();
    bool isOver();
};
int SnackGame::speed()
{
   return  SPEED-Length*8<=10 ? 10:SPEED-Length*8;
}
void SnackGame::back_side()
{
    if(snack_piece[0].X>=HEIGHT)
    snack_piece[0].X=1;
    else if(snack_piece[0].X<=0)
    snack_piece[0].X=HEIGHT-1;
    else if(snack_piece[0].Y>=WIDTH)
    snack_piece[0].Y=1;
    else if(snack_piece[0].Y<=0)
    snack_piece[0].Y=WIDTH-1;
}
bool SnackGame::isOver()
{
    for(int i=1;i<Length;i++)
    {
        if(snack_piece[0].X==snack_piece[i].X && snack_piece[0].Y==snack_piece[i].Y)
        return true;
    }
    return false;
}
bool SnackGame::isEat()
{
    if(snack_piece[0].X==fruitX && snack_piece[0].Y==fruitY)
        return 1;
        return 0;
}
int SnackGame::finishGame()
{
        if(isEat())
        {
            fruit_status=0;
            Length++;
            //oneStep();
            score+=20;
        }
        if(isOver())
        return 1;
        return 0;
}
void SnackGame::inputGame()
{
    if(kbhit())
    {
        getch();
        switch(getch())
        {
        case 72:
            if(last_move!=DOWN)
            last_move=UP;
            break;
        case 75:
            if(last_move!=RIGHT)
            last_move=LEFT;
            break;
        case 80:
            if(last_move!=UP)
            last_move=DOWN;
            break;
        case 77:
            if(last_move!=LEFT)
            last_move=RIGHT;
            break;
        default:
            cout<<"Something went wrong ";

        }
    }
}
void SnackGame::setGame()
{
    system("cls");
    for(int i=0;i<WIDTH;i++)
    cout<<"#";
    cout<<endl;
    gotoxy(HEIGHT,0);
    for(int i=0;i<WIDTH;i++)
    cout<<"#";
    for(int i=0;i<HEIGHT;i++){
    cout<<"#";
    gotoxy(i,WIDTH);
    cout<<"#"<<endl;
    }
    cout<<"\nSCORE :"<<score;
    fruitGame();
    for(int i=0;i<Length;i++)
    {
        gotoxy(snack_piece[i].X,snack_piece[i].Y);
        cout<<'O';
    }
    inputGame();
    oneStep();
}
void SnackGame::fruitGame()
{
    if(fruit_status==0)
    {
    fruitX=rand()%(HEIGHT-1)+1;
    fruitY=rand()%(WIDTH-1)+1;
    fruit_status=1;
    }
    gotoxy(fruitX,fruitY);
   cout<<"$";
}
void SnackGame::oneStep()
{
    for(int i=Length-1;i!=0;i--)
    {
        snack_piece[i].X=snack_piece[i-1].X;
        snack_piece[i].Y=snack_piece[i-1].Y;
    }
    switch(last_move)
    {
    case DOWN:
        (snack_piece[0].X)++;
        break;
    case UP:
        (snack_piece[0].X)--;
        break;
    case RIGHT:
        (snack_piece[0].Y)++;
        break;
    case LEFT:
        (snack_piece[0].Y)--;
        break;
    default:
        cout<<"Something went wrong";
        //exit(0);
    }
    back_side();
}

int main()
{
    SnackGame obj;
    while(!obj.finishGame()){
    obj.setGame();
    Sleep(obj.speed());
    }
    gotoxy(9,13);
    cout<<"GameOver!";
   getch();
   return 0;
}
