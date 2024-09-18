#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

void welcome();
void border();
void Pos(int x, int y);
void getRandomPos(int *x, int *y);
void initSnake();
void createFood();
int inSnake(int x, int y);
void snakeMove();
int getDirection();

typedef struct Node{
    int x;
    int y;
    struct Node *next; //c语言中需要注明strcut
} node;

node *head;
node food;
int reCreateFood;
int fail;
int score, add = 10;

int dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};
int d = -1;

int main(){
    welcome();
    border();
    initSnake();
    createFood();

    while(1){
        if(fail)
            break;
        
        if(reCreateFood){
            createFood();
            reCreateFood = 0;
        }

        snakeMove();
        Sleep(200);

        d = getDirection();
    }
    Pos(0, 24);
    printf("\n");

    return 0;
}

void welcome(){
    system("mode con cols=100 lines=30");
    system("cls");

    Pos(38, 6);
    printf("Welcome come to SnakeGame\n");
    Pos(38, 8);
    printf("keyboard control direction\n");
    Pos(45, 10);
    printf("ESC For Exit\n");
    Pos(42, 12);
    printf("Enter For Begin\n");
    getchar();
    system("cls");
}

void border(){
    for(int i = 0; i < 60; i++){
        Pos(i, 0);
        printf(" ");
        Pos(i, 25);
        printf(" ");
    }

    for(int i = 1; i < 25; i++){
        Pos(0, i);
        printf(" ");
        Pos(59, i);
        printf(" ");
    }    
}

void Pos(int x, int y){
    COORD pos;
    pos.X = x;
    pos.Y = y;

    HANDLE handleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handleOutput, pos);
}

void initSnake(){
    head = (node *)malloc(sizeof(node));
    head->x = rand() % 58 + 1;
    head->y = rand() % 24 + 1;
    head->next = NULL;

    Pos(head->x, head->y);
    printf("*");
}

void getRandomPos(int *x, int *y){
    srand((unsigned int)time(NULL));
    *x = rand() % 58 + 1;
    *y = rand() % 24 + 1;
}

int inSnake(int x, int y){
    node *p = head->next;
    while(p){
        if(x == p->x && y == p->y)
            return 1;
        p = p->next;
    }
}

void createFood(){
    int x, y;
    getRandomPos(&x, &y);
    if(inSnake(x, y))
        createFood();
    food.x = x;
    food.y = y;
    Pos(x, y);
    printf("$");
}

int getDirection(){
    if((GetAsyncKeyState(VK_UP) & 0x8000) && d != 1)
        d = 0;
    else if((GetAsyncKeyState(VK_DOWN) & 0x8000) && d != 0)
        d = 1;
    else if((GetAsyncKeyState(VK_LEFT) & 0x8000) && d != 3)
        d = 2;
    else if((GetAsyncKeyState(VK_RIGHT) & 0x8000) && d != 2)
        d = 3;
    return d;
}

void snakeMove()
{
    if(d == -1)
        while(d == -1)
            d = getDirection();
    
    node *newHead = (node*)malloc(sizeof(node));
    newHead->x = head->x + dx[d];
    newHead->y = head->y + dy[d];
    newHead->next = head;
    head = newHead;

    node *p = head;
    if(inSnake(p->x, p->y) || (p->x == 59 || p->y == 25))
        fail = 1;
    else if(p->x != food.x || p->y != food.y){
        Pos(p->x, p->y);
        printf("*");

        while(p->next->next)
            p = p->next;
        Pos(p->next->x, p->next->y);
        printf(" ");
        p->next = NULL;
    } else {
        reCreateFood = 1;
        score += add;
        Pos(p->x, p->y);
        printf("*");
    }
    Pos(61, 25);
    printf("Score: %d", score);
}