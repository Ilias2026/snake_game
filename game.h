#define KEY_UP 119    // w
#define KEY_DOWN 115  // s
#define KEY_LEFT 97   // a
#define KEY_RIGHT 100 // d

#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2

#define WIDTH 50
#define HEIGHT 50
#define SPEED 15

#define EMPTY '.'
#define SNAKE_SHOW '#'

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#include "./snake.h"
#include "./fruit.h"

void key_down(snake_t *snake);
void print(snake_t *snake, char matrix[HEIGHT][WIDTH], Fruit *fruit, int score);

bool isGameOver(snake_t *snake, bool borders)
{
    linkedNode *head = snake->head;
    linkedNode *here = is_snake_here(snake->head->next, head->x, head->y);
    if (here != NULL)
    {
        return true;
    }
    if (borders)
    {
        return head->x < 0 || head->x >= WIDTH || head->y < 0 || head->y >= HEIGHT;
    }
    return false;
}

bool eatFruit(snake_t *snake, Fruit *fruit)
{
    if (snake->head->x == fruit->x && snake->head->y == fruit->y)
    {
        return true;
    }
    return false;
}

void refillMatrix(snake_t *snake, char matrix[HEIGHT][WIDTH])
{
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            matrix[i][j] = EMPTY;
    linkedNode *current = snake->head;
    //fill matrix with snake
    while (current != NULL)
    {
        matrix[current->y][current->x] = SNAKE_SHOW;
        current = current->next;
    }
}

bool start_game(bool borders)
{
    //init
    //init rand generator
    srand(time(NULL));
    printf("You started to play the game.\n");

    int ms = 1000 / SPEED;
    int us = ms * 1000;

    int score = 0;

    //new snake
    snake_t *snake = (snake_t *)malloc(sizeof(snake_t));
    init_snake(snake, randomNumber(1, WIDTH / 2), randomNumber(1, HEIGHT / 2), 5);
    snake->borders = borders;
    char matrix[HEIGHT][WIDTH];
    refillMatrix(snake, matrix);
    Fruit *fruit = add_fruit(snake, matrix);
    char ch;
    while (true)
    {
        //check if game is over
        if (isGameOver(snake, borders))
        {
            printf("Game Over!\n");
            return false;
        }

        if (eatFruit(snake, fruit))
        {
            add_snake_tail(snake); //add to snake
            refillMatrix(snake, matrix);
            fruit = add_fruit(snake, matrix);
            score += 1;
        }
        else
        {
            refillMatrix(snake, matrix);
            //fill matrix with fruits
            matrix[fruit->y][fruit->x] = 'O';
        }
        //check if key is clicked
        if (kbhit())
        {
            key_down(snake);
        }
        usleep(us); //sleep for 100ms
        move_snake(snake);
        print(snake, matrix, fruit, score);
    }
}

void key_down(snake_t *snake)
{
    int key = (int)getchar();
    int direction = snake->head->direction;
    switch (key)
    {
    case KEY_UP:
        direction = UP;
        break;
    case KEY_DOWN:
        direction = DOWN;
        break;
    case KEY_LEFT:
        direction = LEFT;
        break;
    case KEY_RIGHT:
        direction = RIGHT;
        break;
    default:
        break;
    }
    if (snake->head->direction + direction == 0)
        return; //same direction but backwards
    snake->head->direction = direction;
}

void print(snake_t *snake, char matrix[HEIGHT][WIDTH], Fruit *fruit, int score)
{
    clear();

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            printf(" %c ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("SNAKE: X: %d, Y: %d\n", snake->head->x, snake->head->y);
    printf("Fruit: X: %d, Y: %d\n", fruit->x, fruit->y);
    printf("SCORE: %d\n", score);
}