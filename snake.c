//Funny-Snake Game
//Code by Covey
//2015/09/30 14:00  Movement controlled point       Version 1.0.0
//2015/10/02 00:55  Add negative direction control  Version 1.0.1 Beta
//2015/10/02 16:00  Spend 2 hours to debug which
//                  "=" was written as "==" TAT     Version 1.0.1
//2015/10/05 21:00  Optimize the program structure  Version 1.0.2
//2015/10/05 22:16  Release version                 Version 2.0.0
//2015/10/05 23:24  Optimize food appear time       Version 2.1.0
//2015/10/06 00:02  Add after game over wait time   Version 2.1.1
//2015/10/06 00:42  Add auto increase difficulty    Version 2.2.0
//2015/10/06 16:27  Snake extend at the end         Version 2.3.0
//2015/10/06 18:46  Improve program structure       Version 2.3.1
//2015/10/06 23:15  Adapt with Microsoft VS2010     Version 2.3.2
//2015/10/09 21:18  Add ready time setting
//                  add WASD control support
//                  Add restart game and comment
//                  Add sound and debug mode        Version 2.5.0
//2015/10/10        Improve the code quality        Version 2.5.1
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
int debug_mode         = 0;                    // set 1 to open debug mode
int snake_direction    = 77;                   // snake start movement direction
int *p_snake_direction = &snake_direction;     // the pointer of ...
int wasd_support       = 1;                    // Whether support WASD input
int initial_difficulty = 400;                  // set initial difficulty
int difficulty_limit   = 200;                  // set difficulty limit (ms)
// goto the end of the program see function's definition
DWORD WINAPI ThreadProc1( LPVOID lpParam );
int game_over(int score);
int if_negative_direction(int snake_direction,int last_snake_direction,int *pointer);
void get_direction(int *pointer,int wasd);
void printscreen(int a[10][10], int t,int score);
void random_food(int *pointer);
void ready();
void menu();

