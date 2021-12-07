#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <time.h>
using namespace std;

struct snake {
    int x, y;
} tail[100], head;

struct fruit {
    int x, y;
} fruit, fruit2, fruit3, fruit4, fruit5, fruit6;

bool gameOver, lateGame;
const int width = 30; //map dimensions
const int height = 20;
int nTail, score;
enum eDirection { STOP, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup() {
    gameOver = false;
    lateGame = false;
    dir = STOP;
    srand(time(NULL));
    head.x = width / 2; //to place the snake in the middle by dividing the width by 2
    head.y = height / 2;
    fruit.x = rand() % width;
    fruit.y = rand() % height;
    fruit2.x = rand() % width;
    fruit2.y = rand() % height;
    score = 0;
}

void Draw() {
    system("cls"); //clears the screen and produces a lot of flickering.
    for (int i = 0; i < width+2; i++)
        cout << "_";
    cout << "\n";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#";
            if (i == head.y && j == head.x)
                printf("O");
            else if (i == fruit.y && j == fruit.x)
                printf("Q");
            else if (i == fruit2.y && j == fruit2.x)
                printf("G");
            else if (i == fruit3.y && j == fruit3.x)
                printf("U");
            else if (i == fruit4.y && j == fruit4.x)
                printf("V");
            else if (i == fruit5.y && j == fruit5.x)
                printf("X");
            else if (i == fruit6.y && j == fruit6.x)
                printf("Z");
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {      
                    if(tail[k].x == j && tail[k].y == i) {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print) 
                    cout << " ";
            }
            if (j == width - 1)
                cout << "#";
        }
        cout << "\n";
    }

    for (int i = 0; i < width+2; i++)
        cout << "-";
    cout << "\n";
    cout << "Score: " << score << "\n";
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic() {
    int prevX = tail[0].x;
    int prevY = tail[0].y;
    int prev2X, prev2Y;
    tail[0].x = head.x;
    tail[0].y = head.y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tail[i].x;
        prev2Y = tail[i].y;
        tail[i].x = prevX;
        tail[i].y = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir) {
    case LEFT:
        head.x--;
        break;
    case RIGHT:
        head.x++;
        break;
    case UP:
        head.y--;
        break;
    case DOWN:
        head.y++;
        break;
    default:
        break;
    }
    /* this is if the game should end when the snake touches the edges of the map
    if (x > width || x < 0 || y > height || y < 0) {
        gameOver = true;
    }*/
    if (head.x >= width) head.x = 0; else if (head.x < 0) head.x = width - 1;
    if (head.y >= height) head.y = 0; else if (head.y < 0) head.y = height - 1;
    for (int i = 0; i < nTail; i++) {
        if (tail[i].x == head.x && tail[i].y == head.y) {
            gameOver = true;
        }
    }
    if (head.x == fruit.x && head.y == fruit.y) {
        score += 10;
        fruit.x = rand() % width;
        fruit.y = rand() % height;
        nTail++;
    }
    if (head.x == fruit2.x && head.y == fruit2.y) {
        score += 10;
        fruit2.x = rand() % width;
        fruit2.y = rand() % height;
        nTail++;
    }
    if (nTail > 5) {
        if (!lateGame) {
            fruit3.x = rand() % width;
            fruit3.y = rand() % height;
            fruit4.x = rand() % width;
            fruit4.y = rand() % height;
            fruit5.x = rand() % width;
            fruit5.y = rand() % height;
            fruit6.x = rand() % width;
            fruit6.y = rand() % height;
            lateGame = true;
        }
        if (head.x == fruit3.x && head.y == fruit3.y) {
            score += 10;
            fruit3.x = rand() % width;
            fruit3.y = rand() % height;
            nTail++;
        }
        if (head.x == fruit4.x && head.y == fruit5.y) {
            score += 10;
            fruit4.x = rand() % width;
            fruit4.y = rand() % height;
            nTail++;
        }
        if (head.x == fruit5.x && head.y == fruit5.y) {
            score += 10;
            fruit5.x = rand() % width;
            fruit5.y = rand() % height;
            nTail++;
        }
        if (head.x == fruit6.x && head.y == fruit6.y) {
            score += 10;
            fruit6.x = rand() % width;
            fruit6.y = rand() % height;
            nTail++;
        }
    }
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        //Sleep(10); //slows game a bit
    }
    return 0;
}
