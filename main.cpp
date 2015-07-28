#include <iostream>
#include "basic.h"
#include "user.h"
#include "friendhash.h"
#include "tokenizer.h"
#include "gamelogic.h"

using namespace std;

int main() {
    BasicHT userHashtable(5);
    FriendHash friendshipHashtable(5);
    GameLogic newGame(userHashtable, friendshipHashtable);
    newGame.startGameLoop();

    return 0;
}