//Start game
int main()
{
    int latency       = initial_difficulty;
    int last_snake_direction = snake_direction;
    int a[10][10]     = {0};         // snake pixel point location
    //int *p_a          = a;          // pointer of a
    int snake_length  = 4;           // initial snake length
    int snake_head_x  = 0;           // location of snake head of x
    int snake_head_y  = 0;           // location of snake head of y
    int score         = 0;           // do not change this value to cheating
    int ready_screen  = 3;           // whether display the ready screen, 0 is not display, value is the wait time
    int restart       = 0;           // record restart information
    int game_over_return;            // record the return value of game_over()

    //menu();
                                     // Start getch thread
    CreateThread(
    NULL,                            // default security attributes
    0,                               // use default stack size
    ThreadProc1,                     // thread function
    NULL,                            // argument to thread function
    0,                               // use default creation flags
    NULL);                           // returns the thread identifier



    do//DO 1: for restart the game
    {
        random_food(a);                // initialize snake food
        ready(ready_screen);             // ready for start
        printscreen(a,0,score);          // print first screen

        do// DO 2: main program
        {

            //IF INPUT NEGATIVE DIRECTION,KEEP LAST DIRECTION
            if(if_negative_direction(snake_direction,last_snake_direction,p_snake_direction))
            {
                continue;                 //jump out following statement and run "do" again
            }

            if(snake_direction == 0 || snake_direction == 49 || snake_direction == 50)//IF INPUT ERROR,GET LAST MOVEMENT
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
                                a[i][j] --; // all pixel live time minus 1
                            }
                        }
                    }
                    a[snake_head_x][snake_head_y+1] = snake_length; // add pixel live time to snake head
                    snake_head_y += 1;
                    last_snake_direction = 77;//RECORD LAST MOVEMENT
                }
                else
                {
                    game_over_return = game_over(score);
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
                    if(count == 0)// if eat food, all pixel live time plus 1
                    {
                        {
                            int i = 0;
                            int j = 0;
                            //int count = 0;
                            for(i=0;i<10;i++)
                            {
                                for(j=0;j<10;j++)
                                {
                                    if (a[i][j] > 0)
                                    {
                                        a[i][j] ++;
                                    }
                                }
                            }
                        }
                        // add 1 pixel live time at the snake tail
                        {
                            int i = 0;
                            int j = 0;
                            //int count = 0;
                            for(i=0;i<10;i++)
                            {
                                for(j=0;j<10;j++)
                                {
                                    // Determine the direction of the tail
                                    if (a[i][j] == 2 && a[i][j+1] == 3)
                                    {
                                        a[i][j-1] = 1;
                                    }
                                    else if(a[i][j] == 2 && a[i][j-1] == 3)
                                    {
                                        a[i][j+1] = 1;
                                    }
                                    else if(a[i][j] == 2 && a[i+1][j] == 3)
                                    {
                                        a[i-1][j] = 1;
                                    }
                                    else if(a[i][j] == 2 && a[i-1][j] == 3)
                                    {
                                        a[i+1][j] = 1;
                                    }
                                }
                            }
                        }
                        printf("\a");
                        random_food(a);
                        snake_length++;
                        score++;
                        latency -= score; // Auto increase difficulty
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
                                a[i][j] --; // all pixel live time minus 1
                            }
                        }
                    }
                    a[snake_head_x+1][snake_head_y] = snake_length; // add pixel live time to snake head
                    snake_head_x += 1;
                    last_snake_direction = 80;
                }
                else
                {
                    game_over_return = game_over(score);
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
                    if(count == 0)// if eat food, all pixel live time plus 1
                    {
                        int i = 0;
                        int j = 0;
                        //int count = 0;
                        for(i=0;i<10;i++)
                        {
                            for(j=0;j<10;j++)
                            {
                                if (a[i][j] > 0)
                                {
                                    a[i][j] ++;
                                }

                            }
                        }
                        // add 1 pixel live time at the snake tail
                        {
                            int i = 0;
                            int j = 0;
                            //int count = 0;
                            for(i=0;i<10;i++)
                            {
                                for(j=0;j<10;j++)
                                {
                                    // Determine the direction of the tail
                                    if (a[i][j] == 2 && a[i][j+1] == 3)
                                    {
                                        a[i][j-1] = 1;
                                    }
                                    else if(a[i][j] == 2 && a[i][j-1] == 3)
                                    {
                                        a[i][j+1] = 1;
                                    }
                                    else if(a[i][j] == 2 && a[i+1][j] == 3)
                                    {
                                        a[i-1][j] = 1;
                                    }
                                    else if(a[i][j] == 2 && a[i-1][j] == 3)
                                    {
                                        a[i+1][j] = 1;
                                    }
                                }
                            }
                        }
                        printf("\a");
                        random_food(a);
                        snake_length++;
                        score++;
                        latency -= score; // Auto increase difficulty
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
                                a[i][j] --; // all pixel live time minus 1
                            }
                        }
                    }
                    a[snake_head_x-1][snake_head_y] = snake_length; // add pixel live time to snake head
                    snake_head_x -= 1;
                    last_snake_direction = 72;
                }
                else
                {
                    game_over_return = game_over(score);
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
                    if(count == 0)// if eat food, all pixel live time plus 1
                    {
                        int i = 0;
                        int j = 0;
                        //int count = 0;
                        for(i=0;i<10;i++)
                        {
                            for(j=0;j<10;j++)
                            {
                                if (a[i][j] > 0)
                                {
                                    a[i][j] ++;
                                }
                            }
                        }
                        // add 1 pixel live time at the snake tail
                        {
                            int i = 0;
                            int j = 0;
                            //int count = 0;
                            for(i=0;i<10;i++)
                            {
                                for(j=0;j<10;j++)
                                {
                                    // Determine the direction of the tail
                                    if (a[i][j] == 2 && a[i][j+1] == 3)
                                    {
                                        a[i][j-1] = 1;
                                    }
                                    else if(a[i][j] == 2 && a[i][j-1] == 3)
                                    {
                                        a[i][j+1] = 1;
                                    }
                                    else if(a[i][j] == 2 && a[i+1][j] == 3)
                                    {
                                        a[i-1][j] = 1;
                                    }
                                    else if(a[i][j] == 2 && a[i-1][j] == 3)
                                    {
                                        a[i+1][j] = 1;
                                    }
                                }
                            }
                        }
                        printf("\a");
                        random_food(a);
                        snake_length++;
                        score++;
                        latency -= score; // Auto increase difficulty
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
                                a[i][j] --; // all pixel live time minus 1
                            }
                        }
                    }
                    a[snake_head_x][snake_head_y-1] = snake_length; // add pixel live time to snake head
                    snake_head_y -= 1;
                    last_snake_direction = 75;
                }
                else
                {
                    game_over_return = game_over(score);
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
                    if(count == 0)// if eat food, all pixel live time plus 1
                    {
                        int i = 0;
                        int j = 0;
                        //int count = 0;
                        for(i=0;i<10;i++)
                        {
                            for(j=0;j<10;j++)
                            {
                                if (a[i][j] > 0)
                                {
                                    a[i][j] ++;
                                }
                            }
                        }
                        // add 1 pixel live time at the snake tail
                        {
                            int i = 0;
                            int j = 0;
                            //int count = 0;
                            for(i=0;i<10;i++)
                            {
                                for(j=0;j<10;j++)
                                {
                                    // Determine the direction of the tail
                                    if (a[i][j] == 2 && a[i][j+1] == 3)
                                    {
                                        a[i][j-1] = 1;
                                    }
                                    else if(a[i][j] == 2 && a[i][j-1] == 3)
                                    {
                                        a[i][j+1] = 1;
                                    }
                                    else if(a[i][j] == 2 && a[i+1][j] == 3)
                                    {
                                        a[i-1][j] = 1;
                                    }
                                    else if(a[i][j] == 2 && a[i-1][j] == 3)
                                    {
                                        a[i+1][j] = 1;
                                    }
                                }
                            }
                        }
                        printf("\a");
                        random_food(a);
                        snake_length++;
                        score++;
                        latency -= 10; // Auto increase difficulty
                    }
                }
                printscreen(a,latency,score);
            }

        }//END DO 2
        while(1); //DOUBLE CLICK TO SEE WHRER "break"
        if(game_over_return)
        {
            printf("invalid!");
            restart = 1;
            //reinitialize all the value
            snake_direction      = 77;
            last_snake_direction = snake_direction;
            snake_length         = 4;
            snake_head_x         = 0;
            snake_head_y         = 0;
            latency              = 400;
            score                = 0;
            {
                int i = 0;
                int j = 0;
                for(i=0;i<10;i++)
                {
                    for(j=0;j<10;j++)
                    {
                        a[i][j] = 0;
                    }
                }
            }
        }
        else
        {
            exit(0);// exit the game
        }
    }//END DO 1
    while(restart);
    //Sleep(100000);
    return 0;
}

