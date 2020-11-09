#include <iostream>
#include <thread>
using namespace std;

#include <stdio.h>
#include <string.h>
#include<conio.h>
#ifdef _WIN32
#include <Windows.h>
#else
//#include <unistd.h>
#endif

bool verboseFlag = false;
const int screenWidth=40, screenHeight=20;
char screen[screenWidth][screenHeight];
int plyrPos[screenWidth*screenHeight][2];  //plyrPos[X position][Y position]. not grid but list from 0. for loop search first index for current length of player. second index x=0 y=1 
int plyrTail[2];
int plyrLngth=5, plyrDir=0;
char plyr = '0';
int plyrSpeed = 500;

class Fruit
{
    public:
    int frtPosX, frtPosY;
    Fruit* next;
};

//int pLastPos[screenWidth][screenHeight];

int initScreen() //initialise the screen array to some background value
{
    for(int y=0; y<screenHeight; y++) //move to next column
    {
        for(int x=0; x<screenWidth; x++) //assign row x
        {
            screen[x][y] = ' ';
        }
    }
    
    return 1;
}

int initAssets()
{
    return 1;
}

//wait for player input
int inputEvent()
{
    while(1)
    {
        char input = getch();

        switch (input)
        {
        case 'w':
            plyrDir=0;

            break;

        case 'd':
            plyrDir=1;

            break;

        case 's':
            plyrDir=2;

            break;

        case 'a':
            plyrDir=3;

            break;
        
        case '`':
            exit(0);
            
            break;

        default:
            break;
        }
    }

    return 1;
}

int updatePos()
{
    //FOR 0 TO PLAYERLENGTH

    //int plyrPos[resolution]


    // screen[plyrTail[0]-1][plyrTail[1]-1] = ' ';
    // screen[plyrTail[0]-1][plyrTail[1]+1] = ' ';
    // screen[plyrTail[0]+1][plyrTail[1]-1] = ' ';
    // screen[plyrTail[0]+1][plyrTail[1]+1] = ' ';

    initScreen();

    for (int x=0; x<plyrLngth; x++)
    {
        screen[plyrPos[x][0]][plyrPos[x][1]] = plyr;
    }

    //screen[plyrPos[0][0]][plyrPos[x][1]] = plyr;

    return 1;
}

//move the snake's head position and update the tail position
int snakeCrawl()
{
    while (1)
    {
        switch (plyrDir)
        {
        case 0:
            if(plyrPos[0][1]!=0)
            {
                plyrTail[1]=plyrPos[plyrLngth][1];
                

                for(int x=plyrLngth-1; x>0; x--)
                {
                    plyrPos[x][0] = plyrPos[x-1][0];
                    plyrPos[x][1] = plyrPos[x-1][1];
                }
                plyrPos[0][1]--;

            }
            else
            {
                plyrTail[1]=plyrPos[plyrLngth][1];
                for(int x=plyrLngth-1; x>0; x--)
                {
                    plyrPos[x][0] = plyrPos[x-1][0];
                    plyrPos[x][1] = plyrPos[x-1][1];
                }
                plyrPos[0][1] = screenHeight-1;
            }
            break;

        case 1:
            if(plyrPos[0][0]!=(screenWidth-1))
            {
                plyrTail[0]=plyrPos[plyrLngth][0];
                for(int x=plyrLngth-1; x>0; x--)
                {
                    plyrPos[x][0] = plyrPos[x-1][0];
                    plyrPos[x][1] = plyrPos[x-1][1];
                }
                plyrPos[0][0]++;
            }
            else
            {
                plyrTail[0]=plyrPos[plyrLngth][0];
                for(int x=plyrLngth-1; x>0; x--)
                {
                    plyrPos[x][0] = plyrPos[x-1][0];
                    plyrPos[x][1] = plyrPos[x-1][1];
                }
                plyrPos[0][0] = 0;
            }
            break;

        case 2:
            if(plyrPos[0][1]!=(screenHeight-1))
            {
                plyrTail[1]=plyrPos[plyrLngth][1];
                for(int x=plyrLngth-1; x>0; x--)
                {
                    plyrPos[x][0] = plyrPos[x-1][0];
                    plyrPos[x][1] = plyrPos[x-1][1];
                }
                plyrPos[0][1]++;
            }
            else
            {
                plyrTail[1]=plyrPos[plyrLngth][1];
                for(int x=plyrLngth-1; x>0; x--)
                {
                    plyrPos[x][0] = plyrPos[x-1][0];
                    plyrPos[x][1] = plyrPos[x-1][1];
                }
                plyrPos[0][1] = 0;
            }
            break;

        case 3:
            if(plyrPos[0][0]!=0)
            {
                plyrTail[0]=plyrPos[plyrLngth][0];
                for(int x=plyrLngth-1; x>0; x--)
                {
                    plyrPos[x][0] = plyrPos[x-1][0];
                    plyrPos[x][1] = plyrPos[x-1][1];
                }
                plyrPos[0][0]--;
            }
            else
            {
                plyrTail[0]=plyrPos[plyrLngth][0];
                for(int x=plyrLngth-1; x>0; x--)
                {
                    plyrPos[x][0] = plyrPos[x-1][0];
                    plyrPos[x][1] = plyrPos[x-1][1];
                }
                plyrPos[0][0] = screenWidth-1;
            }
            break;
        
        default:
            break;
        }

        updatePos();

        Sleep(plyrSpeed);
    }
    
}



//print screen array to console
int render()
{
    while(true)
    {
        #ifdef _WIN32
        system("CLS");
        #else
        system("clear");
        #endif

        std::cout << "\r" << std::flush;

        for(int y=0; y<screenHeight; y++) //move to next column
        {
            for(int x=0; x<screenWidth; x++) //print row x
            {
                std::cout << screen[x][y];
                //std::cout << ".";
            }
            std::cout<<std::endl;
        }
        
        Sleep(30);
    }
    
    return 1;
}



int main(int argc, char* argv[])
{
    for(int i=0; i<argc; i++)
    {
        std::cout << "Argument " << argc << ": " << argv[i] << std::endl;
    }

    //plyrTail[0] = 20, plyrTail[1] = 10;
    plyrPos[0][0] = 20, plyrPos[0][1] = 10;

    initScreen();
    //screen[plyrPos[0][0]][plyrPos[0][1]] = plyr;

    std::thread rendthread(render);
    std::thread crawlthread(snakeCrawl);
    std::thread inputthread(inputEvent);
    

    while(true)
    {
        Sleep(1000);
    }

    return 1;
}