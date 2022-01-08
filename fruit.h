typedef struct Fruit
{
    int x;
    int y;
} Fruit;

int available_fields_count(snake_t *snake)
{
    return ((WIDTH * HEIGHT) - snake->length);
}

int *get_available_fields(snake_t *snake, char matrix[HEIGHT][WIDTH])
{
    int length = available_fields_count(snake) * 2;
    long size = sizeof(int) * length;
    int *available_fields = (int *)malloc(size); //[x0,y0, x1,y1, ...]
    int count = 0;
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (matrix[i][j] != SNAKE_SHOW)
            {
                available_fields[count] = j;     //set x
                available_fields[count + 1] = i; //set y
                count += 2;
            }
        }
    }
    return available_fields;
}

Fruit *add_fruit(snake_t *snake, char matrix[HEIGHT][WIDTH])
{
    Fruit *fruit = (Fruit *)malloc(sizeof(Fruit));
    int *available = get_available_fields(snake, matrix);
    int size = available_fields_count(snake) * 2;
    int randomIndex = randomNumber(0, size - 1);
    fruit->x = available[randomIndex];
    fruit->y = available[randomIndex + 1];
    free(available);
    return fruit;
}