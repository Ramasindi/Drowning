#include "libFloodSpace.h"

namespace FloodSpace
{
    ///converting string to integer
    int convertToInteger(string strNumber)
    {
        int intNumber = 0;
        stringstream ssConvert;
        ssConvert << strNumber;
        ssConvert >> intNumber;
        if(ssConvert.fail())
        {
            cerr << "Error: Couldn't convert to integer.";
            exit(CONVERTION_ERR);
        }
        return intNumber;
    }
    ///generate random numbers
    int generateRandom(int intMin,int intMax)
    {
        int intRange = 0;
        int intRandom = 0;

        intRange = intMax - intMin + 1;
        intRandom = rand() % intRange + intMin;
        return intRandom;
    }
    ///place components
    void placeComponents(GameWorld recGameWorld)
    {
        int intDetermineSide = recGameWorld.intCols /2;

        int intDeployedComponents = 0 ;
		while(intDeployedComponents < recGameWorld.intNumComponent)
		{
			int intComponentR = generateRandom(0, intDetermineSide - 1);
			int intComponentC = generateRandom(0, intDetermineSide - 1);
			if(recGameWorld.aryGameArea[intComponentR][intComponentC] == 0)
			{
			   recGameWorld.aryGameArea[intComponentR][intComponentC] = COMPONENT;

                intDeployedComponents++;
                recGameWorld.intComponentR = intComponentR;
                recGameWorld.intComponentC = intComponentC;
			}
		}

    }

    ///Place Player in the game area
    void placePlayer(GameWorld recGameWorld)
    {
        int intDetermineSide = recGameWorld.intCols /2;
        for(int r =0;r < recGameWorld.intRows;r++)
        {
            for(int c =0;c <recGameWorld.intCols;c++)
            {
                if( c < intDetermineSide)
                {
                    recGameWorld.aryGameArea[recGameWorld.intPlayerR][recGameWorld.intPlayerC] = PLAYER;
                }
            }
        }
    }

    ///Place game area features

    void placeFeatures(GameWorld recGameWorld)
    {
        int intDetermineSide = recGameWorld.intCols /2;

        for(int r =0;r < recGameWorld.intRows;r++)
        {
            for(int c =0;c < recGameWorld.intCols;c++)
            {
                if( c > intDetermineSide)
                {
                    recGameWorld.aryGameArea[r][c] = FLOOD;
                }
            }
        }
    }
    ///creating gameworld
    GameWorld createGameWorld()
    {

        GameWorld recGameWorld;
        int intRandomRows = generateRandom(10,25);
        int intRandomCols = generateRandom(10,25);


        cout << intRandomRows << endl;
        cout << intRandomCols << endl;

        recGameWorld.aryGameArea = new int*[intRandomRows];
        for(int r =0;r < intRandomRows;r++)
        {
            recGameWorld.aryGameArea[r] = new int[intRandomCols];
            for(int c =0;c < intRandomCols;c++)
            {
                recGameWorld.aryGameArea[r][c] = EMPTY_SPACE;
            }
        }
        recGameWorld.intRows = intRandomRows;
        recGameWorld.intCols = intRandomCols;
        placeFeatures(recGameWorld);

        return recGameWorld;
    }
    ///check if the player is in the gameworld
    bool  isInWorld(GameWorld recGameWorld,int intRow,int intCol)
    {
		if(intRow < 0)
			return false;
		if(intRow >= recGameWorld.intRows)
			return false;
		if(intCol < 0)
			return false;
		if(intCol>= recGameWorld.intCols)
			return false;
		return true;

    }

    int intP = 0;
    void movePlayer(GameWorld& recGameWorld,char chInput)
    {

            recGameWorld.aryGameArea[recGameWorld.intPlayerR][recGameWorld.intPlayerC] = EMPTY_SPACE;

            switch(chInput)
            {
            case 'w':
            case 'W':
                if(recGameWorld.intPlayerR > 0)
                {
                    recGameWorld.intPlayerR--;
                }

               break;
            case 'a':
            case 'A':
                if(recGameWorld.intPlayerC > 0)
                {
                    recGameWorld.intPlayerC--;
                }
                break;
            case 'd':
            case 'D':
                if(recGameWorld.intPlayerC <= recGameWorld.intCols -2)
                {
                    recGameWorld.intPlayerC++;
                }

                break;
            case 's':
            case 'S':
                if(recGameWorld.intPlayerR <= recGameWorld.intRows -2)
                {
                 recGameWorld.intPlayerR++;
                }
                break;
            default:
                cerr << "Invalid Input!";
                break;
            }

            int intComponentsC =0;

            if(recGameWorld.aryGameArea[recGameWorld.intPlayerR][recGameWorld.intPlayerC] == FLOOD)
            {

                cout << "*************************************************************" << endl;
                cout << "***************GAME OVER YOU DROWNED*************************" << endl;
                cout << "*************************************************************" << endl;
                exit(SUCCESS);
            }

            if(recGameWorld.aryGameArea[recGameWorld.intPlayerR][recGameWorld.intPlayerC] == COMPONENT)
            {

                recGameWorld.intNumComponent--;
            }
            if(recGameWorld.intNumComponent == 0)
            {
                cout << "*************************************************************" << endl;
                cout << "******YOU WON ALL COMPONENTS HAVE BEEN COLLECTED*************" << endl;
                cout << "*************************************************************" << endl;
                exit(SUCCESS);
            }
            recGameWorld.aryGameArea[recGameWorld.intPlayerR][recGameWorld.intPlayerC] = PLAYER;
            int intDetermineSide = recGameWorld.intCols /2;

           recGameWorld.intNewCol = recGameWorld.intCols - intDetermineSide;

             if(generateRandom(1,100) <=50)
             {
               intP--;
               int intDetermineSide = recGameWorld.intCols /2;
                int myTest = intDetermineSide;
                  myTest += intP;
                 for(int r =0;r < recGameWorld.intRows;r++)
                 {
                 recGameWorld.aryGameArea[r][intDetermineSide] = FLOOD;
                 recGameWorld.aryGameArea[r][myTest] = FLOOD;

                    if(recGameWorld.intPlayerC == myTest)
                     {
                        cout << "*************************************************************" << endl;
                        cout << "************THE FLOOD CAUGHT YOU GAMEOVER********************" << endl;
                        cout << "*************************************************************" << endl;
                        exit(SUCCESS);
                     }


                     if(recGameWorld.aryGameArea[r][myTest] == 3)
                     {
                        cout << "*************************************************************" << endl;
                        cout << "************THE FLOOD CAUGHT COMPONENT GAMEOVER**************" << endl;
                        cout << "*************************************************************" << endl;
                       exit(SUCCESS);
                     }
                 }

             }

    }


    ///printing the game world
    void printWorld(GameWorld recGameWorld)
    {

        for(int r=0;r < recGameWorld.intRows;r++)
        {
            for(int c=0;c < recGameWorld.intCols;c++)
            {
               cout << recGameWorld.aryGameArea[r][c] << " ";
            }
            cout << endl;
        }
    }
}
