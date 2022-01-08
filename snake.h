#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
typedef struct linkedNode
{
    int x;
    int y;
    int direction;
    int nextDirection;
    struct linkedNode *next;
    struct linkedNode *prev;
} linkedNode;

typedef struct snake_t
{
    int length;
    int speed;
    int score;
    bool borders;
    linkedNode *head;
    linkedNode *tail;
} snake_t;

void move_node(linkedNode *node, int direction, bool borders);

linkedNode *linkedNode_new(linkedNode *prev, int x, int y, int direction)
{
    linkedNode *node = (linkedNode *)malloc(sizeof(linkedNode));
    node->x = x;
    node->y = y;
    node->direction = direction;
    node->next = NULL;
    node->prev = prev;
    return node;
}

void add_snake_tail(snake_t *snake)
{
    linkedNode *currTail = snake->tail;
    linkedNode *tail = linkedNode_new(currTail, currTail->x, currTail->y, currTail->direction);
    move_node(tail, -tail->direction, snake->borders);
    currTail->next = tail;
    snake->tail = tail;
    snake->length += 1;
}

void init_snake(snake_t *snake, int x, int y, int length)
{
    snake->head = linkedNode_new(NULL, x, y, RIGHT);
    snake->tail = snake->head;
    snake->length = 1;
    for (int i = 0; i < length - 1; i++)
    {
        add_snake_tail(snake);
    }
}

void move_up(linkedNode *node, bool borders)
{
    node->y -= 1;
    if(!borders && node->y < 0) node->y = HEIGHT - 1;
}

void move_down(linkedNode *node, bool borders)
{
    node->y += 1;
    if(!borders && node->y > HEIGHT) node->y = 0;
}

void move_right(linkedNode *node, bool borders)
{
    node->x += 1;
    if(!borders && node->x > WIDTH) node->x = 0;
}

void move_left(linkedNode *node, bool borders)
{
    node->x -= 1;
    if(!borders && node->x < 0) node->x = WIDTH - 1;
}

void move_node(linkedNode *node, int direction, bool borders)
{
    switch (direction)
    {
    case UP:
        move_up(node, borders);
        break;
    case DOWN:
        move_down(node, borders);
        break;
    case LEFT:
        move_left(node, borders);
        break;
    case RIGHT:
        move_right(node, borders);
        break;
    default:
        break;
    }
}

int move_snake(snake_t *snake)
{
    linkedNode *tail = snake->tail;
    snake->head->prev = tail; //make the tail point to the head with prev
    tail->prev->next = NULL; //make previous the end
    snake->tail = tail->prev;
    tail->x = snake->head->x;
    tail->y = snake->head->y;
    tail->direction = snake->head->direction;
    tail->next = snake->head;
    tail->prev = NULL;
    snake->head = tail; //make tail the new head
    move_node(snake->head, snake->head->direction, snake->borders);
    return 0;
}

linkedNode* is_snake_here(linkedNode *start, int x, int y)
{
    linkedNode *current = start;
    while (current != NULL)
    {
        if (current->x == x && current->y == y)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}