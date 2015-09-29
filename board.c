#include <stdio.h>
#include <time.h>
void delay(int t)
{
    time_t t1,t2,t3;
    int i = 1;
    t1 = time(0);
    do
    {
        t2 = time(0);
        t3 = t2 -t1;
        if(t3 == t)
        {
            i = 0;
        }
    }
    while(i);
}

int printscreen(int a[10][10], int t)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int width = 10;
    system("cls");
    for(i=0; i<width+2; i++)printf("##");
    printf("\b ");
    for(j=0; j<width; j++)
    {
        printf("\n# ");
        for(k=0; k<width; k++)
        {
            if(a[j][k] == 1)
            {
                printf("* ");
            }
            else
            {
                printf("  ");
            }
            //printf("%d ",a[j][k]);
        }
        printf("#");
    }
    printf("\n");
    for(i=0; i<width+2; i++)printf("##");
    printf("\b ");

    delay(t);


}

int main()
{
    int Screen[10][10] = {0};
    int x = 0, y = 0;
    for (y=0;y<10;y++)
    {
        for(x=0;x<10;x++)
        {
            Screen[y][x] = 1;
            //printf("Debug X=%d Y=%d\n",y,x);
            printscreen(Screen,1);
            Screen[y][x] = 0;
        }
    }
    return 0;
}

/*
// How to input
int main()
{
    int a[10][10] =
    {
    //   0 1 2 3 4 5 6 7 8 9
        {0,0,0,0,0,0,0,0,0,0},//0
        {0,0,0,0,0,0,0,0,0,0},//1
        {0,0,0,0,0,0,0,0,0,0},//2
        {0,0,0,0,0,5,0,0,0,0},//3
        {0,0,0,0,0,0,5,0,0,0},//4
        {0,0,0,0,0,0,0,5,0,0},//5
        {0,0,0,0,0,0,0,0,5,0},//6
        {0,0,0,0,0,0,0,0,0,5},//7
        {0,0,0,0,0,0,0,0,0,0},//8
        {0,0,0,0,0,0,0,0,0,0},//9

    };
    output_screen(a);
    output_screen(a);


}
*/
