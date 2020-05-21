#include "libFloodSpace.h"
using namespace FloodSpace;

int main(int argc, char* argv[])
{
    srand(time(nullptr));
    if(argc != 4)
    {
        cerr << "Incorrect number of CMD arguments.\nUsage: <Number of Compone> <Player location Row> <Player location Col>";
        exit(CMD_ARG_COUNT);
    }
    GameWorld recGameWorld;

    recGameWorld = createGameWorld();
    recGameWorld.intNumComponent = convertToInteger(argv[1]);
    recGameWorld.intPlayerR = convertToInteger(argv[2]);
    recGameWorld.intPlayerC = convertToInteger(argv[3]);
    placePlayer(recGameWorld);
    placeComponents(recGameWorld);

    int intDetermineSide = recGameWorld.intCols /2;

    if(recGameWorld.intPlayerC > intDetermineSide)
    {
        cerr << "Player can not be placed on the RIGHT half of the game area.\nTry again with a Col value closer to the LEFT half of game area";
        exit(ERROR_RIGHT_SIDE_ALERT);
    }

    char chInput = '\0';
    bool blnContinue =true;
    do{

        system("cls");
        cout << "************************************************************** \n";
        cout << "**************WELCOME TO THE UTOPIAN LAGOON!****************** \n";
        cout << "************************************************************** \n";
        printWorld(recGameWorld);


        cout << " W)-Move UP" << endl
             << " S)-Move DOWN" << endl
             << " A)-Move LEFT" << endl
             << " D)-Move RIGHT" << endl
             << " X)-Exit Utopian Lagoon" << endl
             << "Enter an option: ";
    cin >> chInput;
    switch(chInput)
    {
        case 'w':
        case 'W':
        case 'a':
        case 'A':
        case 'd':
        case 'D':
        case 's':
        case 'S':
        movePlayer(recGameWorld,chInput);
        //evaluateChance(recGameWorld);
        break;
        case 'x':
        case 'X':
            blnContinue = false;
            cout << "*************************************************************" << endl;
            cout << "***************GOODBYE THANKS FOR PLAYING********************" << endl;
            cout << "*************************************************************" << endl;
            break;
        default:
            cerr << "Invalid Input!";
            break;
    }


    }while(blnContinue);
    destroyWorld(recGameWorld);

    return SUCCESS;
}
