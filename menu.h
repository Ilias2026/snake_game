#include <stdio.h>
void show_menu()
{
    int choice;
    printf("1.Start the game\n2.No Borders\n3.Quit\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        start_game(true);
        break;
    case 2:
        start_game(false);
        break;
    case 3:
        exit(0);
        break;
    default:
        break;
    }
    show_menu();
}