#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <vector>
#include <iostream>
#include <list>
#include <memory>


#include "Text.h"

#include "Shapes.h"
#include "math.h"
#include "Tiles.h"

#include "util.h"
#include "Networking.h"
#include "Textures.h"
#include "Camera.h"
#include "SaveLoad.h"
#include "Profile.h"
#include "Entities.h"

class StateTracker
{
public:
    unsigned int lastState;
    unsigned int currentState;
    enum
    {
        quests,
        evolution,
        simulation,
        contest,
        shops,
        archive,
        mainLoop,
        mainMenu,
        multiplayer,
        profile,
        options,
        credits


    };
    StateTracker();
};
extern StateTracker stateTracker;

bool chatCommand(std::string input);



void gameSetup();

void runServerStuffs();


void runPlayerInputs();
void runGame();
void renderGame();

bool playerCamera();



#endif // GAME_H_INCLUDED
