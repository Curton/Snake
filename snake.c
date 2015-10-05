//Funny-Snake Game
//Code by Covey
//2015/09/30 14:00  Movement controlled point       Version 1.00
//2015/10/02 00:55  Add negative direction control  Version 1.01 Beta
//2015/10/02 16:00  Spend 2 hours to debug which "=" written as "==" TAT Version 1.01

#include <stdio.h>
#include <windows.h>
#include <time.h>

int snake_direction = 77;                   //snake start movement direction
int *p_snake_direction = &snake_direction;   //the pointer of ...

//Keyboard getch thread
DWORD WINAPI ThreadProc1( LPVOID lpParam )
{
    while(1)
    {
        get_direction(p_snake_direction);   //Monitor keyboard input
    }
}
//game_over(int s)
//{
//    ;
//}
//print screen
void printscreen(int a[10][10], int t)
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
            if(a[j][k] >= 1)
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

    Sleep(t);


}
// 72->UP   80->DOWN    75->LEFT    77->RIGHT   0->ERROR
int get_direction(int *pointer)
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
    *pointer = key_2;
}
void game_over()
{
    int i = 0;
    system("cls");
    for(i=0; i<21; i++)printf("#");
    for(i=0;i<4;i++)printf("\n#                   #");
    printf("\n#    GAME OVER!     #");
    for(i=0;i<5;i++)printf("\n#                   #");
    printf("\n");
    for(i=0; i<21; i++)printf("#");
}
//Start
int main()
{
    int a[10][10] = {0};             //snake pixel point location
    //int pixel_live[10][10] = {0};  //pixel live time
    int last_snake_direction = snake_direction;
    int snake_length = 5;            //don't change


    int snake_head_x = 0;            //location of snake head of x
    int snake_head_y = 3;            //location of snake head of y
    int food_location[10][10] = {0}; //
    int if_get_direction = 0;        //

    //
    CreateThread(
    NULL,                            // default security attributes
    0,                               // use default stack size
    ThreadProc1,                     // thread function
    NULL,                            // argument to thread function
    0,                               // use default creation flags
    NULL);                           // returns the thread identifier

    //set snake head location
    a[snake_head_x][snake_head_y]   = snake_length;
    //a[snake_head_x][snake_head_y-1] = 3;
    //a[snake_head_x][snake_head_y-2] = 2;
    //a[snake_head_x][snake_head_y-2] = 1;
    printscreen(a,0);
    do
    {
        //IF INPUT NEGATIVE DIRECTION,KEEP LAST DIRECTION
        if(snake_direction == 77&&last_snake_direction == 75)
        {
            snake_direction = 75;
            continue;
        }
        else if(snake_direction == 80&&last_snake_direction == 72)
        {
            snake_direction = 72;
            continue;
        }
        else if(snake_direction == 72&&last_snake_direction == 80)
        {
            snake_direction = 80;
            continue;
        }
        else if(snake_direction == 75&&last_snake_direction == 77)
        {
            snake_direction = 77;
           // printf("888888888888888888888888888");
            continue;
        }

        if(snake_direction == 0)     //IF INPUT ERROR,GET LAST MOVEMENT
        {
            snake_direction = last_snake_direction;
        }
        else if(snake_direction == 77)//INPUT RIGHT
        {
            if(snake_head_y != 9)//NOT IMPACT WITH THE EDGE
            {
                int i = 0;
                int j = 0;
                for(i=0;i<10;i++)
                {
                    for(j=0;j<10;j++)
                    {
                        if (a[i][j] != 0)
                        {
                            a[i][j] --;
                        }
                    }
                }
                a[snake_head_x][snake_head_y+1] = snake_length;
                snake_head_y += 1;
                last_snake_direction = 77;//RECORD LAST MOVEMENT
            }
            else
            {
                game_over();
                break;
            }

            printscreen(a,500);
        }
        else if(snake_direction == 80)//INPUT DOWN
        {
            if(snake_head_x != 9)
            {
                int i = 0;
                int j = 0;
                for(i=0;i<10;i++)
                {
                    for(j=0;j<10;j++)
                    {
                        if (a[i][j] != 0)
                        {
                            a[i][j] --;
                        }
                    }
                }
                a[snake_head_x+1][snake_head_y] = snake_length;
                snake_head_x += 1;
                last_snake_direction = 80;
            }

            printscreen(a,500);
        }
        else if(snake_direction == 72)//INPUT UP
        {
            if(snake_head_x != 0)
            {
                int i = 0;
                int j = 0;
                for(i=0;i<10;i++)
                {
                    for(j=0;j<10;j++)
                    {
                        if (a[i][j] != 0)
                        {
                            a[i][j] --;
                        }
                    }
                }
                a[snake_head_x-1][snake_head_y] = snake_length;
                snake_head_x -= 1;
                last_snake_direction = 72;
            }
             printscreen(a,500);
        }
        else if(snake_direction == 75)//INPUT LEFT
        {
            if(snake_head_y != 0)
            {
                int i = 0;
                int j = 0;
                for(i=0;i<10;i++)
                {
                    for(j=0;j<10;j++)
                    {
                        if (a[i][j] != 0)
                        {
                            a[i][j] --;
                        }
                    }
                }
                a[snake_head_x][snake_head_y-1] = snake_length;
                snake_head_y -= 1;
                last_snake_direction = 75;
            }
            printscreen(a,500);
        }

    }//END DO



    while(1);




    return 0;
}



/*
// How to input value to a[][]
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