/******************************FUNCTION************************************/
// 72->UP   80->DOWN    75->LEFT    77->RIGHT   0->ERROR
void get_direction(int *pointer, int wasd)
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
    // for WASD support
    else if(key_1 == 119 && wasd == 1)//W
    {
        key_2 = 72;
    }
    else if(key_1 == 97 && wasd == 1) //A
    {
        key_2 = 75;
    }
    else if(key_1 == 115 && wasd ==1) //S
    {
        key_2 = 80;
    }
    else if(key_1 == 100 && wasd ==1) //D
    {
        key_2 = 77;
    }
    // for get the input of restart game and exit game
    else if(key_1 == 49 || key_1 == 50)   //1 AND 2
    {
        key_2 = key_1;
    }
    *pointer = key_2;
}
void menu()
{
    ;
}
//Keyboard getch(direction and option) thread
DWORD WINAPI ThreadProc1( LPVOID lpParam )
{
    while(1)
    {
        get_direction(p_snake_direction,wasd_support);   // Monitor keyboard input
    }
}
// print the game
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
            if(debug_mode)// debug mode
            {
                if(a[j][k] >= 1)      // print snake body
                {
                    printf("%d ",a[j][k]);
                }
                else if(a[j][k] == -1)// print food
                {
                    printf("%d ",a[j][k]);
                }
                else                  // print blank
                {
                    printf("  ");
                }
            }
            else
            {
                if(a[j][k] >= 1)      // print snake body
                {
                    printf("* ");
                }
                else if(a[j][k] == -1)// print food
                {
                    printf("& ");
                }
                else                  // print blank
                {
                    printf("  ");
                }
            }

        }
        printf("\b#");
    }
    printf("\n");
    for(i=0; i<width+1; i++)printf("##");
    printf("\b ");
    printf("\nScore: %d",score);
    // don't make too difficult
    // if difficulty lower than limit, set difficulty equal limit
    if(t < difficulty_limit)
    {
        t = difficulty_limit;
    }
    Sleep(t);


}
// print game over screen
int game_over(int score)
{
    int i = 0;
    system("cls");
    for(i=0; i<21; i++)printf("#");
    for(i=0;i<4;i++)printf("\n#                   #");
    printf("\n#    GAME OVER!     #");
    printf("\n#    YOUR SCORE:    #");
    printf("\n#       %03d         #", score);
    for(i=0;i<3;i++)printf("\n#                   #");
    printf("\n");
    for(i=0; i<21; i++)printf("#");
    printf("\ninput 1: continue game\ninput 2: exit game\n");
    do
    {
        if(snake_direction == 49)
        {
            return 1;
        }
        else if(snake_direction == 50)
        {
            return 0;
        }
        else
        {
            Sleep(100);
        }
    }
    while(1);
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
// READY for start
void ready(int i)
{
    if(i > 0)
    {
        int j;
        for(j=i;j>0;j--)
        {
            int i = 0;
            system("cls");
            for(i=0; i<21; i++)printf("#");
            for(i=0;i<4;i++)printf("\n#                   #");
            printf("\n#      Ready!       #");
            printf("\n#        %d          #", j);
            for(i=0;i<4;i++)printf("\n#                   #");
            printf("\n");
            for(i=0; i<21; i++)printf("#");
            Sleep(1000);
        }
    }
}
/*
// How record input value to a[10][10]:
// The value is pixel live time, so the biggest value represent snake head
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
