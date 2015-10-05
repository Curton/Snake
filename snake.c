//Funny-Snake Game
//Code by Covey
//2015/09/30 14:00  Movement controlled point       Version 1.00
//2015/10/02 00:55  Add negative direction control  Version 1.01 Beta
//2015/10/02 16:00  Spend 2 hours to debug which "=" written as "==" TAT Version 1.01
//2015/10/05 21:00  Optimize the program structure  Version 1.02
//2015/10/05 22:16  Release version                 Version 2.0
//2015/10/05 23:24  Optimize food appear time       Version 2.1
//2015/10/06 00:02  Add after game over wait time   Version 2.11

#include <stdio.h>
#include <windows.h>
#include <time.h>

int snake_direction = 77;                   // snake start movement direction
int *p_snake_direction = &snake_direction;  // the pointer of ...

//Keyboard getch thread
DWORD WINAPI ThreadProc1( LPVOID lpParam )
{
    while(1)
    {
        get_direction(p_snake_direction);   // Monitor keyboard input
    }
}
void printscreen(int a[10][10], int t,int score)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int width = 10;
    system("cls");//Clean screen
    for(i=0; i<width+1; i++)printf("##");
    printf("\b ");
    for(j=0; j<width; j++)
    {
        printf("\n#");
        for(k=0; k<width; k++)
        {
            if(a[j][k] >= 1)      //snake body
            {
                printf("* ");
            }
            else if(a[j][k] == -1)//food
            {
                printf("& ");
            }
            else
            {
                printf("  ");     //blank
            }
            //printf("%d ",a[j][k]);
        }
        printf("\b#");
    }
    printf("\n");
    for(i=0; i<width+1; i++)printf("##");
    printf("\b ");
    printf("\nScore: %d",score);
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
// print game over screen
void game_over(int score)
{
    int i = 0;
    system("cls");
    for(i=0; i<21; i++)printf("#");
    for(i=0;i<4;i++)printf("\n#                   #");
    printf("\n#    GAME OVER!     #");
    printf("\n#    YOUR SCORE:    #");
    printf("\n#       %03d         #");
    for(i=0;i<4;i++)printf("\n#                   #");
    printf("\n");
    for(i=0; i<21; i++)printf("#");
    sleep(100);
}
// random create food
void random_food(int *pointer)
{
    int n = 0;
    int m = 0;
    int i = 0;
    int x = 0;
    int conflict = 1;
    do
    {
        srand(GetTickCount());// set random seed
        n = rand()%(0-10);
        i++;
        srand(GetTickCount()+i);
        m = rand()%(0-10);
        x = 10*n+m;
        if(*(pointer+x) == 0)
        {
            *(pointer+x) = -1;
            conflict = 0;
        }
    }
    while(conflict);

}
// judge whether input negative direction
int if_negative_direction(int snake_direction,int last_snake_direction,int *pointer)
{
    int i = 0;
        if(snake_direction == 77&&last_snake_direction == 75)
    {
        *pointer = 75;
        i = 1;
        //continue;
    }
    else if(snake_direction == 80&&last_snake_direction == 72)
    {
        *pointer = 72;
        i = 1;
        //continue;
    }
    else if(snake_direction == 72&&last_snake_direction == 80)
    {
        *pointer = 80;
        i = 1;
        //continue;
    }
    else if(snake_direction == 75&&last_snake_direction == 77)
    {
        *pointer = 77;
        i = 1;
        //continue;
    }
    return i;
}
//Start game
int main()
{
    int a[10][10] = {0};             // snake pixel point location
    int *p_a = &a;                   // pointer of a
    int last_snake_direction = snake_direction;
    int snake_length = 4;            //
    int snake_head_x = 0;            // location of snake head of x
    int snake_head_y = 3;            // location of snake head of y
    int food_location[10][10] = {0}; //
    int if_get_direction = 0;        //
    int latency = 400;               // default 400ms
    int score = 0;

    //Star getch thread
    CreateThread(
    NULL,                            // default security attributes
    0,                               // use default stack size
    ThreadProc1,                     // thread function
    NULL,                            // argument to thread function
    0,                               // use default creation flags
    NULL);                           // returns the thread identifier

                                     //set snake head location
    a[snake_head_x][snake_head_y]   = snake_length;
    random_food(p_a);                // initialize snake food
    printscreen(a,0,score);          // print first screen
    do
    {

        //IF INPUT NEGATIVE DIRECTION,KEEP LAST DIRECTION
        if(if_negative_direction(snake_direction,last_snake_direction,p_snake_direction))
        {
            continue;                 //jump out following statement and run "do" again
        }

        if(snake_direction == 0)      //IF INPUT ERROR,GET LAST MOVEMENT
        {
            snake_direction = last_snake_direction;
        }
        else if(snake_direction == 77)//INPUT RIGHT
        {
            if(snake_head_y != 9 && a[snake_head_x][snake_head_y+1] <= 0)//NOT IMPACT WITH THE EDGE AND BODY
            {

                int i = 0;
                int j = 0;
                for(i=0;i<10;i++)
                {
                    for(j=0;j<10;j++)
                    {
                        if (a[i][j] != 0 && a[i][j] > 0)
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
                game_over(score);
                break;
            }
            //Add food when food was eaten
            {
                int i = 0;
                int j = 0;
                int count = 0;
                for(i=0;i<10;i++)
                {
                    for(j=0;j<10;j++)
                    {
                        if (a[i][j] == -1)
                        {
                            count++;
                        }
                    }
                }
                if(count == 0)
                {
                    random_food(p_a);
                    snake_length++;
                    score++;
                }
            }
            printscreen(a,latency,score);
        }
        else if(snake_direction == 80)//INPUT DOWN
        {
            if(snake_head_x != 9 && a[snake_head_x+1][snake_head_y] <= 0)//NOT IMPACT WITH THE EDGE AND BODY
            {
                int i = 0;
                int j = 0;
                for(i=0;i<10;i++)
                {
                    for(j=0;j<10;j++)
                    {
                        if (a[i][j] != 0 && a[i][j] > 0)
                        {
                            a[i][j] --;
                        }
                    }
                }
                a[snake_head_x+1][snake_head_y] = snake_length;
                snake_head_x += 1;
                last_snake_direction = 80;
            }
            else
            {
                game_over(score);
                break;
            }
            //Add food when food was eaten
            {
                int i = 0;
                int j = 0;
                int count = 0;
                for(i=0;i<10;i++)
                {
                    for(j=0;j<10;j++)
                    {
                        if (a[i][j] == -1)
                        {
                            count++;
                        }
                    }
                }
                if(count == 0)
                {
                    random_food(p_a);
                    snake_length++;
                    score++;
                }
            }
            printscreen(a,latency,score);
        }
        else if(snake_direction == 72)//INPUT UP
        {
            if(snake_head_x != 0 && a[snake_head_x-1][snake_head_y] <= 0)//NOT IMPACT WITH THE EDGE AND BODY
            {
                int i = 0;
                int j = 0;
                for(i=0;i<10;i++)
                {
                    for(j=0;j<10;j++)
                    {
                        if (a[i][j] != 0 && a[i][j] > 0)
                        {
                            a[i][j] --;
                        }
                    }
                }
                a[snake_head_x-1][snake_head_y] = snake_length;
                snake_head_x -= 1;
                last_snake_direction = 72;
            }
            else
            {
                game_over(score);
                break;
            }
            //Add food when food was eaten
            {
                int i = 0;
                int j = 0;
                int count = 0;
                for(i=0;i<10;i++)
                {
                    for(j=0;j<10;j++)
                    {
                        if (a[i][j] == -1)
                        {
                            count++;
                        }
                    }
                }
                if(count == 0)
                {
                    random_food(p_a);
                    snake_length++;
                    score++;
                }
            }
            printscreen(a,latency,score);
        }
        else if(snake_direction == 75)//INPUT LEFT
        {
            if(snake_head_y != 0 && a[snake_head_x][snake_head_y-1] <= 0)//NOT IMPACT WITH THE EDGE AND BODY
            {
                int i = 0;
                int j = 0;
                for(i=0;i<10;i++)
                {
                    for(j=0;j<10;j++)
                    {
                        if (a[i][j] != 0 && a[i][j] > 0)
                        {
                            a[i][j] --;
                        }
                    }
                }
                a[snake_head_x][snake_head_y-1] = snake_length;
                snake_head_y -= 1;
                last_snake_direction = 75;
            }
            else
            {
                game_over(score);
                break;
            }

           //Add food when food was eaten
            {
                int i = 0;
                int j = 0;
                int count = 0;
                for(i=0;i<10;i++)
                {
                    for(j=0;j<10;j++)
                    {
                        if (a[i][j] == -1)
                        {
                            count++;
                        }
                    }
                }
                if(count == 0)
                {
                    random_food(p_a);
                    snake_length++;
                    score++;
                }
            }
            printscreen(a,latency,score);
        }

    }//END DO



    while(1);




    return 0;
}



/*
// How record input value to a[][]
int main()
{
    int a[10][10] =
    {
    //   0 1 2 3 4 5 6 7 8 9
        {0,0,0,0,0,0,0,0,0,0},//0
        {0,0,0,0,0,0,0,0,0,0},//1
        {0,0,0,0,0,0,0,0,0,0},//2
        {0,0,0,0,0,1,2,0,0,0},//3
        {0,0,0,0,0,0,3,0,0,0},//4
        {0,0,0,0,0,0,4,5,6,0},//5
        {0,0,0,0,0,0,0,0,7,0},//6
        {0,0,0,0,0,0,0,0,8,9},//7
        {0,0,0,0,0,0,0,0,0,0},//8
        {0,0,0,0,0,0,0,0,0,0},//9
    };
}
*/

