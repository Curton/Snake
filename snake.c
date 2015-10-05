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
    for(i=0; i<width+1; i++)printf("##");
    printf("\b ");
    for(j=0; j<width; j++)
    {
        printf("\n#");
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
        printf("\b#");
    }
    printf("\n");
    for(i=0; i<width+1; i++)printf("##");
    printf("\b ");

    delay(t);


}

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

int main()
{
    int a[10][10] = {0};             //snake pixel point location
    int pixel_live[10][10] = {0};    //pixel live time
    int keyboard_direction = 1;      //
    int snake_length = 3;            //
    int snake_direction = 0;         //snake movement direction

    int snake_head_x = 0;            //location of snake head of x
    int snake_head_y = 0;            //location of snake head of y
    int food_location[10][10] = {0}; //
    int if_get_direction = 0;        //


    //set snake head location
    a[snake_head_x][snake_head_y] = 1;
    printscreen(a,0);
    do
    {
//        if(if_get_direction == 0)
//        {
            keyboard_direction = get_direction();
//            if_get_direction = 1;
//        }

        if(keyboard_direction == 77)//RIGHT
        {

            if(snake_head_y != 9)
            {
                a[snake_head_x][snake_head_y] = 0;
                a[snake_head_x][snake_head_y+1] = 1;
                snake_head_y += 1;
            }
            printscreen(a,0);
        }
        else if(keyboard_direction == 80)//DOWN
        {
            if(snake_head_x != 9)
            {
                a[snake_head_x][snake_head_y] = 0;
                a[snake_head_x+1][snake_head_y] = 1;
                snake_head_x += 1;
            }
            printscreen(a,0);
        }
        else if(keyboard_direction == 72)//UP
        {
            if(snake_head_x != 0)
            {
                a[snake_head_x][snake_head_y] = 0;
                a[snake_head_x-1][snake_head_y] = 1;
                snake_head_x -= 1;
            }
            printscreen(a,0);
        }
        else if(keyboard_direction == 75)//LEFT
        {
            if(snake_head_y != 0)
            {
                a[snake_head_x][snake_head_y] = 0;
                a[snake_head_x][snake_head_y-1] = 1;
                snake_head_y -= 1;
            }

        }
        printscreen(a,0);
//        a[snake_head_x][snake_head_y] = 0;
//        a[snake_head_x][snake_head_y+1] = 1;
//        snake_head_y += 1;
//        printscreen(a,1);



    }
    while(1);




    return 0;
}

/*
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
*/

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
