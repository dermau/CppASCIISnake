#include <iostream>
//#include <ctime>
#include <thread>
using namespace std;

#include <stdio.h>
#include <string.h>
#include<conio.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

bool verboseFlag = false;
const int screenWidth=40, screenHeight=20;
char screen[screenWidth][screenHeight];
char playerAssetStraight[2][2];
char playerAssetDiagRight[2][2];
char playerAssetDiagLeft[2][2];
char playerAssetFlat[2][2];
int playerPosX, playerPosY;
int pLastPosX, pLastPosY;

int initAssets()
{
    playerAssetStraight[0][0] = '|';
    playerAssetStraight[0][1] = '|';
    playerAssetStraight[1][0] = '|';
    playerAssetStraight[1][1] = '|';

    playerAssetDiagRight[0][0] = '/';
    playerAssetDiagRight[0][1] = ' ';
    playerAssetDiagRight[1][0] = ' ';
    playerAssetDiagRight[1][1] = '/';

    playerAssetDiagLeft[0][0] = ' ';
    playerAssetDiagLeft[0][1] = '\\';
    playerAssetDiagLeft[1][0] = '\\';
    playerAssetDiagLeft[1][1] = ' ';

    playerAssetFlat[0][0] = '-';
    playerAssetFlat[0][1] = '-';
    playerAssetFlat[1][0] = '-';
    playerAssetFlat[1][1] = '-';

    for (int y=0; y<screenHeight; y++)
    {
        for(int x=0; x<screenWidth; x++)
        {
            screen[x][y] = ' ';
        }
    }

    return 1;
}

int updatePos(int x, int y)
{
    //reset the map pixels. use second array for map when implemented
    screen[pLastPosX][pLastPosY] = ' ';
    screen[pLastPosX][pLastPosY+1] = ' ';
    screen[pLastPosX+1][pLastPosY] = ' ';
    screen[pLastPosX+1][pLastPosY+1] = ' ';

    //set the character pixels
    screen[playerPosX][playerPosY] = playerAssetStraight[0][0];
    screen[playerPosX][playerPosY+1] = playerAssetStraight[0][1];
    screen[playerPosX+1][playerPosY] = playerAssetStraight[1][0];
    screen[playerPosX+1][playerPosY+1] = playerAssetStraight[1][1];
    return 1;
}

int positionEvent()
{
    char userIn;
    while(true)
    {
        
        //std::cout << "cin ";
        userIn = getch();
        //std::cout << "char: " << userIn << std::endl;
        if (userIn == 'w'||userIn == 'W') //placeholder for key value (up) condition
        {
            pLastPosX=playerPosX, pLastPosY=playerPosY;
            playerPosY--;
        }
        if (userIn == 'd'||userIn == 'D') //placeholder for key value (up) condition
        {
            pLastPosX=playerPosX, pLastPosY=playerPosY;
            playerPosX++;
        }
        if (userIn == '`')
        {
            exit(0);
        }

        updatePos(playerPosX, playerPosY);
        //Sleep(2000);
    }

    return 1;
}

int render()
{
    while(true)
    {
        #ifdef _WIN32
        system ("CLS");
        #else
        #ifdef linux
        system ("clear");
        #else
        system ("clear");
        #endif
        #endif

        
        std::cout << "\r" << std::flush;

        for (int y=0; y<screenHeight; y++)
        {
            for(int x=0; x<screenWidth; x++)
            {
                std::cout << screen[x][y];
            }
            std::cout << std::endl;
        }

        Sleep(32);
        
    }

    return 1;
}

int main(int argc, char* argv[])
{
    for(int i=0; i<argc; i++)
    {
        std::cout << "Argument " << i << ": " << argv[i] << std::endl;
    }

    initAssets();
    playerPosX=20, playerPosY=10;
    updatePos(playerPosX,playerPosY);
    
    std::thread rendthread(render);

    std::thread eventhread(positionEvent);

    while(true)
    {

    }


    return 1;
}
