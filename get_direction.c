#include<stdio.h>
// 72->UP   80->DOWN    75->LEFT    77->RIGHT   0->ERROR
int get_direction()
{
    int key_1 = getch();
    int key_2 = 0;
    if(key_1 == 224)
    {
        key_2 = getch();
    }
    else if(key_1 == 72||key_1 == 75||key_1 == 77||key_1 == 80)
    {
        key_2 = key_1;
    }
    return key_2;
}
/*
int main()
{
    do
    {
        int c = 0;
        c = get_direction();
        printf("%d\n",c);

    }
    while(1);
    return 0;
}
*/
