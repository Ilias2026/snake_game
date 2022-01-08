#include <stdlib.h>
void clear()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int randomNumber(int min, int max)
{
    int _rand = rand() % max;
    if (_rand < min)
        return min;
    return _rand;
}
