#ifndef LIBFLOODSPACE_H_INCLUDED
#define LIBFLOODSPACE_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cassert>
#include <ctime>

using namespace std;
namespace FloodSpace
{
    ///Exit codes
    enum errorCodes
    {
        SUCCESS,
        CONVERTION_ERR,
        CMD_ARG_COUNT,
        ERROR_RIGHT_SIDE_ALERT
    };
    ///Values for game features
    enum features
    {
        EMPTY_SPACE,
        PLAYER,
        FLOOD,
        COMPONENT
    };
    char const FEATURE_SYMBOL[] = {'.','P','#','O'};
    ///Two dimentional array declaration
    //typedef int* oneD;
    typedef int** gameArea;


    ///Structure for the whole Game World
    struct GameWorld
    {
        gameArea aryGameArea;

        int intRows;
        int intCols;

        int intPlayerR;
        int intPlayerC;

        int intNumComponent;

        int intComponentR;
        int intComponentC;
        int intNewCol;
    };

    ///Convert string to integer
    int convertToInteger(string strNumber);
    int generateRandom(int intMin,int intMax);
    GameWorld createGameWorld();
    void placeFeatures(GameWorld);
    void placePlayer(GameWorld recGameWorld);
    void placeComponents(GameWorld recGameWorld);
    void movePlayer(GameWorld& recGameWorld,char chInput);
    bool isInWorld(GameWorld recGameWorld);
    void evaluateChance(GameWorld& recGameWorld);
    void printWorld(GameWorld recGameWorld);
    void destroyWorld(GameWorld& recworld);

}

#endif // LIBFLOODSPACE_H_INCLUDED
